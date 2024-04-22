/*
Designed by 竹北高中30630盧人豪
*/
#include <Windows.h>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "WindowControl.h"
#include "Input.h"

sf::Image icon; 
PieceInput input;

int main()
{
    ShowWindow(GetConsoleWindow(), SW_HIDE);
    
    icon = input.GetRandomIcon();
    sf::RenderWindow window(sf::VideoMode(1800, 1165), "Chess", sf::Style::Close);
    window.setFramerateLimit(60);
    window.setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
    
    WindowControl WindowControl(window);
    WindowControl.Init();
    WindowControl.Run();
    window.close();
    
    return EXIT_SUCCESS;
}