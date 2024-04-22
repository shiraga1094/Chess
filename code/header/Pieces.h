#ifndef _PIECES_H_
#define _PIECES_H_

#include "ID.h"
#include "PieceType.h"

#include <iostream>
#include <vector>
#include <utility>
#define pair std::pair<int,int>

class BoardControl;

class Piece {
private:
	PieceType* piecetype;
	int row, col;
	bool color;
	ID PieceID;
	bool hasMoved;
	bool canBeEnpassant;
	bool FirstMove;
	bool canCastling;
public:
	Piece();
	void setPiece(int row, int col, int color, ID id);
	int getRow();
	int getCol();
	bool GetColor();
	ID GetPieceID();
	void setEnpassant();
	void unEnpassant();
	void setCastling();
	bool isCastling();
	void unCastling();
	bool isEnpassant();
	bool isFirstMove();
	void setFirstMove();
	bool CheckMove();
	bool canCheck(int X, int Y, int toX, int toY, BoardControl& board);
	std::vector<pair> getPossibleMove(BoardControl& board);
};

#endif
