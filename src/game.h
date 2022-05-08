#ifndef GAME_H
#define GAME_H

#include <random>
#include <mutex>//including mutex, condition_variable, thread
#include <condition_variable>
#include <thread>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "snake.h"

class Game {
 public:
  Game(std::size_t grid_width, std::size_t grid_height);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetScore() const;
  int GetSize() const;
  
  void PlaceFood();
  void PlaceFood2();//new function to place food 2

 private:
  Snake snake;
  SDL_Point food;
  SDL_Point food2;//new SDL_Point food2
  
  std::mutex mtx;//added
  std::condition_variable _condition;//added

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  int score{0};

  void Update();
  bool FoodCell(int x, int y);//check x and y of the first food
};

#endif