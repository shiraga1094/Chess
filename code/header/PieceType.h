#ifndef _PIECETYPE_H_
#define _PIECETYPE_H_
#include <iostream>
#include <vector>
#include <utility>
#include "ID.h"
#define pair std::pair<int,int>

class BoardControl;

class PieceType {
private:
	
public:
	
	virtual std::vector<pair> getPossibleMove(bool color, int row, int col, BoardControl& board) = 0;
	virtual bool canCheck(int X, int Y, int toX, int toY, BoardControl& board) = 0;
};


#endif
