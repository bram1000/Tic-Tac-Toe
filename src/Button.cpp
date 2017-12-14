#include "Button.h"
#include <SFML/Graphics.hpp>

Button::Button()
{
    shape.setSize(sf::Vector2f(100,100));
}

bool Button::IsMouseInButton(sf::RenderWindow& window)
{
    int x = shape.getPosition().x;
    int y = shape.getPosition().y;

    int mx = sf::Mouse::getPosition(window).x;
    int my = sf::Mouse::getPosition(window).y;

    bool IsInX = mx>x && mx<x+100;
    bool IsInY = my>y && my<y+100;

    return IsInX && IsInY;
}
