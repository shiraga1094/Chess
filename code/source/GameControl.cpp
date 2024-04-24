#include <iostream>
#include <SFML/Graphics.hpp>
#include "GameControl.h"

BoardControl Game::getBoard() {
	return *Board;
}
Game::Game() {
	BoardControl *oldBoard = Board;
	Board = new BoardControl();
	delete oldBoard;
	Board->Board_Init();
	Turn = 1;
	_isBlackWin = _isWhiteWin = -1;
	_isStaleMate = _isMove_50 = 0;
	_isBlackChecked = _isWhiteChecked = -1;
	_isBlackKingCastling = _isWhiteKingCastling = -1;
	_isBlackQueenCastling = _isWhiteQueenCastling = -1;
}
void Game::Undo() {
	_isBlackWin = _isWhiteWin = 0;
	_isStaleMate = _isMove_50 = 0;
	_isBlackChecked = _isWhiteChecked = -1;
	_isWhiteKingCastling = _isBlackKingCastling = -1;
	_isWhiteQueenCastling = _isBlackQueenCastling = -1;
	if (Board->Undo()) ChangeTurn();
}
bool Game::isTurn() {
	return Turn;
}
bool Game::isMoveValid(int X, int Y, int toX, int toY) {
	bool color = Board->getPieceColor(X, Y);
	if (Turn != color) return 0;
	return Board->isMoveValid(X, Y, toX, toY, *Board);
}
void Game::Move(int X, int Y, int toX, int toY, bool Castling) {
	Board->Move(X, Y, toX, toY, Castling);
	_isWhiteWin = _isBlackWin = -1;
	_isWhiteChecked = _isBlackChecked = -1;
	_isWhiteKingCastling = _isBlackKingCastling = -1;
	_isWhiteQueenCastling = _isBlackQueenCastling = -1;
	ChangeTurn();
}
void Game::ChangeTurn() {
	Turn ^= 1;
}
bool Game::isBlackWin() {
	if (_isBlackWin==-1)
		_isBlackWin=Board->isBlackCheckMate(*Board);
	return _isBlackWin;
}
bool Game::isWhiteWin() {
	if (_isWhiteWin==-1)
		_isWhiteWin=Board->isWhiteCheckMate(*Board);
	return _isWhiteWin;
}
bool Game::isStaleMate() {
	if (_isStaleMate) return 1;
	_isStaleMate = (Board->isStaleMate(*Board) || Board->isMove_50());
	return _isStaleMate;
}
bool Game::isMove_50() {
	return Board->isMove_50();
}
void Game::Init() {
	Board->Board_Init();
}
bool Game::isBlackChecked() {
	if (_isBlackChecked == -1) _isBlackChecked = Board->isBlackChecked(*Board);
	return _isBlackChecked;
}
bool Game::isWhiteChecked() {
	if (_isWhiteChecked == -1) _isWhiteChecked = Board->isWhiteChecked(*Board);
	return _isWhiteChecked;
}
bool Game::isBlackKingCastling() {
	if(_isBlackKingCastling == -1) _isBlackKingCastling = Board->isBlackKingCastling(*Board);
	return _isBlackKingCastling;
}
bool Game::isBlackQueenCastling() {
	if (_isBlackQueenCastling == -1) _isBlackQueenCastling = Board->isBlackQueenCastling(*Board);
	return _isBlackQueenCastling;
}
bool Game::isWhiteKingCastling() {
	if (_isWhiteKingCastling == -1) _isWhiteKingCastling = Board->isWhiteKingCastling(*Board);
	return _isWhiteKingCastling;
}
bool Game::isWhiteQueenCastling() {
	if (_isWhiteQueenCastling == -1) _isWhiteQueenCastling = Board->isWhiteQueenCastling(*Board);
	return _isWhiteQueenCastling;
}
std::vector<pair> Game::getPossibleMove(int X, int Y) {
	return Board->getPossibleMove(X, Y, *Board);
}
pair Game::getBlackKingPos() {
	return Board->getBlackKingPos();
}
pair Game::getWhiteKingPos() {
	return Board->getWhiteKingPos();
}
pair Game::getLastPrevious() {
	return Board->getLastPrevious();
}
pair Game::getLastTo() {
	return Board->getLastTo();
}
bool Game::isPromotion() {
	return Board->isPromotion();
}
void Game::Promotion(int X, int Y, ID id) {
	Board->Promotion(X, Y, id);
}
void Game::ManualMove(std::string MOVE) {
	std::vector<int> pos;
	switch (MOVE[0]) {
		case 'O':
			if (Turn == 0) {
				if (MOVE.length() == 5) {
					Move(0, 4, 0, 2);
					Move(0, 0, 0, 3, 1);
				}
				else {
					Move(0, 4, 0, 6);
					Move(0, 7, 0, 5, 1);
				}
			}
			else {
				if (MOVE.length() == 5) {
					Move(7, 4, 7, 2);
					Move(7, 0, 7, 3, 1);
				}
				else {
					Move(7, 4, 7, 6);
					Move(7, 7, 7, 5, 1);
				}
			}
			ChangeTurn();
			break;
		default:
			pos = GetManualPos(MOVE);
			bool K = 0;
			for (int r = 0; r < 8 and !K; r++) {
				for (int c = 0; c < 8 and !K; c++) {
					if (MOVE[0]=='N' and Board->GetPieceID(r, c) != White_Knight and Board->GetPieceID(r, c) != Black_Knight)
						continue;
					if (MOVE[0] == 'B' and Board->GetPieceID(r, c) != White_Bishop and Board->GetPieceID(r, c) != Black_Bishop)
						continue;
					if (MOVE[0] == 'R' and Board->GetPieceID(r, c) != White_Rook and Board->GetPieceID(r, c) != Black_Rook)
						continue;
					if (MOVE[0] == 'Q' and Board->GetPieceID(r, c) != White_Queen and Board->GetPieceID(r, c) != Black_Queen)
						continue;
					if (MOVE[0] == 'K' and Board->GetPieceID(r, c) != White_King and Board->GetPieceID(r, c) != Black_King)
						continue;
					if (MOVE[0] >= 'a' and MOVE[0] <= 'z') {
						if (Board->GetPieceID(r, c) != White_Pawn and Board->GetPieceID(r, c) != Black_Pawn)
							continue;
					}
					if (Board->getPieceColor(r, c) != Turn) continue;
					if (pos[0] != -1 and pos[0] != r) continue;
					if (pos[1] != -1 and pos[1] != c) continue;
					if (Board->isMoveValid(r, c, pos[2], pos[3], *Board)) {
						Move(r, c, pos[2], pos[3]);
						K = 1;
					}
				}
			}
			if (MOVE[MOVE.length() - 2] == '=') {
				ID promotionID;
				switch (MOVE[MOVE.length() - 1]) {
					case 'N':
						if (Turn==0) promotionID = White_Knight;
						else promotionID = Black_Knight;
						break;
					case 'R':
						if (Turn == 0) promotionID = White_Rook;
						else promotionID = Black_Rook;
						break;
					case 'B':
						if (Turn == 0) promotionID = White_Bishop;
						else promotionID = Black_Bishop;
						break;
					case 'Q':
						if (Turn == 0) promotionID = White_Queen;
						else promotionID = Black_Queen;
						break;
				}
			}
			break;
	}
}
std::vector<int> Game::GetManualPos(std::string MOVE) {
	int X, Y, toX, toY; X = Y = -1;
	int len = MOVE.length() - (MOVE[MOVE.length() - 1] == '+');
	if (MOVE[MOVE.length() - 2] == '=') len -= 2;
	if (len == 2) {
		Y = toY = MOVE[0] - 'a';
		toX = 8 - (MOVE[1] - '0');
	}
	else if (len == 3) {
		toY = MOVE[1] - 'a'; 
		toX = 8 - (MOVE[2] - '0');
	}
	else if (len == 4) {
		if (MOVE[1] != 'x') {
			if (isalpha(MOVE[1])) Y = MOVE[1] - 'a';
			else X = 8 - (MOVE[1] - '0');
		}
		toY = MOVE[2] - 'a';
		toX = 8 - (MOVE[3] - '0');
	}
	else if (len == 5) {
		//Ndxe4 Qe4h3
		if (MOVE[2] == 'x') {
			if (isalpha(MOVE[1])) Y = MOVE[1] - 'a';
			else X = 8 - (MOVE[1] - '0');
		}
		else {
			Y = MOVE[1] - 'a';
			X = 8 - (MOVE[2] - '0');
		}
		toY = MOVE[3] - 'a';
		toX = 8 - (MOVE[4] - '0');
	}
	else if (len == 6) {
		Y = MOVE[1] - 'a';
		X = 8 - (MOVE[2] - '0');
		toY = MOVE[4] - 'a';
		toX = 8 - (MOVE[5] - '0');
	}

	return { X, Y, toX, toY };
}
