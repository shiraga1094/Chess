#include "csmControl.h"

csmControl::csmControl(Game* game){
	this->game = game;
	path = "./Notation/ChessNotation.csm";
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
	if (!csm.is_open()) std::cout << "Error\n";
	std::string obj;
	std::string name;
	for (int i = 0; csm>>obj and i < 100; i++) {
		name = "";
		while (csm >> obj) {
			name += obj;
			if (obj[obj.length() - 1] == ']') break;
		}
		name = name.substr(1, name.length() - 3);
		filename.push_back(name);
		for (int i = 0; i < 6; i++) {
			name = "";
			while (csm >> obj) {
				name += obj;
				if (obj[obj.length() - 1] == ']') break;
			}
			name = name.substr(1, name.length() - 3);
		}
		std::vector<csmData> Manual;
		csmData tmp;
		while (csm >> obj) {
			if (obj == "1-0" or obj == "0-1" or obj == "1/2-1/2") break;
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
		if(tmp.BlackMove=="-1")
			Manual.push_back(tmp);
		csmManual.push_back(Manual);
	}
	csm.close();
}
int csmControl::Run(sf::RenderWindow& csmWindow) {
	isChosen = isClosed = 0;
	csmWindow.requestFocus();
	csmView* oldview = csmview;
	csmview = new csmView(csmWindow);
	delete oldview;
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
	csmview->Draw(fakeChosen, mouseX, mouseY, isPressed);
}
void csmControl::End() {
	delete csmview;
}