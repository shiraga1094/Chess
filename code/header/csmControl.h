#ifndef _CSMWINDOW_H_
#define _CSMWINDOW_H_

#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
#include <vector>
#include "GameControl.h"
#include "csmView.h"
#include "ID.h"

struct csmData {
	std::string No;
	std::string WhiteMove, BlackMove;
};
class csmControl {
private:
	Game* game;
	csmView* csmview;
	std::ifstream csm;
	std::string path;
	std::vector<std::string> filename;
	std::vector<std::vector <csmData>> csmManual;
	int scrollcnt, ChosenID, fakeChosen;
	float scorllX, scrollY;
	bool isChosen, isClosed, isPressed;
public:
	csmControl (Game* game);
	std::vector<csmData> GetcsmManual(int ID);
	void FileInput();
	int Run(sf::RenderWindow& csmWindow);
	void MouseHoldEvent(sf::RenderWindow& csmWindow);
	void isMouseButtonPressed(sf::RenderWindow& csmWindow, sf::Event event);
	void Draw(sf::RenderWindow& csmWindow);
};





#endif

