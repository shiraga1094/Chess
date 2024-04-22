#include "Pawn.h"
#include "Board.h"

Pawn::Pawn() {
	
}
bool Pawn::isEnemy(bool color, int X, int Y, BoardControl& board) {
	return board.GetPieceID(X, Y) != Empty and board.getPieceColor(X, Y) != color;
}
std::vector<pair> Pawn::getPossibleMove(bool color, int row, int col, BoardControl& board) {
	std::vector<pair> tmp;
	bool black = 0, white = 1;
	if (color == white) {
		int nrow = row, ncol = col;
		if (ncol - 1 >= 0 and row-1>=0 and isEnemy(color, row - 1, col - 1, board)) {
			if(isValidMove(row, col, row-1, col-1, board))
				tmp.push_back({ nrow - 1, ncol - 1 });
		}
		if (ncol + 1 < 8 and row-1>=0 and isEnemy(color, row - 1, col + 1, board)) {
			if(isValidMove(row, col, row-1, col+1, board))
				tmp.push_back({ nrow - 1, ncol + 1 });
		}
		if (nrow-1>=0 and board.GetPieceID(nrow - 1, ncol) == Empty) {
			if(isValidMove(row, col, row-1, col, board))
				tmp.push_back({ nrow - 1, ncol });
		}
		if (board.isFirstMove(row, col)) {
			if (nrow-2>=0 and board.GetPieceID(nrow-1,col)==Empty and board.GetPieceID(nrow - 2, ncol) == Empty) {
				if(isValidMove(row, col, row-2, col, board))
					tmp.push_back({ nrow - 2, ncol });
			}
		}
		if (row == 3) {
			if (col - 1 >= 0 and board.isEnpassant(row, col-1)){
				if(isValidMove(row, col, row-1, col-1, board))
					tmp.push_back({ row-1, col - 1 });
			}
			if (col + 1 < 8 and board.isEnpassant(row, col + 1)) {
				if(isValidMove(row, col, row-1, col+1, board))
					tmp.push_back({ row-1, col + 1 });
			}
		}
	}
	else {
		int nrow = row, ncol = col;
		if (ncol - 1 >= 0 and row+1<8 and isEnemy(color, row + 1, col - 1, board)) {
			if(isValidMove(row, col, row+1, col-1, board))
				tmp.push_back({ nrow + 1, ncol - 1 });
		}
		if (ncol + 1 < 8 and row+1<8 and isEnemy(color, row + 1, col + 1, board)) {
			if(isValidMove(row, col, row+1, col+1, board))
				tmp.push_back({ nrow + 1, ncol + 1 });
		}
		if (nrow+1<8 and board.GetPieceID(nrow + 1, ncol) == Empty) {
			if (isValidMove(row, col, row + 1, col, board)) {
				tmp.push_back({ nrow + 1, ncol });
			}
		}
		if (board.isFirstMove(row, col)) {
			if (nrow+2<8 and board.GetPieceID(nrow + 1, col) == Empty and board.GetPieceID(nrow + 2, ncol) == Empty) {
				if(isValidMove(row, col, row+2, col, board))
					tmp.push_back({ nrow + 2, ncol });
			}
		}
		if (row == 4) {
			if (col - 1 >= 0 and board.isEnpassant(row, col - 1)) {
				if(isValidMove(row, col, row+1, col-1, board))
					tmp.push_back({ row+1, col - 1 });
			}
			if (col + 1 < 8 and board.isEnpassant(row, col + 1)) {
				if(isValidMove(row, col, row+1, col+1, board))
					tmp.push_back({ row+1, col + 1 });
			}
		}
	}
	return tmp;
}
bool Pawn::isValidMove(int X, int Y, int toX, int toY, BoardControl& board) {
	bool copycolor = board.getPieceColor(toX, toY), fromcolor = board.getPieceColor(X, Y);
	ID copyID = board.GetPieceID(toX, toY), fromID = board.GetPieceID(X, Y);
	BoardControl copy = BoardControl();
	for (int r = 0; r < 8; r++) {
		for (int c = 0; c < 8; c++) {
			if (r == toX and c == toY) copy.setPiece(r, c, fromcolor, fromID);
			else if (r == X and c == Y) copy.setPiece(r, c, NULL, Empty);
			else copy.setPiece(r, c, board.getPieceColor(r, c), board.GetPieceID(r, c));
		}
	}
	copy.setPiece(toX, toY, fromcolor, fromID);
	copy.setPiece(X, Y, NULL, Empty);
	bool ans;
	if (fromcolor == black) ans=board.isBlackChecked(copy);
	if (fromcolor == white) ans=board.isWhiteChecked(copy);
	copy.setPiece(X, Y, fromcolor, fromID);
	copy.setPiece(toX, toY, copycolor, copyID);
	return !ans;
}
bool Pawn::canCheck(int X, int Y, int toX, int toY, BoardControl& board) {
	if (board.getPieceColor(X,Y)==black and X + 1 == toX) {
		if (Y + 1 == toY or Y - 1 == toY) return 1;
	}
	if (board.getPieceColor(X, Y) == white and X - 1 == toX) {
		if (Y + 1 == toY or Y - 1 == toY) return 1;
	}
	return 0;
}
