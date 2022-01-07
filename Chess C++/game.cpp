// General Game functions (turns, players)

#include <iostream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <locale>
#include "include/main.hpp"
using namespace std;

//////////////////////
//                  //
//   class Player   //
//                  //
//////////////////////

// Constructors
Player::Player(string n, bool w) {
  name = n;
  white = w;
}
Player::Player() {
  name = "Kasparov"; // Default name
  white = true;
}

// Accessors
string Player::getName() {
  return name;
}
bool Player::getWhite() {
  return white;
}
    
// Mutators
void Player::setName(string n) {
  name = n;
}
void Player::setWhite(bool w) {
  white = w;
}

/////////////////////
//                 //
//   class Board   //
//                 //
/////////////////////

// Constructor
Board::Board() {
  Piece tempPiece; // temporary piece for initialization of cell
  vector<Cell> newRow = {}; // making rows
  board.push_back(newRow); // 0 index
  for (int i = 1; i <= 8; i++) { // 1 to 8 to make ranks easier
    board.push_back(newRow); // add the rank
    for (int j = 1; j <= 8; j++) { // loop through files a-h
      Cell newCell(j, i, tempPiece); // make a piece with the current file/rank
      board[i].push_back(newCell); // add to board
    }
  }
}

// Accessors
Cell Board::getCell(int rank, int file) {
  return board[file][rank]; // -1 to keep 1-8 in the rest of the code
}

//////////////////////
//                  //
//    class Game    //
//                  //
//////////////////////

// Constructor
bool Game::whiteInCheck = false;
bool Game::blackInCheck = false;
bool Game::whiteInCheckmate = false;
bool Game::blackInCheckmate = false;
bool Game::whiteInStalemate = false;
bool Game::blackInStalemate = false;

Game::Game() {

}

// Accessors
Player Game::getPlayer(int input) {
  if (input == 1) {
    return Player1;
  } 
  else {
    return Player2;
  }
}
bool Game::getWhiteInCheck() {
  return whiteInCheck;
}
bool Game::getBlackInCheck() {
  return blackInCheck;
}
bool Game::getWhiteInCheckmate() {
  return whiteInCheckmate;
}
bool Game::getBlackInCheckmate() {
  return blackInCheckmate;
}
bool Game::getWhiteInStalemate() {
  return whiteInStalemate;
}
bool Game::getBlackInStalemate() {
  return blackInStalemate;
}

// Mutators
void Game::setNames() {
  string tempName;
  cout << "Enter White's name: ";
  cin >> tempName;
  Player1.setName(tempName.substr(0,20));
  cout << "\nEnter Black's name: ";
  cin >> tempName;
  if (tempName == Player1.getName()) { // if same name add (1)
    tempName.substr(0,20)+="(1)";
  }
  cout << endl;
  Player2.setName(tempName);
}
void Game::setWhiteInCheck(bool input) {
  whiteInCheck = input;
}
void Game::setBlackInCheck(bool input) {
  blackInCheck = input;
}
void Game::setWhiteInCheckmate(bool input) {
  whiteInCheckmate = input;
}
void Game::setBlackInCheckmate(bool input) {
  blackInCheckmate = input;
}
void Game::setWhiteInStalemate(bool input) {
  whiteInStalemate = input;
}
void Game::setBlackInStalemate(bool input) {
  blackInStalemate = input;
}


///////////////////////////
//                       //
//    Turn processors    //
//                       //
///////////////////////////

