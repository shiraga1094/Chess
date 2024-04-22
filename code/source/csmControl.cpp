#include "csmControl.h"

csmControl::csmControl(Game* game){
	this->game = game;
	path = "./Manual/ChessManual.csm";
	csmView* oldview = csmview;
	csmview = new csmView();
	delete oldview;
	scrollcnt = ChosenID = 0;
	scorllX = scrollY = 0;
	filename = {};
	isChosen = 1;
	fakeChosen = isClosed = isPressed = 0;
	FileInput();
}
std::vector<csmData> csmControl::GetcsmManual(int ID) {
	return csmManual[ID];
}
void csmControl::FileInput() {
	csm.open(path, std::ios::in);
	std::string name;
	std::string obj;
	for (int i = 0; csm>>name and i < 100; i++) {
		filename.push_back(name);
		std::vector<csmData> Manual;
		csmData tmp;
		while (csm >> obj and obj!="#") {
			if ('0' <= obj[0] and obj[0] <= '9') {

				tmp.No = obj;
				tmp.WhiteMove = tmp.BlackMove = "-1";
			}
			else if (tmp.WhiteMove == "-1") {
				tmp.WhiteMove = obj;
			}
			else {
				tmp.BlackMove = obj;
				Manual.push_back(tmp);
			}
		}
		Manual.push_back(tmp);
		csmManual.push_back(Manual);
	}
	csm.close();
}
int csmControl::Run(sf::RenderWindow& csmWindow) {
	isChosen = isClosed = 0;
	csmWindow.requestFocus();
	while (!isChosen and !isClosed) {
		MouseHoldEvent(csmWindow);
		csmview->UpdateFileList(filename, scrollcnt);
		csmWindow.clear(sf::Color(255, 199, 142, 1));
		Draw(csmWindow);
		csmWindow.display();
	}
	csmWindow.close();
	return fakeChosen + scrollcnt * blankamount;
}
void csmControl::MouseHoldEvent(sf::RenderWindow& csmWindow) {
	sf::Event event;
	while (csmWindow.pollEvent(event)) {
		if (event.type == sf::Event::MouseButtonPressed) {
			isMouseButtonPressed(csmWindow,event);
		}
		if (event.type == sf::Event::MouseButtonReleased) {
			isPressed = 0;
		}
		if (event.type == sf::Event::Closed) {
			isClosed = 1;
			break;
		}
	}
}
void csmControl::isMouseButtonPressed(sf::RenderWindow& csmWindow, sf::Event event) {
	int mouseX = sf::Mouse::getPosition(csmWindow).x;
	int mouseY = sf::Mouse::getPosition(csmWindow).y;
	if (event.mouseButton.button==sf::Mouse::Left){
		isPressed = 1;
		if(csmview->inFileList(mouseX, mouseY)) {
			if (fakeChosen==0) {
				int tmp=csmview->inFileBlank(mouseX, mouseY, filename.size(), scrollcnt);
				fakeChosen = tmp;
			}
			else {
				int Chosen= csmview->inFileBlank(mouseX, mouseY, filename.size(), scrollcnt);
				if (fakeChosen == Chosen) {
					isChosen = 1;
				}
				else {
					fakeChosen = Chosen;
				}
			}
		}
		else {
			fakeChosen = 0;
		}

		if (csmview->inDownButton(mouseX, mouseY)) {
			if (scrollcnt + 1 > filename.size() / blankamount) return;
			else scrollcnt++;
		}
		else if (csmview->inUpButton(mouseX, mouseY)) {
			if (scrollcnt - 1 < 0) return;
			else scrollcnt--;
		}
	}
}
void csmControl::Draw(sf::RenderWindow& csmWindow) {
	int mouseX = sf::Mouse::getPosition(csmWindow).x;
	int mouseY = sf::Mouse::getPosition(csmWindow).y;
	csmview->Draw(csmWindow, fakeChosen, mouseX, mouseY, isPressed);
}