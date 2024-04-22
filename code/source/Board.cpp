#include "Board.h"
#include <iostream>

BoardControl::BoardControl() {
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			Piece* oldpiece = piece[r][c];
			piece[r][c] = new Piece();
			delete oldpiece;
		}
	}

	Move_50 = 0;
	MovesList = {};
	BlackKingChecked = WhiteKingChecked = 0;
	BlackCheckMate = WhiteCheckMate = 0;
	BlackKingPos = { 0,4 };
	WhiteKingPos = { 7,4 };
	toPromotion = 0;
}
bool BoardControl::isOutside(int X, int Y) {
	return X < 0 || X >= 8 || Y < 0 || Y >= 8;
}
void BoardControl::Board_Init() {
	piece[0][0]->setPiece(0, 0, black, Black_Rook);
	piece[0][1]->setPiece(0, 1, black, Black_Knight);
	piece[0][2]->setPiece(0, 2, black, Black_Bishop);
	piece[0][3]->setPiece(0, 3, black, Black_Queen);
	piece[0][4]->setPiece(0, 4, black, Black_King);
	piece[0][5]->setPiece(0, 5, black, Black_Bishop);
	piece[0][6]->setPiece(0, 6, black, Black_Knight);
	piece[0][7]->setPiece(0, 7, black, Black_Rook);

	piece[7][0]->setPiece(7, 0, white, White_Rook);
	piece[7][1]->setPiece(7, 1, white, White_Knight);
	piece[7][2]->setPiece(7, 2, white, White_Bishop);
	piece[7][3]->setPiece(7, 3, white, White_Queen);
	piece[7][4]->setPiece(7, 4, white, White_King);
	piece[7][5]->setPiece(7, 5, white, White_Bishop);
	piece[7][6]->setPiece(7, 6, white, White_Knight);
	piece[7][7]->setPiece(7, 7, white, White_Rook);

	Move_50 = 0;
	MovesList.clear(); MovesList.push_back({ -1,-1,-1,-1 });

	piece[0][4]->setCastling();
	piece[7][4]->setCastling();
	BlackKingPos = { 0,4 };
	WhiteKingPos = { 7,4 };
	for (int c = 0; c < 8; c++) {
		piece[1][c]->setPiece(1, c, black, Black_Pawn); piece[1][c]->setFirstMove();
		piece[6][c]->setPiece(6, c, white, White_Pawn); piece[6][c]->setFirstMove();
	}
	piece[0][0]->setFirstMove();
	piece[0][7]->setFirstMove();
	piece[7][0]->setFirstMove();
	piece[7][7]->setFirstMove();
}
bool BoardControl::Undo() {
	DATA data = MovesList.back(); if (data.fromX == -1 and data.fromY == -1) return 0;
	Move_50 = data.lastMove_50;
	MovesList.pop_back();
	bool fromcolor = piece[data.toX][data.toY]->GetColor();
	ID fromID = data.fromPieceID;
	if (fromID == Black_King) {
		BlackKingPos = { data.fromX, data.fromY };
	}
	else if (fromID == White_King) {
		WhiteKingPos = { data.fromX, data.fromY };
	}
	piece[data.fromX][data.fromY]->setPiece(data.fromX, data.fromY, fromcolor, fromID);
	piece[data.toX][data.toY]->setPiece(data.toX, data.toY, data.toColor, data.toPieceID);
	if (data.isfirstmove) piece[data.fromX][data.fromY]->setFirstMove();
	if (data.isenpassant) piece[data.fromX][data.fromY]->setEnpassant();
	if (data.cancastling) piece[data.fromX][data.fromY]->setCastling();
	if (data.toisfirstmove) piece[data.toX][data.toY]->setFirstMove();
	if (data.toisenpassant) piece[data.toX][data.toY]->setEnpassant();
	if (data.tocancastling) piece[data.toX][data.toY]->setCastling();
	if (data.iscastling) Undo();
	if (data.isenpassanting) {
		piece[data.enX][data.enY]->setPiece(data.enX, data.enY, data.enColor, data.enPieceID);
		piece[data.enX][data.enY]->setEnpassant();
	}
	return 1;
}
void BoardControl::setPiece(int X, int Y, int color, ID id) {
	piece[X][Y]->setPiece(X, Y, color, id);
}
ID BoardControl::GetPieceID(int X, int Y) {
	return  piece[X][Y]->GetPieceID();
}
Piece BoardControl::getPiece(int X, int Y) {
	return *piece[X][Y];
}
bool BoardControl::getPieceColor(int X, int Y) {
	return piece[X][Y]->GetColor();
}
void BoardControl::Move(int X, int Y, int toX, int toY, bool Castling) {
	DATA data;
	data.lastMove_50 = Move_50;
	data.fromX = X; data.fromY = Y; data.toX = toX; data.toY = toY;
	data.toColor = piece[toX][toY]->GetColor();
	data.fromPieceID = piece[X][Y]->GetPieceID();
	data.toPieceID = piece[toX][toY]->GetPieceID();
	data.isfirstmove = piece[X][Y]->isFirstMove();
	data.isenpassant = piece[X][Y]->isEnpassant();
	data.cancastling = piece[X][Y]->isCastling();
	data.toisfirstmove = piece[toX][toY]->isFirstMove();
	data.toisenpassant = piece[toX][toY]->isEnpassant();
	data.tocancastling = piece[toX][toY]->isCastling();
	data.isenpassanting = 0;
	if (Castling) data.iscastling = 1;
	else data.iscastling = 0;
	if (piece[toX][toY]->GetPieceID() != Empty and piece[X][Y]->GetColor() != piece[toX][toY]->GetColor())
		Move_50 = 0;
	else if (piece[X][Y]->GetPieceID() == White_Pawn or piece[X][Y]->GetPieceID() == Black_Pawn)
		Move_50 = 0;
	else
		Move_50++;
	piece[toX][toY]->setPiece(toX, toY, piece[X][Y]->GetColor(), piece[X][Y]->GetPieceID());
	if (piece[X][Y]->GetPieceID() == White_Pawn) {
		if (X == 3 and (toY == Y - 1 or toY == Y + 1) and piece[X][toY]->isEnpassant()) {
			data.isenpassanting = 1;
			data.enX = X; data.enY = toY; data.enPieceID = piece[X][toY]->GetPieceID();
			data.enColor = piece[X][toY]->GetColor();
			piece[X][toY]->setPiece(X, toY, NULL, Empty);
		}
		if(toX==0){
			toPromotion = 1;
		}
	}
	else if (piece[X][Y]->GetPieceID() == Black_Pawn) {
		if (X == 4 and (toY == Y - 1 or toY == Y + 1) and piece[X][toY]->isEnpassant()) {
			data.isenpassanting = 1;
			data.enX = X; data.enY = toY; data.enPieceID = piece[X][toY]->GetPieceID();
			data.enColor = piece[X][toY]->GetColor();
			piece[X][toY]->setPiece(X, toY, NULL, Empty);
		}
		if (toX == 7) {
			toPromotion = 1;
		}
	}
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			piece[r][c]->unEnpassant();
		}
	}
	if (piece[X][Y]->GetPieceID() == White_Pawn) {
		if (X == 6 and toX == 4) piece[toX][toY]->setEnpassant();	
	}
	else if (piece[X][Y]->GetPieceID() == Black_Pawn) {
		if (X == 1 and toX == 3) piece[toX][toY]->setEnpassant();
	}
	if (piece[X][Y]->GetPieceID() == Black_King) {
		BlackKingPos = { toX, toY };
		piece[X][Y]->unCastling();
	}
	else if (piece[X][Y]->GetPieceID() == White_King) {
		WhiteKingPos = { toX, toY };
		piece[X][Y]->unCastling();
	}
	piece[X][Y]->setPiece(X, Y, NULL, Empty);

	MovesList.push_back(data);
}
bool BoardControl::isEnpassant(int X, int Y) {
	return piece[X][Y]->isEnpassant();
}
bool BoardControl::isBlackChecked(BoardControl board) {
	pair tmpBlackKingPos;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == Black_King) tmpBlackKingPos = { r,c };
		}
	}
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == Empty) continue;
			if (board.getPieceColor(r, c) == black) continue;
			if (board.getPiece(r, c).canCheck(r, c, tmpBlackKingPos.first, tmpBlackKingPos.second, board))
				return 1;
		}
	}
	return 0;
}
bool BoardControl::isBlackCheckMate(BoardControl& board) {
	if (!isBlackChecked(board)) return 0;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == Empty) continue;
			if (board.getPieceColor(r, c) == white) continue;
			if (board.getPossibleMove(r, c, board).size()) return 0;
		}
	}
	return 1;
}
bool BoardControl::isWhiteChecked(BoardControl board) {
	pair tmpWhiteKingPos;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == White_King) tmpWhiteKingPos = { r,c };
		}
	}
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == Empty) continue;
			if (board.getPieceColor(r, c) == white) continue;
			if(board.getPiece(r,c).canCheck(r,c,tmpWhiteKingPos.first, tmpWhiteKingPos.second, board))
				return 1;
		}
	}
	return 0;
}
bool BoardControl::isWhiteCheckMate(BoardControl& board) {
	if (!isWhiteChecked(board)) return 0;
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (board.GetPieceID(r, c) == Empty) continue;
			if (board.getPieceColor(r, c) == black) continue;
			if (board.getPossibleMove(r, c, board).size()) return 0;
		}
	}
	return 1;
}
bool BoardControl::isMoveValid(int X, int Y, int toX, int toY, BoardControl& board) {
	if (isOutside(toX, toY)) return 0;
	if (piece[X][Y]->GetPieceID() == Empty) return 0;
	for (pair tmp : piece[X][Y]->getPossibleMove(board)) {
		if (tmp.first == toX and tmp.second == toY) return 1;
	}
	return 0;
}
bool BoardControl::isFirstMove(int X, int Y) {
	return piece[X][Y]->isFirstMove();
}
bool BoardControl::isMove_50() {
	return Move_50 >= 50;
}
bool BoardControl::isStaleMate(BoardControl& board) {
	if (!isWhiteChecked(board)) {
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board.GetPieceID(r, c) == Empty) continue;
				if (board.getPieceColor(r, c) == black) continue;
				if (board.getPossibleMove(r, c, board).size()) return 0;
			}
		}
	}
	if (!isBlackChecked(board)) {
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (board.GetPieceID(r, c) == Empty) continue;
				if (board.getPieceColor(r, c) == white) continue;
				if (board.getPossibleMove(r, c, board).size()) return 0;
			}
		}
	}
	return 1;
}
std::vector<pair> BoardControl::getPossibleMove(int X, int Y, BoardControl& board) {
	return piece[X][Y]->getPossibleMove(board);
}
pair BoardControl::getBlackKingPos() {
	return BlackKingPos;
}
pair BoardControl::getWhiteKingPos() {
	return WhiteKingPos;
}
pair BoardControl::getLastPrevious() {
	return { MovesList.back().fromX, MovesList.back().fromY };
}
pair BoardControl::getLastTo() {
	return { MovesList.back().toX, MovesList.back().toY };
}
bool BoardControl::isBlackKingCastling(BoardControl& board) {
	if (piece[0][7]->GetPieceID() != Black_Rook or !piece[0][7]->isFirstMove())
		return 0;
	bool canCastling = piece[BlackKingPos.first][BlackKingPos.second]->isCastling();
	if (!canCastling) return 0;
	if (isBlackChecked(board)) return 0;
	for (int col = 5; col < 7; col++) {
		if (piece[0][col]->GetPieceID() != Empty) return 0;
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (piece[r][c]->GetPieceID() == Empty) continue;
				if (piece[r][c]->GetColor() == black) continue;
				if (board.getPiece(r, c).canCheck(r, c, 0, col, board)) return 0;
			}
		}
	}
	return 1;
}
bool BoardControl::isBlackQueenCastling(BoardControl& board) {
	if (piece[0][0]->GetPieceID() != Black_Rook or !piece[0][0]->isFirstMove())
		return 0;
	bool canCastling = piece[BlackKingPos.first][BlackKingPos.second]->isCastling();
	if (!canCastling) return 0;
	if (isBlackChecked(board)) return 0;
	for (int col = 3; col >1; col--) {
		if (piece[0][col]->GetPieceID() != Empty) return 0;
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (piece[r][c]->GetPieceID() == Empty) continue;
				if (piece[r][c]->GetColor() == black) continue;
				if (board.getPiece(r, c).canCheck(r, c, 0, col, board)) return 0;
			}
		}
	}
	return 1;
}
bool BoardControl::isWhiteKingCastling(BoardControl& board) {
	if (piece[7][7]->GetPieceID() != White_Rook or !piece[7][7]->isFirstMove())
		return 0;
	bool canCastling = piece[WhiteKingPos.first][WhiteKingPos.second]->isCastling();
	if (!canCastling) return 0;
	if (isWhiteChecked(board)) return 0;
	for (int col = 5; col < 7; col++) {
		if (piece[7][col]->GetPieceID() != Empty) return 0;
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (piece[r][c]->GetPieceID() == Empty) continue;
				if (piece[r][c]->GetColor() == white) continue;
				if (board.getPiece(r, c).canCheck(r, c, 7, col, board)) return 0;
			}
		}
	}
	return 1;
}
bool BoardControl::isWhiteQueenCastling(BoardControl& board) {
	if (piece[7][0]->GetPieceID() != White_Rook or !piece[7][0]->isFirstMove())
		return 0;
	bool canCastling = piece[WhiteKingPos.first][WhiteKingPos.second]->isCastling();
	if (!canCastling) return 0;
	if (isWhiteChecked(board)) return 0;
	for (int col = 3; col > 1; col--) {
		if (piece[7][col]->GetPieceID() != Empty) return 0;
		for (int r = 0; r < 8; r++) {
			for (int c = 0; c < 8; c++) {
				if (piece[r][c]->GetPieceID() == Empty) continue;
				if (piece[r][c]->GetColor() == white) continue;
				if (board.getPiece(r, c).canCheck(r, c, 7, col, board)) return 0;
			}
		}
	}
	return 1;
}
void BoardControl::Promotion(int X, int Y, ID id) {
	toPromotion = 0;
	piece[X][Y]->setPiece(X, Y, piece[X][Y]->GetColor(), id);
}
bool BoardControl :: isPromotion() {
	return toPromotion;
}