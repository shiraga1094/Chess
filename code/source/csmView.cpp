#include "csmView.h"

csmView::csmView(sf::RenderWindow& window): csmwindow(window){
	font.loadFromFile("arial.ttf");
	csmFileList = sf::RectangleShape(sf::Vector2f(1000, 800));
	csmFileList.setPosition(100, 300);
	csmFileList.setFillColor(sf::Color(255, 235, 205));
	Tooltip* oldtip = tooltip;
	tooltip = new Tooltip(csmwindow);
	delete oldtip;

	for (int i = 0; i < blankamount; i++) {
		csmListBlank[i] = sf::RectangleShape(sf::Vector2f(796, 46));
		csmListBlank[i].setPosition(BeginblankX+2, BeginblankY + blankgap * i +2);
		csmListBlank[i].setFillColor(sf::Color(211, 211, 211));

		csmListBlankframe[i] = sf::RectangleShape(sf::Vector2f(800, 50));
		csmListBlankframe[i].setPosition(BeginblankX, BeginblankY + blankgap * i);
		csmListBlankframe[i].setFillColor(sf::Color::Black);

		csmListtxt[i].setFont(font);
		csmListtxt[i].setCharacterSize(30);
		csmListtxt[i].setFillColor(sf::Color::Black);
	}
	
	UpButton = sf::CircleShape(50, 3);
	UpButton.setFillColor(sf::Color(126, 192, 238));
	UpButton.setPosition(960, BeginblankY + blankgap * 3);
	DownButton = sf::CircleShape(50, 3);
	DownButton.setFillColor(sf::Color(126, 192, 238));
	DownButton.rotate(180);
	DownButton.setOrigin(DownButton.getGlobalBounds().width, DownButton.getGlobalBounds().height);
	DownButton.setPosition(975, BeginblankY + blankgap * 10);
	
}
void csmView::Draw(int fakeChosen, int X, int Y, bool isPressed) {
	csmwindow.draw(csmFileList);
	UpButton.setFillColor(sf::Color(126, 192, 238));
	if (inUpButton(X, Y)) {
		if (isPressed) UpButton.setFillColor(sf::Color(108, 166, 205));
		else UpButton.setFillColor(sf::Color(135, 206, 255));
	}
	DownButton.setFillColor(sf::Color(126, 192, 238));
	if (inDownButton(X, Y)) {
		if (isPressed) DownButton.setFillColor(sf::Color(108, 166, 205));
		else DownButton.setFillColor(sf::Color(135, 206, 255));
	}
	csmwindow.draw(UpButton);
	csmwindow.draw(DownButton);
	
	for (int i = 0; i < blankamount; i++) {
		csmwindow.draw(csmListBlankframe[i]);
		
		if (fakeChosen!=0 and i == fakeChosen - 1) continue;
		csmListBlank[i].setFillColor(sf::Color(211, 211, 211));
		csmwindow.draw(csmListBlank[i]);
		csmwindow.draw(csmListtxt[i]);
	}
	if (fakeChosen != 0) {
		csmListBlank[fakeChosen-1].setFillColor(sf::Color(190, 190, 190));
		csmwindow.draw(csmListBlank[fakeChosen-1]);
		csmwindow.draw(csmListtxt[fakeChosen-1]);
	}
}
bool csmView::inFileList(int X, int Y) {
	return csmFileList.getGlobalBounds().contains(X, Y);
}
bool csmView::inUpButton(int X, int Y) {
	return UpButton.getGlobalBounds().contains(X, Y);
}
bool csmView::inDownButton(int X, int Y) {
	return DownButton.getGlobalBounds().contains(X, Y);
}
int csmView::inFileBlank(int X, int Y, int size, int scrollcnt) {
	int ans = 0;
	for (ans;  ans < std::min(blankamount, size-scrollcnt*blankamount); ans++) {
		if (csmListBlank[ans].getGlobalBounds().contains(X, Y)) {
			return ans + 1;
		}
	}
	return 0;
}
void csmView::UpdateFileList(std::vector<std::string> filename, int scrollcnt) {
	//filename.push_back("test");
	int size = filename.size();
	for (int i = 0; i < blankamount; i++) {
		if (i + scrollcnt * blankamount < size) {
			csmListtxt[i].setString(filename[i + scrollcnt * blankamount]);
			csmListtxt[i].setOrigin(csmListtxt[i].getGlobalBounds().width / 2.0,
				csmListtxt[i].getGlobalBounds().height / 2.0);
			csmListtxt[i].setPosition(550, BeginblankY + blankgap * i + 15);
		}
		else {
			csmListtxt[i].setString("");
			csmListtxt[i].setOrigin(csmListtxt[i].getGlobalBounds().width / 2.0,
				csmListtxt[i].getGlobalBounds().height / 2.0);
			csmListtxt[i].setPosition(550, BeginblankY + blankgap * i + 15);
		}
	}

}
void csmView::End() {
	delete tooltip;
}