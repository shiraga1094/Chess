#include "TutorialControl.h"

TutorialControl::TutorialControl() {
	status = Tutorial_Initial;
	pagestatus = PieceTutorial;
	mainPieceID = White_Pawn;
	SpecialMoveset = RuleTutorialset = 0;
}
void TutorialControl::Init() {
	TutorialView* oldView = View;
	View = new TutorialView(TutorialWindow);
	delete oldView;
	sf::Image icon; icon.loadFromFile("img/Tutorial.png");
	TutorialWindow.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
}
bool TutorialControl::Run() {
	if (status == Tutorial_Initial) {
		Init();
		status = Tutorial_Start;
	}
	HandleEvent();
	if (status != Tutorial_Start) {
		TutorialWindow.close();
		return 0;
	}
	if (TutorialWindow.hasFocus()) {
		TutorialWindow.clear(sf::Color(255, 199, 142, 1));
		Draw();
		TutorialWindow.display();
	}
	return 1;
}
void TutorialControl::Draw() {
	int mouseX = sf::Mouse::getPosition(TutorialWindow).x;
	int mouseY = sf::Mouse::getPosition(TutorialWindow).y;
	View->Draw(mouseX, mouseY, isMouseHold);
	if (pagestatus == PieceTutorial) {
		View->DrawPieceTutorial(mouseX, mouseY, isMouseHold, mainPieceID);
	}
	else if (pagestatus == PieceSpecialMove) {
		View->DrawPieceSpecialMove(mouseX, mouseY, isMouseHold, SpecialMoveset);
	}
	else if (pagestatus == RuleTutorial) {
		View->DrawRuleTutorial(mouseX, mouseY, isMouseHold, RuleTutorialset);
	}
}
void TutorialControl::HandleEvent() {
	sf::Event event;
	while(TutorialWindow.pollEvent(event)) {
		if (event.type == sf::Event::LostFocus) {
			break;
		}
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				isMouseHold = 1;
				isMouseButtonPressed(event);
			}
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			isMouseHold = 0;
		}
		else if (event.type == sf::Event::Closed) {
			status = Tutorial_Exit;
			break;
		}
	}
	
}
void TutorialControl::isMouseButtonPressed(sf::Event event) {
	int mouseX = sf::Mouse::getPosition(TutorialWindow).x;
	int mouseY = sf::Mouse::getPosition(TutorialWindow).y;
	ID pieceID[6] = {White_Pawn, White_Knight, White_Bishop, White_Rook, White_Queen, White_King};
	
	for (int i = 0; i < 3; i++) {
		if (View->isInListButton(mouseX, mouseY, i)) {
			if (i == 0) pagestatus = PieceTutorial;
			else if (i == 1) pagestatus = PieceSpecialMove;
			else if (i == 2) pagestatus = RuleTutorial;

			return;
		}
	}
	if (pagestatus == PieceTutorial) {
		for (int i = 0; i < 6; i++) {
			if (View->isInPieceButton(mouseX, mouseY, i)) {
				mainPieceID = pieceID[i];
			}
		}
	}
	else if (pagestatus == PieceSpecialMove) {
		for (int i = 0; i < 4; i++) {
			if (View->isInSpecialMoveButton(mouseX, mouseY, i)) {
				SpecialMoveset = i;
			}
		}
	}
	else if (pagestatus == RuleTutorial) {
		for (int i = 0; i < 4; i++) {
			if (View->isInRuleButton(mouseX, mouseY, i)) {
				RuleTutorialset = i;
			}
		}
	}
}