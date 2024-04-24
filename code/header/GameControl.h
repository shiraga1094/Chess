#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Board.h"
#include "ID.h"
#define pair std::pair<int,int>

class Game {
private:
	BoardControl* Board;
	bool Turn; //0 Black 1 White
	int _isBlackWin, _isWhiteWin;
	bool _isStaleMate, _isMove_50;
	int _isBlackChecked, _isWhiteChecked;
	int _isBlackKingCastling, _isWhiteKingCastling;
	int _isBlackQueenCastling, _isWhiteQueenCastling;
public:
	Game();
	BoardControl getBoard();
	void Undo();
	bool isTurn();
	bool isMoveValid(int X, int Y, int toX, int toY);
	void Move(int Bx, int By, int toX, int toY, bool Castling=0);
	void ChangeTurn();
	bool isBlackChecked();
	bool isWhiteChecked();
	bool isPromotion();
	void Promotion(int X, int Y, ID id);
	bool isBlackKingCastling();
	bool isBlackQueenCastling();
	bool isWhiteKingCastling();
	bool isWhiteQueenCastling();
	bool isBlackWin();
	bool isWhiteWin();
	bool isStaleMate();
	bool isMove_50();
	void Init();
	std::vector<pair> getPossibleMove(int X, int Y);
	pair getBlackKingPos();
	pair getWhiteKingPos();
	pair getLastPrevious();
	pair getLastTo();

	void ManualMove(std::string MOVE);
	std::vector<int> GetManualPos(std::string MOVE);
};

#endif