// Classes for different types of pieces, cells on the board, methods

#include <iostream>
#include <stdlib.h>
#include <cstdlib> // abs()
#include <cctype> // tolower()
#include "include/main.hpp"
using namespace std;

/////////////////////
//                 //
//   class Piece   //
//                 //
///////////////////// 

// Constructors
Piece::Piece() { // default (empty cell)
  white = true;
  type = 'x';
  hasMoved = false;
}
Piece::Piece(bool isWhite, char pieceType, bool moved) {
  white = isWhite;
  type = pieceType;
  hasMoved = moved;
}

// Accessors
bool Piece::getWhite() {
  return white;
}
char Piece::getType() {
  return type;
}
bool Piece::getHasMoved() {
  return hasMoved;
}

// Mutators
void Piece::setWhite(bool newColour) {
  white = newColour;
}
void Piece::setType(char newType) {
  //cout << "changed from " << type;
  type = newType;
  //cout << " to " << type << endl;
}
void Piece::setHasMoved(bool moved) {
  hasMoved = moved;
}

/*bool Piece::validMove(string initialSquare, string finalSquare) {
  return true;
}*/
//////////////////////
//                  //
//    class Cell    //
//                  //
//////////////////////
// The squares on the chessboard

// Constructors
Cell::Cell(int f, int r, Piece p) {
  file = f;
  rank = r;
  piece = p;
}

// Accessors for each variable
int Cell::getFile() {
  return file;
}
int Cell::getRank(){
  return rank;
}
Piece& Cell::getPiece() {
  return piece;
}
    
// Mutators
void Cell::setPiece(Piece newPiece) {
  piece = newPiece;
}

//////////////////////
//                  //
//    class Pawn    //
//                  //
//////////////////////

// Constructor
Pawn::Pawn(bool isWhite, bool moved) {
  white = isWhite;
  type = 'p';
  hasMoved = moved;
}

// Accessors
bool Pawn::getHasMoved() {
  return hasMoved;
}

// Mutator
void Pawn::setHasMoved(bool input) {
  hasMoved = input;
}

// Move Validation
// return 0 = invalid, 1 = valid 1 square move, 2 = valid 2 square move, 3 = valid capture
int Pawn::validMove(string initialSquare, string finalSquare) { 
  int initialFile = (int) (tolower(initialSquare[0])); // breaking down into characters/numbers
  int initialRank = initialSquare[1]; 
  int finalFile = (int) (tolower(finalSquare[0])); // char > lowercase char > ascii value
  int finalRank = finalSquare[1] - 48;
  int dist = 2; // assume that it hasn't moved yet
  int tempRank;
  string tempSquare;
  // cout << "variables initialized\n";
  Cell initialCell = chessBoard.find(initialSquare)->second; // find the starting and ending cells for the move
  Cell finalCell = chessBoard.find(finalSquare)->second;
  Pawn p = convertToPawn(initialCell.getPiece());
  int rankChange = finalRank - initialRank + 48; // difference in rank (vertical movement)
  int fileChange = finalFile - initialFile; // difference in file (horizontal movement)
  // cout << "finalRank: " << finalRank << endl;
  // cout << "finalFile: " << finalFile << endl;
  // cout << "rankChange: " << rankChange << endl;
  // cout << "fileChange: " << fileChange << endl;
  // moving outside of board
  if (finalRank < 1 || finalRank > 8) return 0;
  if (finalFile < 97 || finalFile > 104) return 0;
  // cout << "Not invalid\n";
  // if already moved, pawn can only go one square
  //cout << "pawn has moved is " << p.Pawn::getHasMoved() << endl;
  if ((p.Pawn::getHasMoved() == true)) {
    dist = 1;
    //cout << "already moved" << endl;
  }
  
  if (fileChange == 0) { // if no horizontal movement, then only forwards
    // cout << "filechange = 0" << endl;
    if (p.Pawn::getWhite() == true) { // White pawn
      // //cout << "white pawn" << endl;
      if (rankChange <= dist && rankChange > 0) { // moving <= dist, while still moving somewhere
        for (int i = 1; i <= rankChange; i++) { // check every square between initial and final
          // tempRank = initialRank + i; // turns rank = 2 into rank = 3
          string tempRank(1, (char) (initialRank + i));
          string tempFile(1, (char) (initialFile));
          tempSquare = (tempFile) + (tempRank); // converts back to coordinate form (e3)
          // cout << "tempSquare: " << tempSquare << endl;
          Cell tempCell = chessBoard.find(tempSquare)->second; // checks that new square
          if (tempCell.getPiece().getType() != 'x') {
            // cout << "can't move, occupied by " << tempCell.getPiece().getType() << endl;
            return 0; // if it's NOT empty, return false (invalid)
          } 
        }
        //cout << "valid move" << endl;
        // valid move
        return rankChange; // Return either 1 or 2
      }
    }
    else { // Black pawn (similar logic)
      rankChange = -rankChange; // Black pawns are expected to move down, so we make this the opposite sign
      if (rankChange <= dist && rankChange > 0) { // moving <= dist, while still moving somewhere
        for (int i = 1; i <= rankChange; i++) { // check every square between initial and final
          string tempRank(1, (char) (initialRank - i));
          string tempFile(1, (char) (initialFile));
          tempSquare = (tempFile) + (tempRank); // converts back to coordinate form (e3)
          //cout << "tempSquare: " << tempSquare << endl;
          Cell tempCell = chessBoard.find(tempSquare)->second; // checks that new square
          if (tempCell.getPiece().getType() != 'x') {
            //cout << "can't move, occupied by " << tempCell.getPiece().getType() << endl;
            return 0; // if it's NOT empty, return false (invalid)
          }
        }
        // valid move
        return rankChange; // Return either 1 or 2
      }
    }
  } else if (abs(fileChange) == 1) { // only possible horizontal movement is with captures (1 space)
    if (p.Pawn::getWhite() == false) rankChange = -rankChange;
    if (rankChange == 1) { // capturing is only diagonal
      if ((finalCell.getPiece().getType() != 'x') &&(finalCell.getPiece().getWhite() != initialCell.getPiece().getWhite())) { // capture
        return 3;
      }
      else {
        // Check for en passant
        // return enPassantCheck(initialSquare, initialCell, finalRank);
      }
    }
  }
  return 0; // invalid move
}

