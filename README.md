# CPPND: Capstone Snake Game Example

This is a starter repo for the Capstone project in the [Udacity C++ Nanodegree Program](https://www.udacity.com/course/c-plus-plus-nanodegree--nd213). The code for this repo was inspired by [this](https://codereview.stackexchange.com/questions/212296/snake-game-in-c-with-sdl) excellent StackOverflow post and set of responses.

<img src="snake_game.gif"/>

The Capstone Project gives you a chance to integrate what you've learned throughout this program. This project will become an important part of your portfolio to share with current and future colleagues and employers.

In this project, you can build your own C++ application or extend this Snake game, following the principles you have learned throughout this Nanodegree Program. This project will demonstrate that you can independently create applications using a wide range of C++ features.

## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  >Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source. 
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SnakeGame`.


## CC Attribution-ShareAlike 4.0 International


Shield: [![CC BY-SA 4.0][cc-by-sa-shield]][cc-by-sa]

This work is licensed under a
[Creative Commons Attribution-ShareAlike 4.0 International License][cc-by-sa].

[![CC BY-SA 4.0][cc-by-sa-image]][cc-by-sa]

[cc-by-sa]: http://creativecommons.org/licenses/by-sa/4.0/
[cc-by-sa-image]: https://licensebuttons.net/l/by-sa/4.0/88x31.png
[cc-by-sa-shield]: https://img.shields.io/badge/License-CC%20BY--SA%204.0-lightgrey.svg

USER RUBRIC LAYOUT AND ADDITIONS
  SUMMARY
  This is a new version of the snake game with additional elements implemented to make play more
  interesting. Now two pieces of food drop instead of just one. When the snake eats either the first food or food2 the score is incremented by 1, both foods are removed, and two new foods are placed.

  At the start of the program it now check if there are past scores saved and if so it prints them in the console from highest to lowest. When the game is over before the program ends the user is asked if they want to save their score.
  

  RUNNING
    - create a new directory called "build"
    - in build run "cmake .."
    - then run "make"
    - run program with "./SnakeGame

1. Loops, Functions, I/O: The Project reads data from a file and processes the data or the program writes data to a file.
  - In main.cpp the function Input() reads in data from a file called "saved.txt". The data from the file contains previously saved user scores. The scores are then sorted and printed to the console. Lines 15-51
  - In main.cpp the function Output() writes new scores to the file "saved.txt".
  Lines 54-61
2. Loops, Functions, I/O: The project accepts user input and processes the input.
  - At the end of main.cpp the program asks the user if they would like to save the score from the previous game. If the user agrees the program then initiates the Output() function and writes to "saved.txt". If the user selects no then the program terminates without saving the score.
  Lines 81-92
3. The project uses multithreading.
  - In game.cpp in the function Update() the program starts two threads t1 and t2 to call the functions   PlaceFood() and PlaceFood2().
  Lines 98-103
4. A mutex or lock is used in the project
  - In game.cpp inside the function PlaceFood() a mutex is used to lock with lock_guard to be sure that multiple threads never access this function at the same time.
  Line 48
  - In game.cpp inside the function PlaceFood2() a mutex is used with unique_lock
  Line 65
5. A condition variable is used in the project
  - In game.cpp inside PlaceFood2() a condition variable is used to wait until the first food from PlaceFood() is set.
  Line 67
  - In game.cpp inside PlaceFood() the condition is notified when the function ends after the first food has been set.
  Line 57

    