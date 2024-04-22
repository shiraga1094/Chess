#ifndef _PAWN_H_
#define _PAWN_H_
#include <vector>
#include <iostream>
#include <utility>
#include "PieceType.h"
#define pair std::pair<int,int>

class Pawn:public PieceType {
private:
	
public:
	Pawn();
	bool isEnemy(bool color, int X, int Y, BoardControl& board);
	std::vector<pair> getPossibleMove(bool color, int row, int col, BoardControl& board) override;
	bool isValidMove(int X, int Y, int toX, int toY, BoardControl& board);
	bool canCheck(int X, int Y, int toX, int toY, BoardControl& board) override;
};

#endif