//////////////////////
//                  //
//   class Knight   //
//                  //
//////////////////////

// Constructors
Knight::Knight(bool isWhite) {
  white = isWhite;
  type = 'n';
}

bool Knight::validMove(string initialSquare, string finalSquare) { // input is something like e2 to f4
  int initialFile = (int) (tolower(initialSquare[0])); // breaking down into characters/numbers
  int initialRank = initialSquare[1]; 
  int finalFile = (int) (tolower(finalSquare[0])); // char > lowercase char > ascii value
  int finalRank = finalSquare[1] - 48;
    
  Cell initialCell = chessBoard.find(initialSquare)->second; // find the starting and ending cells for the move
  Cell finalCell = chessBoard.find(finalSquare)->second;

  int rankChange = abs(finalRank - initialRank + 48); // difference in rank (vertical movement)
  int fileChange = abs(finalFile - initialFile); // difference in file (horizontal movement)
  /*
  cout << "finalRank: " << finalRank << endl;
  cout << "finalFile: " << finalFile << endl;
  cout << "rankChange: " << rankChange << endl;
  cout << "fileChange: " << fileChange << endl;*/
  
  // moving outside of board  
  if (finalRank < 1 || finalRank > 8) return false;
  // moving outside of board (ASCII edition, a-h)
  if (finalFile < 97 || finalFile > 104) return false;
  /*cout << "not outside of the board" << endl;*/
  
  if ((rankChange == 1 && fileChange == 2) || (rankChange == 2 && fileChange == 1)) { // Valid knight move (L shape)
    if (finalCell.getPiece().getType() == 'x') { // if it's moving to an empty square, it's valid
      /*cout << "moving to empty square" << endl;*/
      return true;
    } else if (initialCell.getPiece().getWhite() != finalCell.getPiece().getWhite()) { // if it's moving to enemy piece, it's valid
      /*cout << "knight capture" << endl;*/
      return true; 
    }
  } 
  //cout << "invalid move" << endl;
  return false; // If it didn't return true already, it's not valid so return false
}

//////////////////////
//                  //
//   class Bishop   //
//                  //
//////////////////////

// Constructors
Bishop::Bishop(bool isWhite) {
  white = isWhite;
  type = 'b';
}

