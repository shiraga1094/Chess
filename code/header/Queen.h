#ifndef _QUEEN_H_
#define _QUEEN_H_
#include <vector>
#include <iostream>
#include <utility>
#include "PieceType.h"
#define pair std::pair<int,int>

class Queen :public PieceType {
private:
	
public:
	Queen();
	bool isSameColor(bool color, int X, int Y, BoardControl& board);
	bool isOutside(int X, int Y);
	std::vector<pair> getPossibleMove(bool color, int row, int col, BoardControl& board) override;
	bool isValidMove(int X, int Y, int toX, int toY, BoardControl& board);
	bool canCheck(int X, int Y, int toX, int toY, BoardControl& board) override;
};



#endif
