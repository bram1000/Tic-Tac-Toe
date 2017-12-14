#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Button
{
public:
    Button();

    bool IsMouseInButton(sf::RenderWindow& window);

    int x,y;
    sf::RectangleShape shape;
};

#endif