bool Bishop::validMove(string initialSquare, string finalSquare) {
  //Very similar logic to Knight::validMove
  int initialFile = (int) (tolower(initialSquare[0]));
  int initialRank = initialSquare[1]; 
  int finalFile = (int) (tolower(finalSquare[0]));
  int finalRank = finalSquare[1] - 48;
  string tempSquare;

  Cell initialCell = chessBoard.find(initialSquare)->second;
  Cell finalCell = chessBoard.find(finalSquare)->second;

  // Note the lack of abs() here; we need to know which
  // way the bishop is moving
  int rankChange = finalRank - initialRank + 48;
  int fileChange = finalFile - initialFile;
/*
  cout << "finalRank: " << finalRank << endl;
  cout << "finalFile: " << finalFile << endl;
  cout << "rankChange: " << rankChange << endl;
  cout << "fileChange: " << fileChange << endl;*/
  
  // Check if coordinates are within the board 
  if (finalRank < 1 || finalRank > 8) return false;
  if (finalFile < 97 || finalFile > 104) return false;
  //cout << "not outside of the board" << endl;
  
  if ((abs(rankChange) == abs(fileChange)) && (rankChange != 0)) { // Valid bishop move
    // Check if there are pieces between the starting and ending
    // positions (here, the logic is similar to pawn movement)
    //cout << "moving diagonally" << endl;
    // No need to check the last square, we'll do that afterwards
    for (int i = 1; i < abs(rankChange); i++) { // Check every square between initial and final
      if (rankChange < 0) {
        i = -i;
        // string tempStr(1, (char) (initialRank + i));
        // tempRank = tempStr;
        // tempSquare = (tempFile) + (tempRank); // converts back to coordinate form (e3)
        // tempRank = initialRank - i;
      }
      string tempRank(1, (char) (initialRank + i));
      i = abs(i);

      if (fileChange < 0) {
        i = -i;
      }

      string tempFile(1, (char) (initialFile + i));
      i = abs(i);

      //cout << "tempRank " << tempRank << " tempFile " << tempFile << endl;
      
      tempSquare = tempFile + tempRank; // Converts back to coordinate form
      Cell tempCell = chessBoard.find(tempSquare)->second; // checks that new square
      if (tempCell.getPiece().getType() != 'x') {
        //cout << "can't move, occupied by " << tempCell.getPiece().getType() << endl;
        return false; // if it's NOT empty, return false (invalid)
      }
    }

    // The final square doesn't have to be empty, but we make
    // the same check as Knight to ensure the final square is
    // either empty or an opponent piece
    if (finalCell.getPiece().getType() == 'x') {
      return true;
    } else if (initialCell.getPiece().getWhite() != finalCell.getPiece().getWhite()) {
      return true;
    }
  } 
  return false; // If it didn't return true already, it's not valid so return false
}

//////////////////////
//                  //
//    class Rook    //
//                  //
//////////////////////

// Constructor
Rook::Rook(bool isWhite, bool moved) {
  white = isWhite;
  type = 'r';
  hasMoved = moved;
}

// Accessors
bool Rook::getHasMoved() {
  return hasMoved;
}

bool Rook::validMove(string initialSquare, string finalSquare) {
  int initialFile = (int) (tolower(initialSquare[0]));
  int initialRank = initialSquare[1]; 
  int finalFile = (int) (tolower(finalSquare[0]));
  int finalRank = finalSquare[1] - 48;
  int tempRank, tempFile;
  string tempSquare;
  
  Cell initialCell = chessBoard.find(initialSquare)->second;
  Cell finalCell = chessBoard.find(finalSquare)->second;

  // Note the lack of abs() here; we need to know which
  // way the rook is moving
  int rankChange = finalRank - initialRank + 48;
  int fileChange = finalFile - initialFile;

  // Moving out of the board is not allowed
  if (finalRank < 1 || finalRank > 8) return false; 
  if (finalFile < 97 || finalFile > 104) return false;

  // If it's not moving up and down, has to be left to right
  if (rankChange == 0) { 
    string tempRank(1, initialRank); // can use any rank value since it's not changing
    if (initialFile != finalFile) { // Making sure it moves somewhere
      for (int i = 1; i < abs(fileChange); i++) {
        if (fileChange < 0) {
          i = -i; // moving left, so subtract by i instead of adding
        }
        // add i to coordinate each time
        string tempFile(1, (char) (initialFile + i));
        i = abs(i);
        tempSquare = tempFile + tempRank; // Converts back to coordinate form
        Cell tempCell = chessBoard.find(tempSquare)->second; // checks that new square
        if (tempCell.getPiece().getType() != 'x') {
          //cout << "can't move, occupied by " << tempCell.getPiece().getType() << endl;
          return false; // if it's NOT empty, return false (invalid)
        }
      }
    }
  } else if (fileChange == 0) { // Same logic here
    string tempFile(1, initialFile); // can use any file value since it's not changing
    if (initialRank != finalRank) {
      for (int i = 1; i < abs(rankChange); i++) {
        if (rankChange < 0) {
          i = -i; // moving down, so subtract by i instead of adding
        }
        string tempRank(1, (char) (initialRank + i));
        i = abs(i);
        tempSquare = tempFile + tempRank; // Converts back to coordinate form
        Cell tempCell = chessBoard.find(tempSquare)->second; // checks that new square
        if (tempCell.getPiece().getType() != 'x') {
          //cout << "can't move, occupied by " << tempCell.getPiece().getType() << endl;
          return false; // if it's NOT empty, return false (invalid)
        }
      }
    }
  } else {
    return false; // Rooks can only move straight
  }
  if (finalCell.getPiece().getType() == 'x') { // If final square is empty
      return true;
      // If the rook is capturing a piece on the final square
  } else if (initialCell.getPiece().getWhite() != finalCell.getPiece().getWhite()) { 
    return true;
  }
  return false; // Hasn't been true yet, so it has to be false
}

