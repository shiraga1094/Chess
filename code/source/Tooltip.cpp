#include "Tooltip.h"

Tooltip::Tooltip(sf::RenderWindow& window): Window(window) {
	font.loadFromFile("arial.ttf");
	text.setFont(font);
	text.setFillColor(sf::Color::White);
	text.setCharacterSize(25);
	nowString = "";
	nowtime = pretime = NULL;
	totaltime = 1000;
	waittime = 1000;
	holdmouseX = holdmouseY = NULL;
	nowvisibility = 0;
	maxvisibility = 180;
	ishold = 0;
	lock = 1;
}
void Tooltip::SetTooltip(std::string SS, double time) {
	lock = 0;
	totaltime = time;
	if (nowString == SS) return;
	nowString = SS;
	text.setString(SS);
	nowWidth = text.getGlobalBounds().width;
	TooltipFrame = sf::RectangleShape(sf::Vector2f(6 + nowWidth, 30));
	ishold = 0;
}
void Tooltip::Draw() {
	int mouseX = sf::Mouse::getPosition(Window).x;
	int mouseY = sf::Mouse::getPosition(Window).y;
	nowtime = clock();
	if (ishold==0 and !lock) {
		nowvisibility = 0;
		ishold = 1;
		holdmouseX = mouseX;
		holdmouseY = mouseY;
		pretime = nowtime;
		TooltipFrame.setPosition(mouseX- nowWidth, mouseY + 30);
		text.setPosition(3+mouseX- nowWidth, mouseY + 32);
		Window.draw(text);
	}
	else {
		if(holdmouseX!=mouseX and holdmouseY!=mouseY) {
			ishold = 0;
			lock = 1;
			Dissappear();
		}
		else if (nowtime - pretime > waittime) {
			Appear();
		}
	}
}
void Tooltip::Appear() {
	double len = maxvisibility / totaltime;
	nowvisibility += len;
	if (nowvisibility > maxvisibility) nowvisibility = maxvisibility;
	TooltipFrame.setFillColor(sf::Color(0, 0, 0, nowvisibility));
	text.setFillColor(sf::Color(255, 255, 255, nowvisibility));
	Window.draw(TooltipFrame);
	Window.draw(text);
}
void Tooltip::Dissappear() {
	double len = maxvisibility / totaltime;
	nowvisibility -= len;
	if (nowvisibility < 0) nowvisibility = 0;
	TooltipFrame.setFillColor(sf::Color(0, 0, 0, nowvisibility));
	text.setFillColor(sf::Color(255, 255, 255, nowvisibility));
	Window.draw(TooltipFrame);
	Window.draw(text);
}