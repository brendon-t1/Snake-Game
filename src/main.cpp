#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>
#include "controller.h"
#include "game.h"
#include "renderer.h"

void sortScores();
//vector of strings to save all of the scores
std::vector<std::string> all_scores;
 
//new function to read in input from "saved.txt"
void Input(){
  std::cout << "Past scores are: " << std::endl;
  std::fstream scores;//create fstream object
  scores.open("saved.txt", std::ios::in);//read in
  if(scores.is_open()) {
  	std::string line;
    while(getline(scores, line)) {
    	all_scores.emplace_back(line);//save each scores in the vector all_scores
    }
    scores.close();
  }
  sortScores();//call the sortScores function
}

//for every score in all_scores print it to the console on its own line
void PrintScores(){
	for(auto &it: all_scores){
    	std::cout << it << std::endl;
    }
}

//compare which score is larger
bool Compare(std::string s1, std::string s2) {
	if(s1.size() == s2.size()) {
		return s1 > s2;
    }
  	else {
  		return s1.size() > s2.size();
  	}
}

//Sort all of the scores from the beginning to the end of the all_scores vector
//then call the PrintScores function
void sortScores(){
	std::sort(all_scores.begin(), all_scores.end(), Compare);
  	PrintScores();
}

//write to the "saved.txt" file in append mode to add the new score in
void Output(std::string score){
  std::fstream output;//fstream object created
  output.open("saved.txt", std::ios::app);//open in append mode
  if(output.is_open()) {
	output << score;//pass the score to output
    output.close();
  }
}

int main() {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{32};
  constexpr std::size_t kGridHeight{32};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
  Game game(kGridWidth, kGridHeight);
  
  //call the input function to get all of the previous saved scores
  Input();
  game.Run(controller, renderer, kMsPerFrame);
  std::cout << "Game has terminated successfully!\n";
  std::cout << "Score: " << game.GetScore() << "\n";
  std::cout << "Size: " << game.GetSize() << "\n";
  //save the score as a string variable
  std::string score = std::to_string(game.GetScore());
  score += "\n";
  //char variable to save the user choice
  char choice;
  //ask the user if they want to save their score
  std::cout << "Do you want to add your new score to your saved scores?" << std::endl;
  std::cout << "If you do want to save please type y and hit enter, n for no: " << std::endl;
  std::cin >> choice;
  //save score if the user types 'y' otherwise end the program without saving
  if(choice == 'y'){
  Output(score);
  }
  return 0;
}