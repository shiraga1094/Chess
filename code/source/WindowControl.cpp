#include "WindowControl.h"

WindowControl::WindowControl(sf::RenderWindow& window):MainWindow(window){
	game = nullptr;
	view = nullptr;
	status = Uninitialize;
	isRotate = 0;
	isMouseHold = isDrag= 0;
	isDragPiece = nullptr;
	ManualID = Manualscroll = NULL;
	ManualsetID = preManualsetID = -1;
	PieceBx = PieceBy = PiecetoX = PiecetoY = NULL;
	PiecePosBx = PiecePosBy = NULL;
}
void WindowControl::Init() {
	Game *oldgame = game;
	game = new Game();
	delete oldgame;
	View* oldview = view;
	view = new View(MainWindow, game);
	delete oldview;
	view->Init(isRotate);
	csmControl* oldcsmcontrol = csmcontrol;
	csmcontrol = new csmControl(game);
	delete oldcsmcontrol;
	isDrag = isChosen = 0;
	preManualsetID = -1;
	selfmove = 0;
	status = Start;
}
StatusID WindowControl::Run() {
	if (status == Uninitialize) {
		throw "Uninitialize";
	}
	
	while (status != Exit) {
		while (status == Promotion) {
			PromotionWindow();
		}
		if (status == CSM) {
			sf::RenderWindow csmWindow(sf::VideoMode(1200, 1200), "ChessNotation", (sf::Style::Close));
			int tmp= csmcontrol->Run(csmWindow);
			ManualID = tmp;
			if(ManualID!=0)
				csmManual = csmcontrol->GetcsmManual(ManualID-1);
			ManualsetID = Manualscroll = 0;
			fakeManualscroll = -1;
			preManualsetID = -1;
			status = Start;
		}
		MouseHoldEvent();
		MainWindow.clear(sf::Color(255, 199, 142, 1));
		Draw();
		MainWindow.display();
	}
	return Exit;
}
void WindowControl::PromotionWindow() {
	if (game->isTurn() == white) promotionID = Black_Queen;
	else promotionID = White_Queen;
	sf::RenderWindow SubWindow(sf::VideoMode(gap*5, gap*2), "Promotion", (sf::Style::Close,sf::Style::Titlebar));
	SubWindow.requestFocus();
	while (status == Promotion) {
		SubHoldEvent(SubWindow);
		SubWindow.clear(sf::Color(255, 199, 142, 1));
		view->DrawSubWindow(SubWindow);
		SubWindow.display();
	}
	game->Promotion(PiecetoX, PiecetoY, promotionID);
}
void WindowControl::isMouseButtonPressed(sf::Event event) {
	int mouseX = sf::Mouse::getPosition(MainWindow).x;
	int mouseY = sf::Mouse::getPosition(MainWindow).y;
	isMouseHold = 1;
	if (view->isInUndoButton(mouseX, mouseY)) {
		if (selfmove) {
			game->Undo();
			isChosen = 0;
			status = Start;
			selfmove--;
		}
		return;
	}
	else if (view->isInResetButton(mouseX, mouseY)) {
		Init();
		return;
	}
	else if (view->isInRotateButton(mouseX, mouseY)) {
		isRotate ^= 1;
		return;
	}
	else if (view->isInInputButton(mouseX, mouseY)) {
		status = CSM;
		return;
	}
	else if (view->isInManualLeftButton(mouseX, mouseY)) {
		Manualscroll = std::max(0, Manualscroll - 1);
		return;
	}
	else if (view->isInManualRightButton(mouseX, mouseY)) {
		int len = csmManual.size() / 6;
		Manualscroll = std::min(len, Manualscroll + 1);
		return;
	}
	else if (ManualID and view->isInManualWindow(mouseX, mouseY)) {
		int tmp = ManualsetID;
		ManualsetID = view->isInManualWindow(mouseX, mouseY);
		int len = csmManual.size()*2 - (csmManual.back().BlackMove == "-1");
		if (Manualscroll * 12 + ManualsetID <= len) {
			fakeManualscroll = Manualscroll;
			int nowManualsetID = Manualscroll * 12 + ManualsetID;
			//Init();
			if (preManualsetID == -1) {
				Init();
				selfmove = 0;
				int i;
				for (i = 0; i < nowManualsetID/2; i++) {
					game->ManualMove(csmManual[i].WhiteMove);
					game->ManualMove(csmManual[i].BlackMove);
				}
				if (nowManualsetID % 2 == 1)
					game->ManualMove(csmManual[i].WhiteMove);
			}
			else if (nowManualsetID > preManualsetID) {
				for (int s = 0; s < selfmove; s++) {
					game->Undo();
				}
				selfmove = 0;
				status = Start;
				int i = preManualsetID;
				for (i; i < nowManualsetID; i++) {
					if (i % 2 == 0) game->ManualMove(csmManual[i / 2].WhiteMove);
					else game->ManualMove(csmManual[i / 2].BlackMove);
				}
			}
			else if(nowManualsetID < preManualsetID){
				int i = preManualsetID;
				for (int s = 0; s < selfmove; s++) {
					game->Undo();
				}
				selfmove = 0;
				status = Start;
				for (i; i > nowManualsetID; i--) {
					game->Undo();
				}
				status = Start;
			}
			else {
				for (int s = 0; s < selfmove; s++) {
					game->Undo();
				}
				selfmove = 0;
				status = Start;
			}
			preManualsetID = Manualscroll * 12 + ManualsetID;
			isChosen = 0;
		}
		else {
			ManualsetID = tmp;
		}
		return;
	}
	if (event.mouseButton.button == sf::Mouse::Left and isChosen) {
		PiecetoX = (mouseY - 10) / gap;
		PiecetoY = (mouseX - 10) / gap;
		if (isRotate) {
			PiecetoX = 7 - PiecetoX;
			PiecetoY = 7 - PiecetoY;
		}
		isChosen = 0;
		if (game->isMoveValid(PieceBx, PieceBy, PiecetoX, PiecetoY)) {
			isDrag = 0; selfmove++;
			if (game->getBoard().GetPieceID(PieceBx, PieceBy) == Black_King) {
				if (game->isBlackKingCastling() and PiecetoY - PieceBy == 2) {
					game->Move(0, 7, 0, 5);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else if (game->isBlackQueenCastling() and PieceBy - PiecetoY == 2) {
					game->Move(0, 0, 0, 3);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else {
					isChosenPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
				}
			}
			else if (game->getBoard().GetPieceID(PieceBx, PieceBy) == White_King) {
				if (game->isWhiteKingCastling() and PiecetoY - PieceBy == 2) {
					game->Move(7, 7, 7, 5);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else if (game->isWhiteQueenCastling() and PieceBy - PiecetoY == 2) {
					game->Move(7, 0, 7, 3);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else {
					isChosenPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
				}
			}
			else {
				isChosenPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
				game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
			}
			if (game->isPromotion()) {
				status = Promotion;
			}
			if (game->isBlackWin() || game->isWhiteWin())
				status = GameOver;
			if (game->isStaleMate())
				status = GameOver;
			return;
		}
	}
	if (event.mouseButton.button == sf::Mouse::Left and !isDrag) {
		if (status != GameOver) {
			for (sf::Sprite& tmp : view->getSpriteItem()) {
				if (tmp.getGlobalBounds().contains(mouseX, mouseY)) {
					isDrag = isChosen = 1;
					isDragPiece = isChosenPiece = &tmp;
					PiecePosBx = PieceBx = tmp.getPosition().y;
					PiecePosBy = PieceBy = tmp.getPosition().x;
					PieceBx = (PieceBx - 10) / gap;
					PieceBy = (PieceBy - 10) / gap;
					if (isRotate) {
						PiecePosBx = 1165 - PiecePosBx;
						PiecePosBy = 1800 - PiecePosBy;
						PieceBx = 7 - PieceBx;
						PieceBy = 7 - PieceBy;
					}
				}
			}
		}
	}
}
void WindowControl::isMouseButtonReleased(sf::Event event) {
	int mouseX = sf::Mouse::getPosition(MainWindow).x;
	int mouseY = sf::Mouse::getPosition(MainWindow).y;
	isMouseHold = 0;
	PiecetoX = (mouseY-10) / gap;
	PiecetoY = (mouseX-10) / gap;
	if (isRotate) {
		PiecetoX = 7 - PiecetoX;
		PiecetoY = 7 - PiecetoY;
	}
	if (isDrag) {
		isDrag = 0;
		if (game->isMoveValid(PieceBx, PieceBy, PiecetoX, PiecetoY)) {
			isChosen = 0; selfmove++;
			if (game->getBoard().GetPieceID(PieceBx, PieceBy) == Black_King) {
				if (game->isBlackKingCastling() and PiecetoY-PieceBy==2) {
					game->Move(0, 7, 0, 5);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else if (game->isBlackQueenCastling() and PieceBy-PiecetoY==2) {
					game->Move(0, 0, 0, 3);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else {
					isDragPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
				}
			}
			else if(game->getBoard().GetPieceID(PieceBx, PieceBy) == White_King){
				if (game->isWhiteKingCastling() and PiecetoY - PieceBy == 2) {
					game->Move(7, 7, 7, 5);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else if (game->isWhiteQueenCastling() and PieceBy - PiecetoY==2) {
					game->Move(7, 0, 7, 3);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY, 1);
					game->ChangeTurn();
				}
				else {
					isDragPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
					game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
				}
			}
			else {
				isDragPiece->setPosition(BeginY + PiecetoY * gap, BeginX + PiecetoX * gap);
				game->Move(PieceBx, PieceBy, PiecetoX, PiecetoY);
			}
		}
		else {
			isDragPiece->setPosition(PiecePosBy, PiecePosBx);
		}

		if (game->isPromotion()) {
			status = Promotion;
		}
		if (game->isBlackWin() || game->isWhiteWin())
			status = GameOver;
		if (game->isStaleMate())
			status = GameOver;
	}
	
}
void WindowControl::MouseDrag(sf::Event event) {
	int mouseX = sf::Mouse::getPosition(MainWindow).x;
	int mouseY = sf::Mouse::getPosition(MainWindow).y;
	isDragPiece->setPosition(mouseX-MouseAdjustX, mouseY-MouseAdjustY);
}
void WindowControl::Draw() {
	int mouseX = sf::Mouse::getPosition(MainWindow).x;
	int mouseY = sf::Mouse::getPosition(MainWindow).y;
	if (fakeManualscroll == Manualscroll)
		view->DrawManual(csmManual, Manualscroll, ManualsetID);
	else
		view->DrawManual(csmManual, Manualscroll, 0);
	view->Draw(isDrag, isRotate);
	view->DrawButton(mouseX, mouseY, isMouseHold, isDrag);
	if (isChosen) {
		view->DrawMoveHint(PieceBx, PieceBy, isRotate);
		view->DrawDragPiece(*isChosenPiece);
	}
	if (isDrag) {
		view->DrawMoveHint(PieceBx, PieceBy, isRotate);
		view->DrawDragPiece(*isDragPiece);
	}
}
void WindowControl::MouseHoldEvent() {
	sf::Event event;
	int mouseX = sf::Mouse::getPosition(MainWindow).x;
	int mouseY = sf::Mouse::getPosition(MainWindow).y;
	while (MainWindow.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			isMouseButtonPressed(event);
		}
		else if (event.type == sf::Event::MouseButtonReleased) {
			isMouseButtonReleased(event);
		}
		else if (event.type == sf::Event::Closed) {
			status = Exit;
			break;
		}
		if (isDrag) MouseDrag(event);
	}
}
void WindowControl::SubHoldEvent(sf::RenderWindow& SubWindow) {
	sf::Event event;
	bool ischosen = 0;
	while (SubWindow.pollEvent(event)) {
		view->DrawSubWindow(SubWindow);
		if (event.type == sf::Event::MouseButtonPressed) {
			if (event.mouseButton.button == sf::Mouse::Left) {
				int mouseX = sf::Mouse::getPosition(SubWindow).x;
				int mouseY = sf::Mouse::getPosition(SubWindow).y;
				if (mouseY >= 73 and mouseY <= 219) {
					if (mouseX >= 73 and mouseX <= 219) {
						if (game->isTurn() == black) promotionID = White_Knight;
						else promotionID = Black_Knight;
					}
					else if (mouseX > 219 and mouseX <= 365) {
						if (game->isTurn() == black) promotionID = White_Bishop;
						else promotionID = Black_Bishop;
					}
					else if (mouseX > 365 and mouseX <= 511) {
						if (game->isTurn() == black) promotionID = White_Rook;
						else promotionID = Black_Rook;
					}
					else if (mouseX > 511 and mouseX <= 657) {
						if (game->isTurn() == black) promotionID = White_Queen;
						else promotionID = Black_Queen;
					}
					ischosen = 1;
				}
			}
		}
	}
	if (ischosen) status = Start;
}