int Game::processTurn1() { // should take input for white process them
  string p1Initial, p1Final;
  bool validInput = false;
  int validInputPawn = 0;
  updateState();
  
  while (validInput == false) { // Loop while input is invalid
    validInput = true; // Set to true, and turn false if something goes wrong
    cout << Player1.getName() << "'s turn. Enter the square on which the piece you wish to move is located: ";
    cin >> p1Initial;
    if (p1Initial == "resign") return 1;
    if (p1Initial == "draw") {
      string input;
      cout << getPlayer(1).getName() << " has requested a draw. Accept? Y/n: ";
      cin >> input;
      if (input.substr(0, 1) == "Y" || input.substr(0, 1) == "y") {
        return 2;
      } 
      else {
        cout << "Draw declined." << endl;
        validInput = false;
        continue;
      }
    }
    cout <<"\nEnter the square where you want to move this piece: ";
    cin >> p1Final;
    for (int i = 0; i < p1Initial.length(); i++) {
      cout << "loop to break down string" << endl;
      p1Initial[i] = tolower(p1Initial[i]);
      p1Final[i] = tolower(p1Final[i]);
    }
    int curFile = (int) (p1Initial[0] - 96);
    cout<< "you're trying to move a " << chessBoard.find(p1Initial)->second.getPiece().getType() << " from " << p1Initial<< " to " << p1Final << endl;
    try {
      Cell selectedCell = chessBoard.find(p1Initial)->second;
      Piece curPiece = selectedCell.getPiece();
      // cout << "white is playing a " << curPiece.getWhite() << " piece (1 = w, 0 = b)" << endl;
      if (curPiece.getWhite() == false) { // White playing black's pieces
        // cout << "that's not your piece" << endl;
        validInput = false;
      }
      else {
        switch (curPiece.getType()) {
          case 'p': {
            Pawn curPawn = convertToPawn(curPiece);
            validInputPawn = curPawn.validMove(p1Initial, p1Final);
            if (validInputPawn == 0) { // if invalid pawn move
              validInput = false;
            }
            break;
          }
          case 'n': {
            Knight curKnight = convertToKnight(curPiece);
            validInput = curKnight.validMove(p1Initial, p1Final);
            break;  
          }
          case 'b': {
            Bishop curBishop = convertToBishop(curPiece);
            validInput = curBishop.validMove(p1Initial, p1Final);
            break;
          }
          case 'r': {
            Rook curRook = convertToRook(curPiece);
            validInput = curRook.validMove(p1Initial, p1Final);
            break;
          }  
          case 'q': {
            Queen curQueen = convertToQueen(curPiece);
            validInput = curQueen.validMove(p1Initial, p1Final);
            break;
          }
          case 'k': {
            King curKing = convertToKing(curPiece);
            validInput = curKing.validMove(p1Initial, p1Final);
            break;
          }
          default: { // Player didn't move any of the previous pieces
            cout << "default Invalid Move.\n"; // Invalid by default
            validInput = false;
            continue;
          }
        }
      }
      if (validInput == true || validInputPawn != 0) {
        // Moving the piece // Create new cell
        bool moveFlag = chessBoard.find(p1Initial)->second.getPiece().getHasMoved();
        Piece tempPiece = chessBoard.find(p1Final)->second.getPiece(); // store piece if illegal move
        chessBoard.find(p1Final)->second.setPiece(selectedCell.getPiece()); // Move piece to new cell
        chessBoard.find(p1Final)->second.getPiece().setHasMoved(true);
        Piece blankPiece = Piece(); // replace moved piece with empty square
        chessBoard.find(p1Initial)->second.setPiece(blankPiece);
        updateState();
        if (getWhiteInCheck() == true) { // illegal move, as it put white in check
          cout << "illegal move, puts white in check" << endl;
          chessBoard.find(p1Initial)->second.setPiece(chessBoard.find(p1Final)->second.getPiece()); // put piece back
          chessBoard.find(p1Initial)->second.getPiece().setHasMoved(moveFlag); // Set has moved to what it was before this turn
          chessBoard.find(p1Final)->second.setPiece(tempPiece); // Put back the original piece
          validInput = false;
          updateState(); // re-update
        }
      }
      else {
        cout << "invalid, validInput = false\n";
        validInput = false;
        continue;
      }
    } catch (...) {
        cout << "invalid, caught error.\n";
        validInput = false;
    }
  }
  return 0; // no problems, move on as usual
}

