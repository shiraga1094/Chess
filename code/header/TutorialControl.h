#ifndef _Tutorial_Control_H_
#define _Tutorial_Control_H_
#include <SFML/Graphics.hpp>
#include <iostream>
#include "TutorialView.h"

enum Tutorial_StatusID {
	Tutorial_Start = 1,
	Tutorial_Initial = 0,
	Tutorial_Exit = -1,
};
enum Page_StatusID {
	PieceTutorial = 1,
	PieceSpecialMove = 0,
	RuleTutorial = -1,
};
class TutorialControl {
private:
	const float BeginX = 3;
	const float BeginY = 3;
	const float gap = 131;
	bool isMouseHold;
	sf::RenderWindow TutorialWindow = { sf::VideoMode(BeginX + gap * 8, BeginY + gap*9.5), "ChessTutorial", sf::Style::Close };
	Tutorial_StatusID status;
	Page_StatusID pagestatus;
	TutorialView* View;
	ID mainPieceID;
	int SpecialMoveset;
	int RuleTutorialset;

	void HandleEvent();
public:
	TutorialControl();
	void Init();
	bool Run();
	void Draw();
	void isMouseButtonPressed(sf::Event event);
};


#endif
