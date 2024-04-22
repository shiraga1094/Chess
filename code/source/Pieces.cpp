#include <iostream>
#include <vector>
#include "Board.h"
#include "Pieces.h"
#include "Pawn.h"
#include "Knight.h"
#include "Bishop.h"
#include "Rook.h"
#include "Queen.h"
#include "King.h"

Piece::Piece() {
	row = col = color = NULL;
	PieceID = Empty;
	hasMoved = 0;
	canBeEnpassant = 0;
	FirstMove = 0;
	piecetype = nullptr;
	canCastling = 0;
}
void Piece::setPiece(int row, int col, int color, ID id) {
	FirstMove = 0;
	this->row = row;
	this->col = col;
	this->color = color;
	this->PieceID = id;
	PieceType* oldpiecetype = piecetype;
	switch (PieceID) {
		case Black_Pawn:
		case White_Pawn:
			piecetype = new Pawn(); break;
		case Black_Knight:
		case White_Knight:
			piecetype = new Knight(); break;
		case Black_Queen:
		case White_Queen:
			piecetype = new Queen(); break;
		case Black_Bishop:
		case White_Bishop:
			piecetype = new Bishop(); break;
		case Black_Rook:
		case White_Rook:
			piecetype = new Rook(); break;
		case Black_King:
		case White_King:
			piecetype = new King(); break;
		default:
			piecetype = nullptr;
	}
	//delete oldpiecetype;
}
int Piece::getCol() {
	return col;
}
int Piece::getRow() {
	return row;
}
bool Piece::GetColor() {
	return color;
}
ID Piece::GetPieceID() {
	return PieceID;
}
bool Piece::CheckMove() {
	return 0;
}
void Piece::setEnpassant() {
	this->canBeEnpassant = 1;
}
void Piece::unEnpassant() {
	this->canBeEnpassant = 0;
}
bool Piece::isEnpassant() {
	return canBeEnpassant;
}
bool Piece::isFirstMove() {
	return FirstMove;
}
void Piece::setFirstMove() {
	this->FirstMove = 1;
}
bool Piece::canCheck(int X, int Y, int toX, int toY, BoardControl& board) {
	return piecetype->canCheck(X, Y, toX, toY, board);
}
std::vector<pair> Piece::getPossibleMove(BoardControl& board) {
	return piecetype->getPossibleMove(color, row, col, board);
}
void Piece::setCastling() {
	this->canCastling = 1;
}
bool Piece::isCastling() {
	return canCastling;
}
void Piece::unCastling() {
	this->canCastling = 0;
}