int Game::processTurn2() { // should take input for black process them
  string p2Initial, p2Final;
  bool validInput = false;
  int validInputPawn = 0;
  updateState();
  
  while (validInput == false) { // Loop while input is invalid
    validInput = true; // Set to true, and turn false if something goes wrong
    cout << Player2.getName() << "'s turn. Enter the square on which the piece you wish to move is located: ";
    cin >> p2Initial;
    if (p2Initial == "resign") return 1;
    if (p2Initial == "draw") {
      string input;
      cout << getPlayer(2).getName() << " has requested a draw. Accept? Y/n: ";
      cin >> input;
      if (input.substr(0) == "Y" || input.substr(0) == "y") {
        return 2;
      } 
      else {
        cout << "Draw declined." << endl;
        validInput = false;
        continue;
      }
    }
    cout <<"\nEnter the square where you want to move this piece: ";
    cin >> p2Final;
    for (int i = 0; i < p2Initial.length(); i++) {
      p2Initial[i] = tolower(p2Initial[i]);
      p2Final[i] = tolower(p2Final[i]);
    }
    try {
      Cell selectedCell = chessBoard.find(p2Initial)->second;
      Piece curPiece = selectedCell.getPiece();
      // cout << "black is playing a " << curPiece.getWhite() << " piece (1 = w, 0 = b)" << endl;
      if (curPiece.getWhite() == true) { // Black playing white's pieces
        // cout << "that's not your piece" << endl;
        validInput = false;
      }
      else {
        switch (curPiece.getType()) {
          case 'p': {
            Pawn curPawn = convertToPawn(curPiece);
            validInputPawn = curPawn.validMove(p2Initial, p2Final);
            if (validInputPawn == 0) { // if invalid pawn move
              validInput = false;
            }
            break;
          }
          case 'n': {
            Knight curKnight = convertToKnight(curPiece);
            validInput = curKnight.validMove(p2Initial, p2Final);
            break;  
          }
          case 'b': {
            Bishop curBishop = convertToBishop(curPiece);
            validInput = curBishop.validMove(p2Initial, p2Final);
            break;
          }
          case 'r': {
            Rook curRook = convertToRook(curPiece);
            validInput = curRook.validMove(p2Initial, p2Final);
            break;
          }  
          case 'q': {
            Queen curQueen = convertToQueen(curPiece);
            validInput = curQueen.validMove(p2Initial, p2Final);
            break;
          }
          case 'k': {
            King curKing = convertToKing(curPiece);
            validInput = curKing.validMove(p2Initial, p2Final);
            break; 
          }
          default: { // Player didn't move any of the previous pieces
            cout << "Invalid Move.\n"; // Invalid by default
            validInput = false;
          }
        }
      }
      if (validInput == true || validInputPawn != 0) {
        // Moving the piece // Create new cell
        bool moveFlag = chessBoard.find(p2Initial)->second.getPiece().getHasMoved();
        Piece tempPiece = chessBoard.find(p2Final)->second.getPiece(); // Store the piece in case the move is illegal 
        chessBoard.find(p2Final)->second.setPiece(selectedCell.getPiece()); // Move piece to new cell
        chessBoard.find(p2Final)->second.getPiece().setHasMoved(true);
        Piece blankPiece = Piece(); // replace moved piece with empty square
        chessBoard.find(p2Initial)->second.setPiece(blankPiece);
        updateState();
        //selectedCell.setPiece(blankPiece); // Delete the piece from initial cell
        if (getBlackInCheck() == true) { // illegal move, as it put black in check
          cout << "illegal move, puts black in check" << endl;
          chessBoard.find(p2Initial)->second.setPiece(chessBoard.find(p2Final)->second.getPiece()); // put piece back
          chessBoard.find(p2Initial)->second.getPiece().setHasMoved(moveFlag); 
          chessBoard.find(p2Final)->second.setPiece(tempPiece); // Put back the original piece
          validInput = false;
          updateState(); // re-update
        }
      }
      else {
        cout << "invalid, validInput = false\n";
        validInput = false;
        continue;
      }
    } catch (...) {
        cout << "Invalid Move.\n";
        validInput = false;
    }
  }
  return 0;
}

