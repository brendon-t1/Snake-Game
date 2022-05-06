#include "game.h"
#include <thread>
#include <iostream>
#include "SDL.h"

Game::Game(std::size_t grid_width, std::size_t grid_height)
    : snake(grid_width, grid_height),
      engine(dev()),
      random_w(0, static_cast<int>(grid_width - 1)),
      random_h(0, static_cast<int>(grid_height - 1)) {
  PlaceFood();
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  bool running = true;

  while (running) {
    frame_start = SDL_GetTicks();

    // Input, Update, Render - the main game loop.
    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, food2);

    frame_end = SDL_GetTicks();

    // Keep track of how long each loop through the input/update/render cycle
    // takes.
    frame_count++;
    frame_duration = frame_end - frame_start;

    // After every second, update the window title.
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    // If the time for this frame is too small (i.e. frame_duration is
    // smaller than the target ms_per_frame), delay the loop to
    // achieve the correct frame rate.
    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {//ORIGINAL
  std::lock_guard<std::mutex> uLock(mtx);//locking mutex to allow only one thread at a time
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y)) {
      food.x = x;//food is now a unique pointer
      food.y = y;
      _condition.notify_one();
      return;
    }
  }
}

void Game::PlaceFood2() {//take in food one data points as pointers
  std::unique_lock<std::mutex> uLock(mtx);//locking mutex to allow only one thread at a time
  //condition variable here to start
  _condition.wait(uLock, [this] (){ return (food.x == -1 && food.y == -1) ? true : false; });//make sure food is set
  int x, y;
  while (true) {
    x = random_w(engine);//make sure that these are different values
    y = random_h(engine);
    // Check that the location is not occupied by a snake item before placing
    // food.
    if (!snake.SnakeCell(x, y) && !FoodCell(x, y)) {//if the cell is not occupied by the first food
      food2.x = x;
      food2.y = y;
      return;
    }
  }
}

void Game::Update() {
  if (!snake.alive) return;

  snake.Update();

  int new_x = static_cast<int>(snake.head_x);
  int new_y = static_cast<int>(snake.head_y);

  // Check if there's food over here, either food or food 2
  if (food.x == new_x && food.y == new_y || food2.x == new_x && food.y == new_y) {
    score++;
      food.x = -1;
      food.y = -1;
      food2.x = -1;
      food2.y = -1;
      std::thread t1{ &Game::PlaceFood, this };//using threads here to place two foods
      std::thread t2{ &Game::PlaceFood2, this };
      t1.join();
      t2.join();
    // Grow snake and increase speed.
    snake.GrowBody();
    snake.speed += 0.02;
  }
}

bool Game::FoodCell(int x, int y) {
  if (x == static_cast<int>(food.x) && y == static_cast<int>(food.y)) {
    return true;
  }
//   for (auto const &item : body) {
//     if (x == item.x && y == item.y) {
//       return true;
//     }
//   }
  return false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }