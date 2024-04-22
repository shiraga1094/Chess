#include <SFML/Graphics.hpp>
#include "View.h"
#include "GameControl.h"
#include "csmControl.h"
#include <iostream>
#include <cmath>
#include <vector>

const int BeginX = 10;
const int BeginY = 10;
const int MouseAdjustX = 60;
const int MouseAdjustY = 60;
const float gap = 146;
enum StatusID {
	CSM = 4,
	Uninitialize=3,
	Start = 2,
	Promotion = 1,
	GameOver = 0,
	Exit = -1,
};
class WindowControl {
private:
	sf::RenderWindow& MainWindow;
	sf::Sprite* isDragPiece;
	sf::Sprite* isChosenPiece;
	Game* game;
	View* view;
	csmControl* csmcontrol;
	bool isRotate;
	bool isMouseHold, isDrag, isChosen;
	float PiecePosBx, PiecePosBy;
	int PieceBx, PieceBy, PiecetoX, PiecetoY;
	int ManualID;
	int ManualsetID, Manualscroll;
	int fakeManualscroll;
	std::vector<csmData> csmManual;
	StatusID status;
	ID promotionID;

	void MouseHoldEvent();
	void SubHoldEvent(sf::RenderWindow& SubWindow);

public:
	WindowControl(sf::RenderWindow&);
	void Init();
	StatusID Run();
	void PromotionWindow();
	void isMouseButtonPressed(sf::Event event);
	void isMouseButtonReleased(sf::Event event);
	void MouseDrag(sf::Event event);
	void Draw();
};





