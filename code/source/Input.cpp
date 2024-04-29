#include "Input.h"

PieceInput::PieceInput() {
	Black_King_Texture.loadFromFile("img/King_Black.png");
	Black_Queen_Texture.loadFromFile("img/Queen_Black.png");
	Black_Bishop_Texture.loadFromFile("img/Bishop_Black.png");
	Black_Knight_Texture.loadFromFile("img/Knight_Black.png");
	Black_Rook_Texture.loadFromFile("img/Rook_Black.png");
	Black_Pawn_Texture.loadFromFile("img/Pawn_Black.png");

	White_King_Texture.loadFromFile("img/King_White.png");
	White_Queen_Texture.loadFromFile("img/Queen_White.png");
	White_Bishop_Texture.loadFromFile("img/Bishop_White.png");
	White_Knight_Texture.loadFromFile("img/Knight_White.png");
	White_Rook_Texture.loadFromFile("img/Rook_White.png");
	White_Pawn_Texture.loadFromFile("img/Pawn_White.png");
	
	Board_Texture.loadFromFile("img/Board.png");
	RotateBoard_Texture.loadFromFile("img/Rotate_Board.png");
	Rotate_Arrow.loadFromFile("img/Rotate_Arrow.png");
	Input_Button.loadFromFile("img/input.png");

	font.loadFromFile("arial.ttf");
	PlayerTurnText.setFont(font);
	PlayerTurnText.setCharacterSize(50);
	PlayerTurnText.setPosition(1210, 110);
	PlayerTurnText.setFillColor(sf::Color::Black);

	Message.setFont(font);
	Message.setCharacterSize(50);
	Message.setPosition(1210, 170);
	Message.setFillColor(sf::Color::Black);
	
	CommandWindow = sf::RectangleShape(sf::Vector2f(570, 200));
	CommandWindow.setPosition(1200, 100);
	CommandWindow.setFillColor(sf::Color(255, 235, 205));

	ManualWindow = sf::RectangleShape(sf::Vector2f(500, 600));
	ManualWindow.setPosition(1270, 350);
	ManualWindow.setFillColor(sf::Color(255, 235, 205));

	MoveHint = sf::CircleShape(20);
	MoveHint.setFillColor(sf::Color(123, 122, 106, 240));

	CheckSquare = sf::RectangleShape(sf::Vector2f(146, 146));
	CheckSquare.setFillColor(sf::Color(255, 114, 86));

	PreviousSquare = sf::RectangleShape(sf::Vector2f(146, 146));
	PreviousSquare.setFillColor(sf::Color(152,251,152));

	ToSquare = sf::RectangleShape(sf::Vector2f(146, 146));
	ToSquare.setFillColor(sf::Color(152,251,152));

	UndoButton = sf::RectangleShape(sf::Vector2f(200, 100));
	UndoButton.setPosition(1250, 1000);
	UndoButton.setFillColor(sf::Color(238, 216, 174));
	Undotxt.setFont(font);
	Undotxt.setCharacterSize(30);
	Undotxt.setPosition(1310, 1035);
	Undotxt.setFillColor(sf::Color::Black);
	Undotxt.setString("Undo");

	ResetButton = sf::RectangleShape(sf::Vector2f(200, 100));
	ResetButton.setPosition(1535, 1000);
	ResetButton.setFillColor(sf::Color(238, 216, 174));
	Resettxt.setFont(font);
	Resettxt.setCharacterSize(30);
	Resettxt.setPosition(1600, 1035);
	Resettxt.setFillColor(sf::Color::Black);
	Resettxt.setString("Reset");

	ManualLine[0] = sf::RectangleShape(sf::Vector2f(500, 5));
	ManualLine[0].setFillColor(sf::Color::Black);
	for (int i = 1; i < 3; i++) {
		ManualLine[i] = sf::RectangleShape(sf::Vector2f(5, 525));
		ManualLine[i].setFillColor(sf::Color::Black);
	}
	Manualtext.setFont(font);
	Manualtext.setCharacterSize(30);
	Manualtext.setFillColor(sf::Color::Black);
	ManualButton = sf::CircleShape(30, 3);
	ManualButton.setFillColor(sf::Color(126, 192, 238));
	ManualChosen =  sf::RectangleShape(sf::Vector2f(225, 75));
	ManualChosen.setFillColor(sf::Color(211, 211, 211));
	ManualNextMove.loadFromFile("img/ManualNextMove.png");
	ManualPreviousMove.loadFromFile("img/ManualPreviousMove.png");
	ManualPlayButton.loadFromFile("img/ManualPlay.png");
	ManualPauseButton.loadFromFile("img/ManualPause.png");
}
sf::Sprite PieceInput::GetBoard() {
	return sf::Sprite(Board_Texture);
}
sf::Sprite PieceInput::GetRotateBoard() {
	return sf::Sprite(RotateBoard_Texture);
}
sf::Sprite PieceInput::GetRotateArrow() {
	return sf::Sprite(Rotate_Arrow);
}
sf::Sprite PieceInput::GetInputButton() {
	return sf::Sprite(Input_Button);
}
sf::Text PieceInput::GetPlayerTurnText() {
	return PlayerTurnText;
}
sf::Text PieceInput::GetMessage() {
	return Message;
}
sf::Sprite PieceInput::GetSprite(ID piece) {
	sf::Sprite sprite;
	switch (piece) {
	case White_Pawn:
		sprite=sf::Sprite(White_Pawn_Texture);
		break;
	case White_Knight:
		sprite=sf::Sprite(White_Knight_Texture);
		break;
	case White_Bishop:
		sprite=sf::Sprite(White_Bishop_Texture);
		break;
	case White_Rook:
		sprite=sf::Sprite(White_Rook_Texture);
		break;
	case White_Queen:
		sprite=sf::Sprite(White_Queen_Texture);
		break;
	case White_King:
		sprite=sf::Sprite(White_King_Texture);
		break;
	case Black_Pawn:
		sprite=sf::Sprite(Black_Pawn_Texture);
		break;
	case Black_Knight:
		sprite=sf::Sprite(Black_Knight_Texture);
		break;
	case Black_Bishop:
		sprite=sf::Sprite(Black_Bishop_Texture);
		break;
	case Black_Rook:
		sprite=sf::Sprite(Black_Rook_Texture);
		break;
	case Black_Queen:
		sprite=sf::Sprite(Black_Queen_Texture);
		break;
	case Black_King:
		sprite=sf::Sprite(Black_King_Texture);
		break;
	}
	return sprite;
}
sf::RectangleShape PieceInput::GetCommandWindow() {
	return CommandWindow;
}
sf::RectangleShape PieceInput::GetManualWindow() {
	return ManualWindow;
}
sf::RectangleShape PieceInput::GetCheckSquare() {
	return CheckSquare;
}
sf::RectangleShape PieceInput::GetPreviousSquare() {
	return PreviousSquare;
}
sf::RectangleShape PieceInput::GetToSquare() {
	return ToSquare;
}
sf::CircleShape PieceInput::GetMoveHint() {
	return MoveHint;
}
sf::RectangleShape PieceInput::GetUndoButton() {
	return UndoButton;
}
sf::RectangleShape PieceInput::GetResetButton() {
	return ResetButton;
}
sf::Text PieceInput::GetUndotxt() {
	return Undotxt;
}
sf::Text PieceInput::GetResettxt() {
	return Resettxt;
}
sf::Image PieceInput::GetRandomIcon() {
	sf::Image img;
	std::srand(time(NULL));
	int rnd = std::rand() % 6;
	switch (rnd + 1) {
		case 1:
			img.loadFromFile("img/Pawn_White.png"); break;
		case 2:
			img.loadFromFile("img/Knight_White.png"); break;
		case 3:
			img.loadFromFile("img/Bishop_White.png"); break;
		case 4:
			img.loadFromFile("img/Rook_White.png"); break;
		case 5:
			img.loadFromFile("img/Queen_White.png"); break;
		case 6:
			img.loadFromFile("img/King_White.png"); break;
	}
	return img;
}
std::vector<sf::RectangleShape> PieceInput::GetManualLine(int N) {
	std::vector<sf::RectangleShape> tmp;
	int Manualblank = 75;
	for (int i = 0; i < N-2; i++) {
		ManualLine[0].setPosition(1270, 420 + Manualblank * i);
		tmp.push_back(ManualLine[0]);
	}
	ManualLine[1].setPosition(1320, 350);
	ManualLine[2].setPosition(1545, 350);

	tmp.push_back(ManualLine[1]);
	tmp.push_back(ManualLine[2]);
	return tmp;
}
std::vector<sf::Text> PieceInput::GetManualtext(int N) {
	std::vector<sf::Text> tmp;
	int Manualblank = 75;
	for (int i = 0; i < N; i++) {
		std::string SS;
		SS = std::to_string(i+1);
		Manualtext.setString(SS);
		Manualtext.setCharacterSize(30);
		Manualtext.setPosition(1280, 440 + Manualblank * i);
		tmp.push_back(Manualtext);
	}
	tmp[tmp.size() - 2].setString("White");
	tmp[tmp.size() - 2].setPosition(1370, 350);
	tmp[tmp.size() - 2].setCharacterSize(50);
	tmp[tmp.size() - 1].setString("Black");
	tmp[tmp.size() - 1].setPosition(1600, 350);
	tmp[tmp.size() - 1].setCharacterSize(50);
	return tmp;
}
sf::CircleShape PieceInput::GetManualButton() {
	return ManualButton;
}
sf::RectangleShape PieceInput::GetManualChosen() {
	return ManualChosen;
}
sf::Sprite PieceInput::GetManualNextMoveButton() {
	return sf::Sprite(ManualNextMove);
}
sf::Sprite PieceInput::GetManualPreviousButton() {
	return sf::Sprite(ManualPreviousMove);
}
sf::Sprite PieceInput::GetManualPlayButton() {
	return sf::Sprite(ManualPlayButton);
}
sf::Sprite PieceInput::GetManualPauseButton() {
	return sf::Sprite(ManualPauseButton);
}