#include "Knight.h"
#include "Board.h"

Knight::Knight() {

}
bool Knight::isOutside(int X, int Y) {
	return X < 0 || X >= 8 || Y < 0 || Y >= 8;
}
std::vector<pair> Knight::getPossibleMove(bool color, int row, int col, BoardControl& board) {
	std::vector<pair> tmp;
	int dx[8] = { -2,-2,-1,1,2,2,1,-1 }, dy[8] = { -1,1,2,2,1,-1,-2,-2 };
	for (int i = 0; i < 8; i++) {
		int nx = row + dx[i], ny = col + dy[i];
		if (isOutside(nx, ny)) continue;
		if (board.GetPieceID(nx,ny)!=Empty and board.getPieceColor(nx, ny) == color) continue;
		if(isValidMove(row, col, nx, ny, board))
			tmp.push_back({ nx,ny });
	}
	return tmp;
}
bool Knight::isValidMove(int X, int Y, int toX, int toY, BoardControl& board) {
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
	if (fromcolor == black) ans = board.isBlackChecked(copy);
	if (fromcolor == white) ans = board.isWhiteChecked(copy);
	copy.setPiece(X, Y, fromcolor, fromID);
	copy.setPiece(toX, toY, copycolor, copyID);
	return !ans;
}
bool Knight::canCheck(int X, int Y, int toX, int toY, BoardControl& board) {
	int dx[8] = { -2,-2,-1,1,2,2,1,-1 }, dy[8] = { -1,1,2,2,1,-1,-2,-2 };
	for (int i = 0; i < 8; i++) {
		int nx = X + dx[i], ny = Y + dy[i];
		if (nx == toX and ny == toY)
			return 1;
	}
	return 0;
}
