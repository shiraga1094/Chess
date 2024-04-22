#ifndef _BOARD_H_
#define _BOARD_H_

#include <iostream>
#include <deque>
#include <vector>
#include <utility>
#include "Pieces.h"
#include "ID.h"
#define pair std::pair<int,int>

const int black = 0;
const int white = 1;
class Piece;

struct DATA {
	int lastMove_50;
	int fromX, fromY, toX, toY, enX, enY;
	bool toColor, enColor;
	ID fromPieceID, toPieceID, enPieceID;
	bool isfirstmove, toisfirstmove;
	bool isenpassant, toisenpassant;
	bool cancastling, tocancastling;
	bool iscastling, isenpassanting;
};

class BoardControl {
private:
	Piece* piece[8][8];
	int Move_50;
	bool isOutside(int x, int y);
	std::deque<DATA> MovesList;
	bool BlackKingChecked, WhiteKingChecked;
	bool BlackCheckMate, WhiteCheckMate;
	bool toPromotion;
	pair BlackKingPos, WhiteKingPos;
public:
	BoardControl();
	void Board_Init();
	bool Undo();

	ID GetPieceID(int X, int Y);
	Piece getPiece(int X, int Y);
	bool getPieceColor(int X, int Y);
	void Move(int X, int Y, int toX, int toY, bool Castling=0);
	void setPiece(int X, int Y, int color, ID id);
	bool isPromotion();
	void Promotion(int X, int Y, ID id);
	bool isEnpassant(int X, int Y);
	bool isWhiteKingCastling(BoardControl& board);
	bool isBlackKingCastling(BoardControl& board);
	bool isWhiteQueenCastling(BoardControl& board);
	bool isBlackQueenCastling(BoardControl& board);
	bool isFirstMove(int X, int Y);
	bool isBlackChecked(BoardControl board);
	bool isWhiteChecked(BoardControl board);
	bool isBlackCheckMate(BoardControl& board);
	bool isWhiteCheckMate(BoardControl& board);
	bool isMoveValid(int X, int Y, int toX, int toY, BoardControl& board);
	bool isMove_50();
	bool isStaleMate(BoardControl& board);
	std::vector<pair> getPossibleMove(int X, int Y, BoardControl& board);
	pair getWhiteKingPos();
	pair getBlackKingPos();
	pair getLastPrevious();
	pair getLastTo();
};
#endif
