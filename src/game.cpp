#include "game.h"
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

    controller.HandleInput(running, snake);
    Update();
    renderer.Render(snake, food, food2);//pass food2 to Render

    frame_end = SDL_GetTicks();

    frame_count++;
    frame_duration = frame_end - frame_start;

    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(score, frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

void Game::PlaceFood() {
  //using lock_guard to lock the thread
  std::lock_guard<std::mutex> uLock(mtx);
  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
  
    if (!snake.SnakeCell(x, y)) {
      food.x = x;
      food.y = y;
      _condition.notify_one();//notify other thread
      return;
    }
  }
}

void Game::PlaceFood2() {
  //lock using a unique_lock
  std::unique_lock<std::mutex> uLock(mtx);
  //condition variable here to start
  _condition.wait(uLock, [this] (){ return (food.x != -1 && food.y != -1) ? true : false; });//make sure first food is set

  int x, y;
  while (true) {
    x = random_w(engine);
    y = random_h(engine);
//     Check that the location is not occupied by a snake item or the first
    //food item before placing the second food
    if (!snake.SnakeCell(x, y) && !FoodCell(x, y)) {
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

  // Check if food or food2 is present where the snake head is
  if (food.x == new_x && food.y == new_y || food2.x == new_x && food2.y == new_y) {
    score++;
      food.x = -1;
      food.y = -1;
      food2.x = -1;
      food2.y = -1;
    //Call functions PlaceFood and PlaceFood2 using threads
    std::thread t1(&Game::PlaceFood, this);
    std::thread t2(&Game::PlaceFood2, this);
    //join the threads back to the main function
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
  return false;
}

int Game::GetScore() const { return score; }
int Game::GetSize() const { return snake.size; }