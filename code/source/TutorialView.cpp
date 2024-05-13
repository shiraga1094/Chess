#include "TutorialView.h"
#define pair std::pair<int,int>

TutorialView::TutorialView(sf::RenderWindow& window):TutorialWindow(window) {
	Tooltip* oldtip = tooltip;
	tooltip = new Tooltip(TutorialWindow);
	delete oldtip;
	input = new PieceInput();
	Board = input->GetTutorialBoard();
	Board.setScale(0.9, 0.9);
	listButton = input->GetListButton();
	listButton[0].setScale(0.6, 0.6);
	listButton[0].setPosition(BeginX + gap * 7, 10+BeginY);
	listButton[1].setScale(0.6, 0.6);
	listButton[1].setPosition(BeginX + gap * 7, 10+BeginY+gap*1.5);
	listButton[2].setScale(0.4, 0.4);
	listButton[2].setPosition(BeginX + gap * 7, 10+BeginY+gap*3);
	for (int i = 0; i < 6; i++) {
		PieceButton[i] = input->GetSprite(pieceID[i]);
		PieceButton[i].setScale(0.9, 0.9);
		PieceButton[i].setPosition(BeginX + gap*0.5 + gap * i, BeginY + gap * 8.5);
	}
	SpecialMoveButton = input->GetSpecialMoveButton();
	for (int i = 0; i < 4; i++) {
		SpecialMoveButton[i].setScale(0.9, 0.9);
		SpecialMoveButton[i].setPosition(BeginX+gap * 0.5 + gap * i, BeginY + gap * 8.5);
	}
	RuleButton = input->GetRuleButton();
	for (int i = 0; i < 4; i++) {
		RuleButton[i].setScale(0.9, 0.9);
		RuleButton[i].setPosition(BeginX + gap * 0.5 + gap * i, BeginY + gap * 8.5);
	}
	ButtonBg = sf::RectangleShape(sf::Vector2f(118, 118));
	MoveHint = input->GetMoveHint();
	PreviousSquare = sf::RectangleShape(sf::Vector2f(gap+1, gap+1));
	PreviousSquare.setFillColor(sf::Color(152, 251, 152));
	CheckSquare = sf::RectangleShape(sf::Vector2f(gap+1, gap+1));
	CheckSquare.setFillColor(sf::Color(255, 114, 86));
	font.loadFromFile("arial.ttf");
	HintTitle.setFont(font);
	HintTitle.setFillColor(sf::Color::Black);
	HintTitle.setStyle(sf::Text::Bold);
	HintTitle.setPosition(BeginX + 10, BeginY + gap * 7 + 2);
	HintTitle.setCharacterSize(40);
	HintText.setFont(font);
	HintText.setFillColor(sf::Color::Black);
	HintText.setPosition(BeginX + 10, BeginY + gap * 7.3 + 12);
	HintText.setCharacterSize(30);
	CommandWindow = sf::RectangleShape(sf::Vector2f(gap * 7.8, gap * 1.5));
	CommandWindow.setFillColor(sf::Color(255, 235, 205));
	CommandWindow.setPosition(BeginX, BeginY + gap * 7);
}
void TutorialView::Draw(int X, int Y, bool isPressed) {
	TutorialWindow.draw(Board);
	TutorialWindow.draw(CommandWindow);
	DrawButton(X, Y, isPressed);
}
void TutorialView::DrawButton(int X, int Y, bool isPressed) {
	for (int i = 0; i < 3; i++) {
		if (isInListButton(X, Y, i)) {
			ButtonBg.setPosition(BeginX + gap * 7, 10 + BeginY + gap*(1.5*i));
			if (isPressed) ButtonBg.setFillColor(sf::Color(190, 190, 190));
			else ButtonBg.setFillColor(sf::Color(211, 211, 211));
			TutorialWindow.draw(ButtonBg);
		}
		TutorialWindow.draw(listButton[i]);
	}
	for (int i = 0; i < 3; i++) {
		if (isInListButton(X, Y, i)) {
			if (i == 0) tooltip->SetTooltip("PieceTutorial", 50);
			else if (i == 1) tooltip->SetTooltip("PieceSpecialMove", 50);
			else if (i == 2) tooltip->SetTooltip("RuleTutorial", 50);
		}
	}
	tooltip->Draw();
}
void TutorialView::DrawPieceTutorial(int X, int Y, bool isPressed, ID pieceID) {
	DrawPieceButton(X, Y, isPressed);
	sf::Sprite piece = input->GetSprite(pieceID);
	piece.setScale(0.9, 0.9);
	piece.setPosition(BeginX + gap * 3, BeginY + gap * 3);
	TutorialWindow.draw(piece);
	if (pieceID == White_Pawn) {
		piece = input->GetSprite(Black_Pawn);
		piece.setScale(0.9, 0.9);
		piece.setPosition(BeginX + gap * 2, BeginY + gap * 2);
		TutorialWindow.draw(piece);
		piece.setPosition(BeginX + gap * 4, BeginY + gap * 2);
		TutorialWindow.draw(piece);
	}
	std::vector<pair> pos;
	switch (pieceID) {
		case White_Pawn:
			HintTitle.setString("Pawn");
			HintText.setString("Pawn moves straight forward one square.\nIt also can capture an enemy piece on either of the two squares \ndiagonally in front of the pawn.");
			pos.push_back({ 3,2 });
			pos.push_back({ 2,2 });
			pos.push_back({ 4,2 });
			break;
		case White_Knight:
			HintTitle.setString("Knight");
			HintText.setString("Knight moves to one of the nearest squares not on the same rank, file, \nor diagonal.");
			pos = { {2,1},{4,1},{5,2},{5,4},{4,5},{2,5},{1,4},{1,2} };
			break;
		case White_Bishop:
			HintTitle.setString("Bishop");
			HintText.setString("Bishop moves any number of vacant squares diagonally.");
			for (int r = 0; r <= 6; r++) {
				if (r == 3) continue;
				pos.push_back({ r,r });
				pos.push_back({ r,6 - r });
			}
			break;
		case White_Rook:
			HintTitle.setString("Rook");
			HintText.setString("Rook moves any number of vacant squares horizontally or vertically.");
			for (int r = 0; r <= 6; r++) {
				if (r == 3) continue;
				pos.push_back({ r,3 });
				pos.push_back({ 3,r });
			}
			break;
		case White_Queen:
			HintTitle.setString("Queen");
			HintText.setString("Queen moves any number of vacant squares horizontally, vertically, \nor diagonally.");
			for (int r = 0; r <= 6; r++) {
				if (r == 3) continue;
				pos.push_back({ r,3 });
				pos.push_back({ 3,r });
			}
			for (int r = 0; r <= 6; r++) {
				if (r == 3) continue;
				pos.push_back({ r,r });
				pos.push_back({ r,6 - r });
			}
			break;
		case White_King:
			HintTitle.setString("King");
			HintText.setString("King moves exactly one square horizontally, vertically, or diagonally.");
			pos = { {2,2},{2,3},{2,4},{3,2},{3,4},{4,2},{4,3},{4,4} };
			break;
	}
	for (pair now : pos) {
		MoveHint.setPosition(5+BeginX + gap*0.25 + gap * now.first, 5+BeginY + gap * 0.25 + gap * now.second);
		TutorialWindow.draw(MoveHint);
	}
	TutorialWindow.draw(HintTitle);
	TutorialWindow.draw(HintText);
}
void TutorialView::DrawPieceButton(int X, int Y, bool isPressed) {
	ButtonBg.setFillColor(sf::Color(0, 0, 0, 1));
	for (int i = 0; i < 6; i++) {
		if (isInPieceButton(X, Y, i)) {
			ButtonBg.setPosition(BeginX + gap * 0.5 + gap * i, BeginY + gap * 8.5);
			if (isPressed) ButtonBg.setFillColor(sf::Color(190, 190, 190));
			else ButtonBg.setFillColor(sf::Color(211, 211, 211));
		}
	}
	TutorialWindow.draw(ButtonBg);
	for (int i = 0; i < 6; i++) {
		TutorialWindow.draw(PieceButton[i]);
		if (isInPieceButton(X, Y, i)) {
			switch (i) {
				case 0: tooltip->SetTooltip("Pawn", 50); break;
				case 1: tooltip->SetTooltip("Knight", 50); break;
				case 2: tooltip->SetTooltip("Bishop", 50); break;
				case 3: tooltip->SetTooltip("Rook", 50); break;
				case 4: tooltip->SetTooltip("Queen", 50); break;
				case 5: tooltip->SetTooltip("King", 50); break;
			}
		}
	}
	tooltip->Draw();
}
void TutorialView::DrawPieceSpecialMove(int X, int Y, bool isPressed, int ID) {
	DrawSpecialMoveButton(X, Y, isPressed);
	std::vector<pair> pos;
	sf::Sprite sprite;
	switch (ID) {
		case 0: //PawnFirstMove
			HintTitle.setString("Pawn--FirstMove");
			HintText.setString("If Pawn hasn't moved yet, it also has the option of moving two squares \nstraight forward, provided both squares are vacant.");
			sprite = input->GetSprite(White_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY + gap * 5);
			TutorialWindow.draw(sprite);
			pos.push_back({ 3,4 });
			pos.push_back({ 3,3 });
			break;
		case 1: //Enpassant
			HintTitle.setString("Pawn--Enpassant");
			HintText.setString("When a pawn advances two squares on its initial move and ends the turn \nadjacent to an enemy pawn on the same rank in the previous turn, it may \nbe captured en passant by the enemy pawn as if it had moved only \none square.");
			PreviousSquare.setPosition(gap * 3, gap * 1);
			TutorialWindow.draw(PreviousSquare);
			PreviousSquare.setPosition(gap * 3, gap * 3);
			TutorialWindow.draw(PreviousSquare);
			sprite = input->GetSprite(White_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 4, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(Black_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			pos.push_back({ 3,2 });
			break;
		case 2: //Promotion
			HintTitle.setString("Pawn--Promotion");
			HintText.setString("If Pawn advances to its eighth rank, the pawn is then promoted to a queen, \nrook, bishop, or knight of the same color at the choice of the player ");
			PreviousSquare.setPosition(gap * 3, 0);
			TutorialWindow.draw(PreviousSquare);
			PreviousSquare.setPosition(gap * 3, gap);
			TutorialWindow.draw(PreviousSquare);
			sprite = input->GetSprite(White_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY);
			TutorialWindow.draw(sprite);
			break;
		case 3: //Castling
			HintTitle.setString("Castling");
			HintText.setString("King moves two squares to its left or right, and rook leaps over next to it.\nNeither the king nor the rook has moved and the king may not be in check.\nThere must not be any pieces between the king and the rook.\nThe two squares the king will pass through may not be under attack.\n");
			PreviousSquare.setPosition(gap * 3, gap * 6);
			TutorialWindow.draw(PreviousSquare);
			PreviousSquare.setPosition(gap * 5, gap * 6);
			TutorialWindow.draw(PreviousSquare);
			sprite = input->GetSprite(White_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 5, BeginY + gap * 6);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(White_Rook);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 4, BeginY + gap * 6);
			TutorialWindow.draw(sprite);
			break;
	}
	for (pair now : pos) {
		MoveHint.setPosition(5 + BeginX + gap * 0.25 + gap * now.first, 5 + BeginY + gap * 0.25 + gap * now.second);
		TutorialWindow.draw(MoveHint);
	}
	TutorialWindow.draw(HintTitle);
	TutorialWindow.draw(HintText);
}
void TutorialView::DrawSpecialMoveButton(int X, int Y, bool isPressed) {
	ButtonBg.setFillColor(sf::Color(0, 0, 0, 1));
	for (int i = 0; i < 4; i++) {
		if (isInSpecialMoveButton(X, Y, i)) {
			ButtonBg.setPosition(BeginX + gap * 0.5 + gap*i, BeginY + gap * 8.5);
			if (isPressed) ButtonBg.setFillColor(sf::Color(190, 190, 190));
			else ButtonBg.setFillColor(sf::Color(211, 211, 211));
		}
	}
	TutorialWindow.draw(ButtonBg);
	for (int i = 0; i < 4; i++) {
		TutorialWindow.draw(SpecialMoveButton[i]);
		if (isInSpecialMoveButton(X, Y, i)) {
			switch (i) {
			case 0: tooltip->SetTooltip("Pawn--FirstMove", 50); break;
			case 1: tooltip->SetTooltip("Pawn--Enpassant", 50); break;
			case 2: tooltip->SetTooltip("Pawn--Promotion", 50); break;
			case 3: tooltip->SetTooltip("Castling", 50); break;
			}
		}
	}
	tooltip->Draw();
}
void TutorialView::DrawRuleTutorial(int X, int Y, bool isPressed, int ID) {
	DrawRuleButton(X, Y, isPressed);
	std::vector<pair> pos;
	sf::Sprite sprite;
	switch (ID) {
		case 0: //Check
			HintTitle.setString("Check");
			HintText.setString("A king is in check when it is under attack by at least one enemy piece.\nIt is illegal to make a move that places or leaves one's king in check.");
			CheckSquare.setPosition(gap * 3, 0);
			TutorialWindow.draw(CheckSquare);
			sprite = input->GetSprite(White_Bishop);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 1, BeginY + gap * 2);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(Black_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY);
			TutorialWindow.draw(sprite);
			pos.push_back({ 2,1 });
			pos.push_back({ 3,0 });
			break;
		case 1: //CheckMate
			HintTitle.setString("To Win--CheckMate");
			HintText.setString("If a player's king is placed in check and there is no legal move that player \ncan make to escape check,then the king is said to be checkmated.");
			CheckSquare.setPosition(gap * 3, 0);
			TutorialWindow.draw(CheckSquare);
			sprite = input->GetSprite(White_Bishop);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 1, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(White_Queen);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY + gap * 1);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(Black_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY);
			TutorialWindow.draw(sprite);
			for (int r = 2; r <= 4; r++) {
				for (int c = 0; c<=1; c++) {
					if (r == 3 and c == 1) continue;
					pos.push_back({ r,c });
				}
			}
			break;
		case 2: //StaleMate
			HintTitle.setString("Draw--StaleMate");
			HintText.setString("If the player to move is not in check and has no legal move, this situation is \ncalled a stalemate.");
			sprite = input->GetSprite(White_Bishop);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 4, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(White_Queen);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(Black_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 2, BeginY);
			TutorialWindow.draw(sprite);
			for (int c = 0; c < 3; c++) {
				for (int r = 3; r >=c; r--) {
					if (r == 2 and c == 0) continue;
					pos.push_back({ r,c });
				}
			}
			break;
		case 3: //50Move
			HintTitle.setString("Draw--50MoveRule");
			HintText.setString("If no capture is made and no pawn is moved for 50 consecutive moves, \nthen it's a draw.");
			sprite = input->GetSprite(Black_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 1, BeginY + gap * 3);
			TutorialWindow.draw(sprite);
			sprite.setPosition(BeginX + gap * 6, BeginY + gap * 4);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(White_Pawn);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 1, BeginY + gap * 4);
			TutorialWindow.draw(sprite);
			sprite.setPosition(BeginX + gap * 6, BeginY + gap * 5);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(Black_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY);
			TutorialWindow.draw(sprite);
			sprite = input->GetSprite(White_King);
			sprite.setScale(0.9, 0.9);
			sprite.setPosition(BeginX + gap * 3, BeginY + gap*6);
			TutorialWindow.draw(sprite);
			break;
	}
	for (pair now : pos) {
		MoveHint.setPosition(5 + BeginX + gap * 0.25 + gap * now.first, 5 + BeginY + gap * 0.25 + gap * now.second);
		TutorialWindow.draw(MoveHint);
	}
	TutorialWindow.draw(HintTitle);
	TutorialWindow.draw(HintText);
}
void TutorialView::DrawRuleButton(int X, int Y, bool isPressed) {
	ButtonBg.setFillColor(sf::Color(0, 0, 0, 1));
	for (int i = 0; i < 4; i++) {
		if (isInRuleButton(X, Y, i)) {
			ButtonBg.setPosition(BeginX + gap * 0.5 + gap * i, BeginY + gap * 8.5);
			if (isPressed) ButtonBg.setFillColor(sf::Color(190, 190, 190));
			else ButtonBg.setFillColor(sf::Color(211, 211, 211));
		}
	}
	TutorialWindow.draw(ButtonBg);
	for (int i = 0; i < 4; i++) {
		TutorialWindow.draw(RuleButton[i]);
		if (isInRuleButton(X, Y, i)) {
			switch (i) {
			case 0: tooltip->SetTooltip("Check", 50); break;
			case 1: tooltip->SetTooltip("CheckMate", 50); break;
			case 2: tooltip->SetTooltip("StaleMate", 50); break;
			case 3: tooltip->SetTooltip("50MoveRule", 50); break;
			}
		}
	}
	tooltip->Draw();
}
bool TutorialView::isInListButton(int X, int Y, int ID) {
	return listButton[ID].getGlobalBounds().contains(X, Y);
}
bool TutorialView::isInPieceButton(int X, int Y, int ID) {
	return PieceButton[ID].getGlobalBounds().contains(X, Y);
}
bool TutorialView::isInSpecialMoveButton(int X, int Y, int ID) {
	return SpecialMoveButton[ID].getGlobalBounds().contains(X, Y);
}
bool TutorialView::isInRuleButton(int X, int Y, int ID) {
	return RuleButton[ID].getGlobalBounds().contains(X, Y);
}
