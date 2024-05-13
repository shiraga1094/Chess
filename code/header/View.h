#ifndef _VIEW_H_
#define _VIEW_H_
#include <SFML/Graphics.hpp>
#include "Input.h"
#include "Tooltip.h"
#include "ID.h"
#include "GameControl.h"
#include "csmControl.h"
#include <sstream>
#include <cmath>
#include <iostream>
#include <vector>

class View {
private:
	PieceInput* input;
	Tooltip* tooltip;
	Game* game;
	sf::RenderWindow& MainWindow;
	sf::Sprite Board;
	std::vector<sf::Sprite> SpriteItem;
	std::vector<sf::Sprite> PromotionItem;
	sf::Sprite Rotate_Button;
	sf::Sprite Input_Button;
	sf::CircleShape MoveHint;
	sf::RectangleShape CheckSquare;
	sf::RectangleShape PreviousSquare[3];
	sf::Text PlayerTurnText;
	sf::Text Message;
	sf::RectangleShape UndoButton;
	sf::RectangleShape ResetButton;
	sf::RectangleShape RotateBackground;
	sf::RectangleShape InputBackground;
	float BeginX, BeginY, gap;

	std::vector<sf::RectangleShape> ManualLine;
	std::vector<sf::Text> Manualtext;
	std::vector<sf::Text> Manualcontent;
	sf::CircleShape ManualLeftButton, ManualRightButton;
	sf::RectangleShape ManualChosen;
	sf::Sprite ManualNextMoveButton;
	sf::Sprite ManualPreviousMoveButton;
	sf::RectangleShape ManualNextMoveBg;
	sf::RectangleShape ManualPreviousMoveBg;
	sf::Sprite ManualPlayButton, ManualPauseButton;
	sf::RectangleShape ManualPlaybg;

	sf::Sprite TutorialButton;
	sf::RectangleShape TutorialBg;

public:
	View(sf::RenderWindow&, Game*);
	void Init(bool isRotate);
	void Update(bool isRotate);
	void Draw(bool isDrag, bool isRotate);
	void DrawMoveHint(int X, int Y, bool isRotate);
	void DrawDragPiece(sf::Sprite& DragPiece);
	void DrawSubWindow(sf::RenderWindow& SubWindow);
	void DrawText(bool isRotate);
	void DrawButton(int X, int Y, bool isPressed, bool isDrag);
	void DrawManaulPlayButton(int X, int Y, bool isPressed, int isManaulPlay);
	void DrawManual(std::vector<csmData> csmManual, int Manualscroll, int ManualsetID);
	std::vector<sf::Sprite>& getSpriteItem();
	std::vector<sf::Sprite>& getPromotionItem();
	bool isInResetButton(int X, int Y);
	bool isInUndoButton(int X, int Y);
	bool isInRotateButton(int X, int Y);
	bool isInInputButton(int X, int Y);
	bool isInManualLeftButton(int X, int Y);
	bool isInManualRightButton(int X, int Y);
	int isInManualWindow(int X, int Y);
	bool isInManualNextMoveButton(int X, int Y);
	bool isInManualPreviousMoveButton(int X, int Y);
	bool isInManualPlayButton(int X, int Y, int isManaulPlay);
	bool isInTutorialButton(int X, int Y);
};

#endif
