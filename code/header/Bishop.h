#ifndef _BISHOP_H_
#define _BISHOP_H_
#include <vector>
#include <iostream>
#include <utility>
#include "PieceType.h"

#define pair std::pair<int,int>

class Bishop : public PieceType {
private:
	
public:
	Bishop();
	bool isOutside(int X, int Y);
	bool isSameColor(bool color, int X, int Y, BoardControl& board);
	std::vector<pair> getPossibleMove(bool color, int row, int col, BoardControl& board) override;
	bool isValidMove(int X, int Y, int toX, int toY, BoardControl& board);
	bool canCheck(int X, int Y, int toX, int toY, BoardControl& board) override;
};


#endif