// Update state of kings and game
void Game::updateState() { 
  string blackKingSquare, whiteKingSquare;
  bool whiteFlag, blackFlag; // Haha white Flag Surrender
  for (char i = 'a'; i <= 'h'; i++) { // find the kings
    for (int j = 1; j <= 8; j++) {
      string tempSquare(1, i);
      tempSquare += to_string(j);
      //cout << "checking " << tempSquare << endl;
      Piece curPiece = chessBoard.find(tempSquare)->second.getPiece();
      if (curPiece.getType() == 'k') {
        if (curPiece.getWhite() == true) {
          whiteKingSquare = tempSquare;
          cout << "White king on: " << whiteKingSquare << endl;
        }
        else {
          blackKingSquare = tempSquare;
          cout << "Black King on " << blackKingSquare << endl;
        }
      }
    }
  }
  for (char i = 'a'; i <= 'h'; i++) {
    for (int j = 1; j <= 8; j++) {
      string tempSquare(1, i);
      tempSquare += to_string(j);
      Piece curPiece = chessBoard.find(tempSquare)->second.getPiece();
      bool curPieceColor = curPiece.getWhite();
      switch(curPiece.getType()) {
        case 'p': {
          Pawn tempPawn = convertToPawn(curPiece);
          if (curPieceColor == true) {
            if (tempPawn.validMove(tempSquare, blackKingSquare) == 3) { // if pawn can CAPTURE (not just move)
              setBlackInCheck(true);
              blackFlag = true;
              cout << "White Pawn Check" << endl;
            }
          }
          else {
            if (tempPawn.validMove(tempSquare, whiteKingSquare) == 3) {
              setWhiteInCheck(true);
              whiteFlag = true;
              cout << "Black Pawn Check" << endl;
            }
          }
          break;
        }
        case 'n': {
          Knight tempKnight = convertToKnight(curPiece);
          if (curPieceColor == true) {
            if (tempKnight.validMove(tempSquare, blackKingSquare) == true) {
              setBlackInCheck(true);
              blackFlag = true;
              cout << "White knight check" << endl;
            }
          }
          else {
            if (tempKnight.validMove(tempSquare, whiteKingSquare) == true) {
              setWhiteInCheck(true);
              whiteFlag = true;
              cout << "Black knight check" << endl;
            }
          }
          break;
        }
        case 'b': {
          Bishop tempBishop = convertToBishop(curPiece);
          if (curPieceColor == true) {
            if (tempBishop.validMove(tempSquare, blackKingSquare) == true) {
              setBlackInCheck(true);
              blackFlag = true;
              cout << "White Bishop Check" << endl;
            }
          } 
          else {
            if (tempBishop.validMove(tempSquare, whiteKingSquare) == true) {
              setWhiteInCheck(true);
              whiteFlag = true;
              cout << "Black Bishop Check" << endl;
            }
          }
          break;
        }
        case 'r': {
          Rook tempRook = convertToRook(curPiece);
          if (curPieceColor == true) {
            if (tempRook.validMove(tempSquare, blackKingSquare) == true) {
              setBlackInCheck(true);
              blackFlag = true;
              cout << "White Rook Check" << endl;
            }
          } 
          else {
            if (tempRook.validMove(tempSquare, whiteKingSquare) == true) {
              setWhiteInCheck(true);
              whiteFlag = true;
              cout << "Black Rook Check" << endl;
            }
          }
          break;
        }  
        case 'q': {
          Queen tempQueen = convertToQueen(curPiece);
          if (curPieceColor == true) {
            if (tempQueen.validMove(tempSquare, blackKingSquare) == true) {
              setBlackInCheck(true);
              blackFlag = true;
              cout << "White Queen Check" << endl;
            }
          } 
          else {
            if (tempQueen.validMove(tempSquare, whiteKingSquare) == true) {
              setWhiteInCheck(true);
              whiteFlag = true;
              cout << "Black Queen Check" << endl;
            }
          }
          break;
        }
        default: {
          //cout << "No checks detected" << endl;
          break;
        }
      }
    }
  }
  if (!whiteFlag) setWhiteInCheck(false); // reset flags
  if (!blackFlag) setBlackInCheck(false);
}

