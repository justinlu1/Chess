#include <iostream>
#include "include/main.hpp"

using namespace std;

bool castlingCheck(string initialSquare, string finalSquare, Cell initialCell, Cell finalCell) {
  // This string array represents the squares that cannot
  // be attacked if a king is to castle
  string kingSquares[4][2] = {{"f1", "g1"}, {"d1", "c1"}, {"f8", "g8"}, {"d8", "c8"}};
  Piece king, rook;

  if ((initialSquare == "e1") && (initialCell.getPiece().getWhite()) && (initialCell.getPiece().getType() == 'k')) {
    if (finalSquare == "g1") {
      cout << "Kingside" << endl;
      king = initialCell.getPiece();
      rook = chessBoard.find("h1")->second.getPiece();
      
      // Ensure that the rook is white (king starting on e1)
      if (!rook.getWhite()) {
        cout << "not white" << endl;
        return false;
        } // not same color of rook
      if (rook.getType() != 'r') { // not a rook
        cout << "not a rook" << endl;
        return false;
        }

      // Make sure all squares between king and rook are empty
      if ((chessBoard.find("f1")->second.getPiece().getType() != 'x') || (chessBoard.find("g1")->second.getPiece().getType() != 'x')) {
        cout<<"Piece is in the way"<<endl;
        return false;
      }
      // Can't castle if king or rook have moved
      if ((king.getHasMoved()) || (rook.getHasMoved())) {
        cout << "already moved" << endl;
        return false;
      } 

      if (Game::getWhiteInCheck()) {
        cout << "can't castle, you're in check" << endl; 
        return false;
      }

      cout << "ready to check square safety"  << endl;
      for (int i = 0; i < 2; i++) { // moves king over square by square, checking if check
        // Bring king to kingSquares[0][i] (white kingside castle)
        chessBoard.find(kingSquares[0][i])->second.setPiece(initialCell.getPiece()); // Move piece to new cell
        Piece blankPiece = Piece(); // replace moved piece with empty square
        if (i == 0) {
          chessBoard.find("e1")->second.setPiece(blankPiece);
        }
        else {
          chessBoard.find("f1")->second.setPiece(blankPiece);
        }
        Game::updateState();
        cout << "white is in check? " << Game::getWhiteInCheck() << endl;
        if (Game::getWhiteInCheck()) {
          cout << "no castling bc white is in check on " << kingSquares[0][i] << endl;
          // Square is attacked, so can't castle
          chessBoard.find("e1")->second.setPiece(chessBoard.find(kingSquares[0][i])->second.getPiece());
          Piece blankPiece = Piece(); // replace king with empty square
          chessBoard.find(kingSquares[0][i])->second.setPiece(blankPiece);
          Game::updateState(); // re-update state, king no longer in check
          return false;
        }
      }
      // King is now on g1 and castling is valid since we made it through the loop
      // Must move rook from h1 to f1
      chessBoard.find("f1")->second.setPiece(chessBoard.find("h1")->second.getPiece());
      Piece blankPiece = Piece(); // replace moved piece with empty square
      chessBoard.find("h1")->second.setPiece(blankPiece);
      return true;
    }
    else if (finalSquare == "c1") {
      cout<<"queenside"<<endl;
      king = initialCell.getPiece();
      rook = chessBoard.find("a1")->second.getPiece();
      
      // Ensure that the rook is white (king starting on e1)
      if (!rook.getWhite()) {
        cout << "not white" << endl;
        return false;
        } // not same color of rook
      if (rook.getType() != 'r') { // not a rook
        cout << "not a rook" << endl;
        return false;
        }

      // Make sure all squares between king and rook are empty
      if ((chessBoard.find("b1")->second.getPiece().getType() != 'x') || (chessBoard.find("c1")->second.getPiece().getType() != 'x') || (chessBoard.find("d1")->second.getPiece().getType() != 'x')) {
        cout<<"Piece is in the way"<<endl;
        return false;
      }
      // Can't castle if king or rook have moved
      if ((king.getHasMoved()) || (rook.getHasMoved())) {
        cout << "already moved" << endl;
        return false;
      } 

      if (Game::getWhiteInCheck()) {
        cout << "can't castle, you're in check" << endl; 
        return false;
      }

      cout << "ready to check square safety"  << endl;
      for (int i = 0; i < 2; i++) { // moves king over square by square, checking if check
        // Bring king to kingSquares[1][i] (white queenside castle)
        chessBoard.find(kingSquares[1][i])->second.setPiece(initialCell.getPiece()); // Move piece to new cell
        Piece blankPiece = Piece(); // replace moved piece with empty square
        if (i == 0) {
          chessBoard.find("e1")->second.setPiece(blankPiece);
        }
        else {
          chessBoard.find("d1")->second.setPiece(blankPiece);
        }
        Game::updateState();
        cout << "white is in check? " << Game::getWhiteInCheck() << endl;
        if (Game::getWhiteInCheck()) {
          cout << "no castling bc white is in check on " << kingSquares[1][i] << endl;
          // Square is attacked, so can't castle
          chessBoard.find("e1")->second.setPiece(chessBoard.find(kingSquares[1][i])->second.getPiece());
          Piece blankPiece = Piece(); // replace king with empty square
          chessBoard.find(kingSquares[1][i])->second.setPiece(blankPiece);
          Game::updateState(); // re-update state, king no longer in check
          return false;
        }
      }
      // King is now on c1 and castling is valid since we made it through the loop
      // Must move rook from a1 to d1
      chessBoard.find("d1")->second.setPiece(chessBoard.find("a1")->second.getPiece());
      Piece blankPiece = Piece(); // replace moved piece with empty square
      chessBoard.find("a1")->second.setPiece(blankPiece);
      return true;
    }
  }
  else if ((initialSquare == "e8") && (!initialCell.getPiece().getWhite()) && (initialCell.getPiece().getType() == 'k')) {
    if (finalSquare == "g8") {
      cout << "Kingside" << endl;
      king = initialCell.getPiece();
      rook = chessBoard.find("h8")->second.getPiece();
      
      // Ensure that the rook is black (king starting on e8)
      if (rook.getWhite()) {
        cout << "not black" << endl;
        return false;
        } // not same color of rook
      if (rook.getType() != 'r') { // not a rook
        cout << "not a rook" << endl;
        return false;
        }

      // Make sure all squares between king and rook are empty
      if ((chessBoard.find("f8")->second.getPiece().getType() != 'x') || (chessBoard.find("g8")->second.getPiece().getType() != 'x')) {
        cout<<"Piece is in the way"<<endl;
        return false;
      }
      // Can't castle if king or rook have moved
      if ((king.getHasMoved()) || (rook.getHasMoved())) {
        cout << "already moved" << endl;
        return false;
      } 

      if (Game::getBlackInCheck()) {
        cout << "can't castle, you're in check" << endl; 
        return false;
      }

      cout << "ready to check square safety"  << endl;
      for (int i = 0; i < 2; i++) { // moves king over square by square, checking if check
        // Bring king to kingSquares[2][i] (black kingside castle)
        chessBoard.find(kingSquares[2][i])->second.setPiece(initialCell.getPiece()); // Move piece to new cell
        Piece blankPiece = Piece(); // replace moved piece with empty square          
        if (i == 0) {
          chessBoard.find("e8")->second.setPiece(blankPiece);
        }
        else {
          chessBoard.find("f8")->second.setPiece(blankPiece);
        }
        Game::updateState();
        cout << "black is in check? " << Game::getBlackInCheck() << endl;
        if (Game::getBlackInCheck()) {
          cout << "no castling bc black is in check on " << kingSquares[2][i] << endl;
          // Square is attacked, so can't castle
          chessBoard.find("e8")->second.setPiece(chessBoard.find(kingSquares[2][i])->second.getPiece());
          Piece blankPiece = Piece(); // replace king with empty square
          chessBoard.find(kingSquares[2][i])->second.setPiece(blankPiece);
          Game::updateState(); // re-update state, king no longer in check
          return false;
        }
      }
      // King is now on g8 and castling is valid since we made it through the loop
      // Must move rook from h8 to f8
      chessBoard.find("f8")->second.setPiece(chessBoard.find("h8")->second.getPiece());
      Piece blankPiece = Piece(); // replace moved piece with empty square
      chessBoard.find("h8")->second.setPiece(blankPiece);
      return true;
    } 
    else if (finalSquare == "c8") {
      cout<<"queenside"<<endl;
      king = initialCell.getPiece();
      rook = chessBoard.find("a8")->second.getPiece();
      
      // Ensure that the rook is black (king starting on e8)
      if (rook.getWhite()) {
        cout << "not getBlackInCheck" << endl;
        return false;
        } // not same color of rook
      if (rook.getType() != 'r') { // not a rook
        cout << "not a rook" << endl;
        return false;
        }

      // Make sure all squares between king and rook are empty
      if ((chessBoard.find("b8")->second.getPiece().getType() != 'x') || (chessBoard.find("c8")->second.getPiece().getType() != 'x') || (chessBoard.find("d8")->second.getPiece().getType() != 'x')) {
        cout<<"Piece is in the way"<<endl;
        return false;
      }
      // Can't castle if king or rook have moved
      if ((king.getHasMoved()) || (rook.getHasMoved())) {
        cout << "already moved" << endl;
        return false;
      } 

      if (Game::getBlackInCheck()) {
        cout << "can't castle, you're in check" << endl; 
        return false;
      }

      cout << "ready to check square safety"  << endl;
      for (int i = 0; i < 2; i++) { // moves king over square by square, checking if check
        chessBoard.find(kingSquares[3][i])->second.setPiece(initialCell.getPiece()); // Move piece to new cell
        Piece blankPiece = Piece(); // replace moved piece with empty square          
        if (i == 0) {
          chessBoard.find("e8")->second.setPiece(blankPiece);
        }
        else {
          chessBoard.find("d8")->second.setPiece(blankPiece);
        }
        Game::updateState();
        cout << "black is in check? " << Game::getBlackInCheck() << endl;
        if (Game::getBlackInCheck()) {
          cout << "no castling bc black is in check on " << kingSquares[3][i] << endl;
          // Square is attacked, so can't castle
          chessBoard.find("e8")->second.setPiece(chessBoard.find(kingSquares[3][i])->second.getPiece());
          Piece blankPiece = Piece(); // replace king with empty square
          chessBoard.find(kingSquares[3][i])->second.setPiece(blankPiece);
          Game::updateState(); // re-update state, king no longer in check
          return false;
        }
      }
      // King is now on c8 and castling is valid since we made it through the loop
      // Must move rook from a8 to d8
      chessBoard.find("d8")->second.setPiece(chessBoard.find("a8")->second.getPiece());
      Piece blankPiece = Piece(); // replace moved piece with empty square
      chessBoard.find("a8")->second.setPiece(blankPiece);
      return true;
    }
  }
  return false;
}
/*
void ePCountDecrease() {
  // Decrease the EP count of all pawns, down to a minimum of 0
  for (char i = 'a'; i <= 'h'; i++) {
    for (int j = 1; j <= 8; j++) {
      string tempSquare(1, i);
      tempSquare += to_string(j);

      // For pieces, the following line of code keeps the
      // number at 0; for pawns, it decreases the EP count
      // by 1 to a minimum of 0.
      chessBoard.find(tempSquare)->second.getPiece().setEPCountDown(min(chessBoard.find(tempSquare)->second.getPiece().getEPCountDown() - 1, 0));
    }
  }
}

int enPassantCheck(string initialSquare, Cell initialCell, int finalRank) {
  // Check for en passant
  if (initialCell.getPiece().getWhite() == true) {
    // White pawn trying to do en passant
    if (finalRank == 6) {
      string enPassantSquare = initialSquare;
      enPassantSquare[2] -= 1; // Check the piece one rank down
      Piece tempPiece = chessBoard.find(enPassantSquare)->second.getPiece();
      cout << "trying to do en passant on " << enPassantSquare << endl;
      if ((tempPiece.getType() == 'p') && (tempPiece.getWhite() == false)) {
        // Must be an opposite-coloured pawn
        cout << "ep count is " << tempPiece.getEPCountDown() << endl;
        if (tempPiece.getEPCountDown() > 0) {
          // The en passant move is valid
          return 3;
        }
      }
    }
  }
  else {
    // Black pawn trying to do en passant
    if (finalRank == 3) {
      string enPassantSquare = initialSquare;
      enPassantSquare[2] += 1; // Check the piece one rank up
      Piece tempPiece = chessBoard.find(enPassantSquare)->second.getPiece();
      cout << "trying to do en passant on " << enPassantSquare << endl;
      if ((tempPiece.getType() == 'p') && (tempPiece.getWhite() == true)) {
        // Must be an opposite-coloured pawn
        cout << "ep count is " << tempPiece.getEPCountDown() << endl;
        if (tempPiece.getEPCountDown() > 0) {
          // The en passant move is valid
          return 3;
        }
      }
    }
  }
  return 0; // Invalid by default
}
*/
void pawnPromotion() {
  for (char i = 'a'; i <= 'h'; i++) { // promotion
    Piece p;
    string input;
    bool validPromotion = false;
    char choice;
    string firstRank(1, i);
      firstRank += to_string(1);
      p = chessBoard.find(firstRank)->second.getPiece();
    
    if (p.getType() == 'p') {
      if (p.getWhite() == false) {
        while (validPromotion == false) {
          validPromotion = true;
          cout << "What would you like to promote your pawn to?\n(n = knight, b = bishop, r = rook, q = queen): ";
          cin >> input; // string, not a character since chars tend to crash
          choice = input[0];
          switch(choice) {
            case 'n': {
              chessBoard.find(firstRank)->second.getPiece().setType('n');
              break;
            }
            case 'b': {
              chessBoard.find(firstRank)->second.getPiece().setType('b');
              break;
            }
            case 'r': {
              chessBoard.find(firstRank)->second.getPiece().setType('r');
              break;
            }
            case 'q': {
              chessBoard.find(firstRank)->second.getPiece().setType('q');
              break;
            }
            default: {
              cout << "Invalid promotion choice." << endl;
              validPromotion = false;
              break;
            }
          }
        }  
      }
    }
    string eighthRank(1, i);
    eighthRank += to_string(8);
    p = chessBoard.find(eighthRank)->second.getPiece();
    if (p.getType() == 'p') {
      if (p.getWhite() == true) {
        while (validPromotion == false) {
          validPromotion = true;
          cout << "What would you like to promote your pawn to?\n(n = knight, b = bishop, r = rook, q = queen)";
          cin >> input; // string, not a character since chars tend to crash
          choice = input[0];
          switch(choice) {
            case 'n': {
              chessBoard.find(eighthRank)->second.getPiece().setType('n');
              break;
            }
            case 'b': {
              chessBoard.find(eighthRank)->second.getPiece().setType('b');
              break;
            }
            case 'r': {
              chessBoard.find(eighthRank)->second.getPiece().setType('r');
              break;
            }
            case 'q': {
              chessBoard.find(eighthRank)->second.getPiece().setType('q');
              break;
            }
            default: 
              cout << "Invalid promotion choice." << endl;
              validPromotion = false;
              break;
          }
        } 
      }
    }
  }
}