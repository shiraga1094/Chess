#ifndef _KNIGHT_H_
#define _KNIGHT_H_
#include <vector>
#include <iostream>
#include <utility>
#include "PieceType.h"
#define pair std::pair<int,int>

class Knight : public PieceType {
private:
	
public:
	Knight();
	bool isOutside(int X, int Y);
	std::vector<pair> getPossibleMove(bool color, int row, int col, BoardControl& board) override;\
	bool isValidMove(int X, int Y, int toX, int toY, BoardControl& board);
	bool canCheck(int X, int Y, int toX, int toY, BoardControl& board) override;
};

#endif