void Game::mateCheck(bool colour) { // stalemate and checkmate
  bool hasValidMoves = false;
  for (char i = 'a'; i <= 'h'; i++) {
    for (int j = 1; j <= 8; j++) {
      string tempSquare1(1, i);
      tempSquare1 += to_string(j);
      Piece tempPiece = chessBoard.find(tempSquare1)->second.getPiece();
      cout << "piece on " << tempSquare1 << " is a " << tempPiece.getWhite() << " " << tempPiece.getType() << endl;
      if (tempPiece.getWhite() == colour && tempPiece.getType() != 'x') {
        for (char m = 'a'; m <= 'h'; m++) {
          for (int n = 1; n <= 8; n++) {
            Piece curPiece = tempPiece;
            string tempSquare2(1, m);
            tempSquare2 += to_string(n);
            cout << curPiece.getType() << " on " << tempSquare1 << " moving to " << tempSquare2 << ": ";
            switch(curPiece.getType()) {
              case 'p': {
                Pawn curPawn = convertToPawn(curPiece);
                if (curPawn.validMove(tempSquare1, tempSquare2) != 0) {
                  cout << "Pawn move" << endl;
                  hasValidMoves = true;
                }
                break;
              }
              case 'n': {
                Knight curKnight = convertToKnight(curPiece);
                if (curKnight.validMove(tempSquare1, tempSquare2)) {
                  cout << "Knight move" << endl;
                  hasValidMoves = true;
                }
                break;
              }
              case 'b': {
                Bishop curBishop = convertToBishop(curPiece);
                if (curBishop.validMove(tempSquare1, tempSquare2)) {
                  cout << "bishop move" << endl;
                  hasValidMoves = true;
                }
                break;
              }
              case 'r': {
                Rook curRook = convertToRook(curPiece);
                if (curRook.validMove(tempSquare1, tempSquare2)) {
                  cout << "Rook move" << endl;
                  hasValidMoves = true;
                }
                break;
              }  
              case 'q': {
                Queen curQueen = convertToQueen(curPiece);
                if (curQueen.validMove(tempSquare1, tempSquare2)) {
                  cout << "Queen move" << endl;
                  hasValidMoves = true;
                }
                break;
              }
              case 'k': {
                King curKing = convertToKing(curPiece);
                if (curKing.validMove(tempSquare1, tempSquare2)) {
                  cout << "King move" << endl;
                  hasValidMoves = true;
                }
                break;
              }
              default: { // didn't match to a piece
                cout << "error, invalid piece"; // Invalid by default
              }
            }
            cout << endl;
            if (hasValidMoves) break;
          }
          if (hasValidMoves) break;
        }
        if (hasValidMoves) break;
      }
      if (hasValidMoves) break;
    }
    if (hasValidMoves) break;
  }
  cout << "hasValidMoves is " << hasValidMoves << endl;
  if (!hasValidMoves) {
    if (colour == true) {
      if (whiteInCheck == true) {
        cout << "Checkmate." << endl;
        setWhiteInCheckmate(true);
      } 
      else {
        cout << "Stalemate." << endl;
        setWhiteInStalemate(true);
      }
    }
    else if (colour == false) {
      if (blackInCheck == true) {
        cout << "Checkmate." << endl;
        setBlackInCheckmate(true);
      } 
      else {
        cout << "Stalemate." << endl;
        setBlackInStalemate(true);
      }
    }
  }
}