///////////////////////
//                   //
//    class Queen    //
//                   //
///////////////////////

// Constructor
Queen::Queen(bool isWhite) {
  white = isWhite;
  type = 'q';
}

bool Queen::validMove(string initialSquare, string finalSquare) {
  Bishop b(getWhite());
  Rook r(getWhite(), true);
  if ((b.validMove(initialSquare, finalSquare)) || (r.validMove(initialSquare, finalSquare))) {
    return true; // A queen can move somewhere if either a bishop or rook can
  }
  return false;
}

//////////////////////
//                  //
//    class King    //
//                  //
//////////////////////

// Constructor
King::King(bool isWhite, bool moved) {
  white = isWhite;
  type = 'k';
  hasMoved = moved;
}

// Accessor
bool King::getHasMoved() {
  return hasMoved;
}

bool King::validMove(string initialSquare, string finalSquare) {
  //Very similar logic to Knight::validMove

  int initialFile = (int) (tolower(initialSquare[0]));
  int initialRank = initialSquare[1]; 
  int finalFile = (int) (tolower(finalSquare[0]));
  int finalRank = finalSquare[1] - 48;

  Cell initialCell = chessBoard.find(initialSquare)->second;
  Cell finalCell = chessBoard.find(finalSquare)->second;

  int rankChange = abs(finalRank - initialRank + 48);
  int fileChange = abs(finalFile - initialFile);

  //Check if coordinates are within the board
  if (finalRank < 1 || finalRank > 8) return false;
  if (finalFile < 97 || finalFile > 104) return false;
  
  if ((rankChange <= 1 && fileChange <= 1) && (rankChange != 0 || fileChange != 0)) { // Valid king move
    // Check validity
    if (finalCell.getPiece().getType() == 'x') {
      return true;
    } else if (initialCell.getPiece().getWhite() != finalCell.getPiece().getWhite()) {
      return true; 
    }
  }
  else if ((fileChange == 2) && (rankChange == 0)) {
    cout << "castling detected" << endl;
    // Castling
    return castlingCheck(initialSquare, finalSquare, initialCell, finalCell);
  }
  return false; // If it didn't return true already, it's not valid so return false
}

/////////////////////////
//  Converter methods  //
/////////////////////////

// These methods convert from a Piece to any specific piece

Pawn convertToPawn(Piece input) {
  Pawn p(input.getWhite(), input.getHasMoved());
  //cout << "converted to pawn with " << input.getWhite() << " colour; it has/hasn't (" << input.getHasMoved() << ") moved" << endl;
  return p;
}

Knight convertToKnight(Piece input) {
  Knight n(input.getWhite());
  return n;
}

Bishop convertToBishop(Piece input) {
  Bishop b(input.getWhite());
  return b;
}

Rook convertToRook(Piece input) {
  Rook r(input.getWhite(), input.getHasMoved());
  return r;
}

Queen convertToQueen(Piece input) {
  Queen q(input.getWhite());
  return q;
}

King convertToKing(Piece input) {
  King k(input.getWhite(), input.getHasMoved());
  return k;
}