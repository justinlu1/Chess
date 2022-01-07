// Sets up the game (board with pieces)

#include <iostream>
#include <stdlib.h>
#include <string>
#include <map>
#include "include/main.hpp"
using namespace std;

map<string, Cell> chessBoard;
Board board;

// Set up the board
void initialize() {
  chessBoard.clear();
  cout << "Initializing board...\n";

  string curCoordinates;
  string pieceOrder = "rnbqkbnr";
  // To start, make everything empty squares
  for (int i = 1; i <= 8; i++) {
    for (int j = 1; j <= 8; j++) {
      Cell curCell(i, j, Piece());
      string tempFile(1, (char) (i + 96));
      // char tempFile = (char) (i + 96);
      curCoordinates = (tempFile) + to_string(j);
      //cout << curCoordinates << endl;
      chessBoard.insert(make_pair(curCoordinates, curCell));
    }
  }
  /*
  // Castling Debugging position
  chessBoard.find("e1")->second.getPiece().setType('k');
  chessBoard.find("e1")->second.getPiece().setWhite(true);

  chessBoard.find("h1")->second.getPiece().setType('r');
  chessBoard.find("h1")->second.getPiece().setWhite(true);

  chessBoard.find("a1")->second.getPiece().setType('r');
  chessBoard.find("a1")->second.getPiece().setWhite(true);

  chessBoard.find("a6")->second.getPiece().setType('n');
  chessBoard.find("a6")->second.getPiece().setWhite(true);

  chessBoard.find("a3")->second.getPiece().setType('n');
  chessBoard.find("a3")->second.getPiece().setWhite(false);

  chessBoard.find("e8")->second.getPiece().setType('k');
  chessBoard.find("e8")->second.getPiece().setWhite(false);
  
  chessBoard.find("a8")->second.getPiece().setType('r');
  chessBoard.find("a8")->second.getPiece().setWhite(false);

  chessBoard.find("h8")->second.getPiece().setType('r');
  chessBoard.find("h8")->second.getPiece().setWhite(false);*/

/*
  // Promotion debugging position
  chessBoard.find("e1")->second.getPiece().setType('k');
  chessBoard.find("e1")->second.getPiece().setWhite(true);

  chessBoard.find("g7")->second.getPiece().setType('p');
  chessBoard.find("g7")->second.getPiece().setWhite(true);

  chessBoard.find("a1")->second.getPiece().setType('n');
  chessBoard.find("a1")->second.getPiece().setWhite(true);

  chessBoard.find("e8")->second.getPiece().setType('k');
  chessBoard.find("e8")->second.getPiece().setWhite(false);

  chessBoard.find("b2")->second.getPiece().setType('p');
  chessBoard.find("b2")->second.getPiece().setWhite(false);

  chessBoard.find("h8")->second.getPiece().setType('n');
  chessBoard.find("h8")->second.getPiece().setWhite(false);*/

  // Checkmate debugging position
  chessBoard.find("h1")->second.getPiece().setType('k');
  chessBoard.find("h1")->second.getPiece().setWhite(true);

  chessBoard.find("h2")->second.getPiece().setType('p');
  chessBoard.find("h2")->second.getPiece().setWhite(true);

  chessBoard.find("g2")->second.getPiece().setType('p');
  chessBoard.find("g2")->second.getPiece().setWhite(true);

  chessBoard.find("f2")->second.getPiece().setType('p');
  chessBoard.find("f2")->second.getPiece().setWhite(true);

  chessBoard.find("e8")->second.getPiece().setType('k');
  chessBoard.find("e8")->second.getPiece().setWhite(false);

  chessBoard.find("a8")->second.getPiece().setType('r');
  chessBoard.find("a8")->second.getPiece().setWhite(false);

  // Put the pawns and pieces in
  /*for (int i = 1; i <= 8; i++) {
    // Creating White pawns
    string tempFile(1, (char) (i + 96));
    cout << "white pawn " << (tempFile) + "2" << endl;
    chessBoard.find((tempFile) + "2")->second.getPiece().setType('p');
    cout << "piece on " << (tempFile) + "2 is now " << chessBoard.find((tempFile) + "2")->second.getPiece().getType() << endl;
    chessBoard.find((tempFile) + "2")->second.getPiece().setWhite(true);
    
    // Black pawns
    cout << "black pawn " << (tempFile) + "7" << endl;
    chessBoard.find((tempFile) + "7")->second.getPiece().setType('p');
    chessBoard.find((tempFile) + "7")->second.getPiece().setWhite(false);

    // White pieces
    cout << "white " << pieceOrder[i-1] << " " << (tempFile) + "1" << endl;
    chessBoard.find((tempFile) + "1")->second.getPiece().setType(pieceOrder[i-1]); // Because pieceOrder is 0-indexed
    chessBoard.find((tempFile) + "1")->second.getPiece().setWhite(true);

    // Black pieces
    cout << "black " << pieceOrder[i-1] << " " << (tempFile) + "8" << endl;
    chessBoard.find((tempFile) + "8")->second.getPiece().setType(pieceOrder[i-1]);
    chessBoard.find((tempFile) + "8")->second.getPiece().setWhite(false);
  }*/
}