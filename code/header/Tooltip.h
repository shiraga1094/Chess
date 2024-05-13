#ifndef _Tooltip_
#define _Tooltip_
#include <SFML/Graphics.hpp>
#include <iostream>
#include <algorithm>
#include <windows.h>

class Tooltip {
private:
	sf::RenderWindow& Window;
	sf::RectangleShape TooltipFrame;
	sf::Font font;
	sf::Text text;
	std::string nowString;
	int nowWidth;
	double pretime, nowtime;
	double totaltime, waittime;
	double nowvisibility, maxvisibility;
	int holdmouseX, holdmouseY;
	bool ishold;
	bool lock;

public:
	Tooltip(sf::RenderWindow& window);
	void SetTooltip(std::string SS, double time);
	void Draw();
	void Appear();
	void Dissappear();
};





#endif
