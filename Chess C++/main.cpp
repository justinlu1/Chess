// C++ Chess Project
// Justin, Danny, Evan
// May 24, 2021

// Main file, handles the menus and overall structure of the program

#include <iostream>
#include <stdlib.h>
#include <string>
#include <ctype.h>
#include "include/main.hpp"
using namespace std;

//♙ ♘ ♗ ♖ ♕ ♔ ♚ ♛ ♜ ♝ ♞ ♟

// Overloading cout
ostream& operator<<(ostream& os, map<string, Cell>& inputBoard) {
  string coordinate;
  os << endl;
  for (int i = 8; i >= 1; i--) { // Print from 8th rank first (top of the board)
    os << i << " ";
    for (int j = 1; j <= 8; j++) { // Print from a-file first (left of the board)
      string tempFile(1, (char) (j + 96));
      // char tempFile = (char) (i + 96);
      coordinate = (tempFile) + to_string(i);
      // cout << "printing " << coordinate << endl;
      Piece curPiece = inputBoard.find(coordinate)->second.getPiece();
      string unicodePiece = "";
      char pieceType = curPiece.getType();
      bool pieceColour = curPiece.getWhite();
      if (pieceType == 'x') os << "  ";
      else {
        if (pieceColour == false) { // black
          unicodePiece = "\033[1;31m";
          switch (pieceType) {
            case 'p':
              unicodePiece += "♙\033[0m";
              break;
            case 'n':
              unicodePiece += "♘\033[0m";
              break;
            case 'b':
              unicodePiece += "♗\033[0m";
              break;
            case 'r':
              unicodePiece += "♖\033[0m";
              break;
            case 'q':
              unicodePiece += "♕\033[0m";
              break;
            case 'k':
              unicodePiece += "♔\033[0m";
              break;
          }
        }
        else { // white
          switch (pieceType) {
            case 'p':
              unicodePiece += "♟";
              break;
            case 'n':
              unicodePiece += "♞";
              break;
            case 'b':
              unicodePiece += "♝";
              break;
            case 'r':
              unicodePiece += "♜";
              break;
            case 'q':
              unicodePiece += "♛";
              break;
            case 'k':
              unicodePiece += "♚";
              break;
          }
        }
        os << unicodePiece << " ";
      }
    }
    os << endl;
  }
  os << "  A B C D E F G H" << endl;
  return os;
}

bool startMenu() { // initial menu for choosing options
  string menuChoice; // what the user chooses
  int stoiMenuChoice; // integer version of user choice
  bool validMenu = false; // whether or not the input was valid
  
  cout << "Welcome to Danny, Evan, and Justin's C++ Chess Game!\n1. Start\n2. Rules\n3. Quit\n";

  while (validMenu == false) { // Input validation for first menu
    cin >> menuChoice;
    validMenu = true; // setting to true each time through
    try { 
      stoiMenuChoice = stoi(menuChoice); // try to convert a string to an int
    } catch (...) { // catch any error
        cout << "Invalid choice, try again." << endl; 
        validMenu = false; // setting false to restart loop if invalid
    }
  }
  switch(stoiMenuChoice) { // switch between 1,2,3
      case 1: // Starting program: 
        cout << "Starting..." << endl;
        return true; // only return true if we should continue
      case 2: 
        cout << "Read up on the rules of chess here:\nhttps://en.wikipedia.org/wiki/Rules_of_chess\n" << endl;
        break;
      case 3:
        cout << "Quitting..." << endl;
        exit(0);
      default: 
        cout << "Invalid choice, try again." << endl;
        break;
  }
  return false; // return false otherwise
}

bool endMenu() { // final menu to play again or quit
  bool playAgainValid = false; // input validation loop for playAgain
  string playAgainChoice; // taking input as string to avoid crashes
  int stoiPlayAgainChoice; // converting to int

  cout << "Game over!\n1. Play Again\n2. Quit\n" << endl;
    while (playAgainValid == false) { // loop while user hasn't entered a valid choice
      playAgainValid = true; // assume true (if valid, then the loop won't restart)
      cin >> playAgainChoice;
      try {
        stoiPlayAgainChoice = stoi(playAgainChoice); 
      } catch (...) { // if input can't be converted, it's invalid
        cout << "Invalid input." << endl;
        playAgainValid = false; // set to false and restart loop
      }
    }
  if (stoiPlayAgainChoice == 1) { // if user chose to restart
    cout << "Restarting..." << endl;
    return true;
  }
  cout << "Quitting..." << endl;
  exit(0);
}

int main() { // main function
  bool playAgain = true; // loop the entire program
  bool loopStartMenu = false; // loop the start menu
  bool loopEndMenu = false; // loop the end menu
  bool gameOver = false; // loop the game (each turn)
  int gameResult = 0;
  Game game; // The chess game

  while (playAgain == true) { // Allows user to play another game
    do { // Show first menu 
      loopStartMenu = startMenu();
    } while (loopStartMenu == false);
    
    game.setNames(); // Set the names of both players
    initialize(); // Initialize the board (initialize.cpp)
    
    while (gameOver == false) { // main game loop
      // cout << board << endl;
      system("CLS"); // clear output
      cout << "C++ Chess Game\n\n" << chessBoard << endl;
      switch(game.processTurn1()) { // 0 = normal, 1 = resign, 2 = draw
        case 0: // continue
          break;
        case 1: // resign
          cout << game.getPlayer(2).getName() << " wins by resignation." << endl;
          gameOver = true;
          break;
        case 2: // draw
          cout << "Drawn by agreement." << endl;
          gameOver = true;
          break;
      }
      Game::mateCheck(false); // check if black can still play
      cout << "white checkmate: " << Game::getWhiteInCheckmate() << " black checkmate: " << Game::getBlackInCheckmate() << " black stalemate: " << Game::getBlackInStalemate() <<    " white stalemate: " << Game::getWhiteInStalemate() << endl;
      if (Game::getBlackInCheckmate()) {
        gameOver = true;
        cout << "Game over: White wins by checkmate." << endl;
      }
      else if (Game::getBlackInStalemate()) {
        gameOver = true;
        cout << "Game over: Draw by stalemate." << endl;
      }
      if (gameOver == true) { // if game is over
        break; // get out of loop
      }
      //ePCountDecrease();
      pawnPromotion();
      cout << chessBoard << endl;
      switch(game.processTurn2()) {
        case 0: // continue
          cout << "End of turn." << endl;
          break;
        case 1: // resign
          cout << game.getPlayer(1).getName() << " wins by resignation." << endl;
          gameOver = true;
          break;
        case 2: // draw
          cout << "Drawn by agreement." << endl;
          gameOver = true;
          break;
      }
      Game::mateCheck(true); // check if white can still play
      cout << "white checkmate: " << Game::getWhiteInCheckmate() << " black checkmate: " << Game::getBlackInCheckmate() << " black stalemate: " << Game::getBlackInStalemate() <<    " white stalemate: " << Game::getWhiteInStalemate() << endl;
      if (Game::getWhiteInCheckmate()) {
        gameOver = true;
        cout << "Game over: Black wins by checkmate." << endl;
      } 
      else if (Game::getWhiteInStalemate()) {
        gameOver = true;
        cout << "Game over: Draw by stalemate." << endl;
      }
      if (gameOver == true) {
        break; // get out of loop
      }
      // ePCountDecrease();
      pawnPromotion();
    }
    
    gameOver = false; // resetting in case players want to play again
    do { // Show second menu 
      loopEndMenu = endMenu();
    } while (loopEndMenu == false);
  }
  return 0;
}