#ifndef _Tutorial_View_H_
#define _Tutorial_View_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <utility>
#include "ID.h"
#include "Input.h"

class TutorialView {
private:
	const float BeginX = 10;
	const float BeginY = 10;
	const float gap = 131;
	sf::RenderWindow& TutorialWindow;
	PieceInput* input;
	sf::Sprite Board;
	std::vector<sf::Sprite> listButton;
	ID pieceID[6] = { White_Pawn,
		White_Knight,
		White_Bishop,
		White_Rook,
		White_Queen,
		White_King };
	sf::Sprite PieceButton[6];
	std::vector<sf::Sprite> SpecialMoveButton;
	std::vector<sf::Sprite> RuleButton;
	sf::RectangleShape ButtonBg;
	sf::CircleShape MoveHint;
	sf::RectangleShape PreviousSquare;
	sf::RectangleShape CheckSquare;
	sf::Font font;
	sf::Text HintTitle;
	sf::Text HintText;
	sf::RectangleShape CommandWindow;
public:
	TutorialView(sf::RenderWindow&);
	void Draw(int X, int Y, bool isPressed);
	void DrawButton(int X, int Y, bool isPressed);
	void DrawPieceTutorial(int X, int Y, bool isPressed, ID pieceID);
	void DrawPieceButton(int X, int Y, bool isPressed);
	void DrawPieceSpecialMove(int X, int Y, bool isPressed, int ID);
	void DrawSpecialMoveButton(int X, int Y, bool isPressed);
	void DrawRuleTutorial(int X, int Y, bool isPressed, int ID);
	void DrawRuleButton(int X, int Y, bool isPressed);
	bool isInListButton(int X, int Y, int ID);
	bool isInPieceButton(int X, int Y, int ID);
	bool isInSpecialMoveButton(int X, int Y, int ID);
	bool isInRuleButton(int X, int Y, int ID);
};

#endif
