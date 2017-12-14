#include <vector>
#include <memory>
#include <SFML/Graphics.hpp>
#include "Button.h"


void ClearMap(char game_map[3][3])
{
    for(int x=0; x<3; ++x)
    for(int y=0; y<3; ++y)
        game_map[x][y] = ' ';
}

void ClearButtons(std::vector<std::shared_ptr<Button>> buttons, sf::Texture& normal)
{
    for(std::shared_ptr<Button> button : buttons)
        button->shape.setTexture(&normal);
}

char WhoWonTheGame(char game_map[3][3], sf::RectangleShape& line)
{
    for (int x=0; x<3; ++x)
        if (game_map[x][0]!=' ' && game_map[x][0]==game_map[x][1] && game_map[x][0]==game_map[x][2])
        {
            line.setOrigin(sf::Vector2f(0,0));
            line.setSize(sf::Vector2f(420,10));
            line.setPosition(x*140+95,20);
            line.setRotation(90);
            return game_map[x][0];
        }

    for (int y=0; y<3; ++y)
        if (game_map[0][y]!=' ' && game_map[0][y]==game_map[1][y] && game_map[0][y]==game_map[2][y])
        {
            line.setOrigin(sf::Vector2f(0,0));
            line.setSize(sf::Vector2f(420,10));
            line.setPosition(20,y*140+85);
            line.setRotation(0);
            return game_map[0][y];
        }

    if (game_map[0][0]!=' ' && game_map[0][0]==game_map[1][1] && game_map[0][0]==game_map[2][2])
    {
        line.setOrigin(sf::Vector2f(293,5));
        line.setSize(sf::Vector2f(586,10));
        line.setPosition(230,230);
        line.setRotation(45);
        return game_map[0][0];
    }

    if (game_map[2][0]!=' ' && game_map[2][0]==game_map[1][1] && game_map[2][0]==game_map[0][2])
    {
        line.setOrigin(sf::Vector2f(293,5));
        line.setSize(sf::Vector2f(586,10));
        line.setPosition(230,230);
        line.setRotation(315);
        return game_map[2][0];
    }

    return ' ';
}

bool IsMapFull(char game_map[3][3])
{
    for (int x=0; x<3; ++x)
    for (int y=0; y<3; ++y)
        if (game_map[x][y]==' ')
            return false;

    return true;
}


int main()
{
    /// Variables
    bool IsCrossesTurn = true;
    bool GamePaused = false;
    bool ShowLine = false;
    char game_map[3][3] = {};

    std::vector<std::shared_ptr<Button>> buttons;

    sf::RectangleShape line(sf::Vector2f(420,10));
    line.setFillColor(sf::Color(255,0,0,200));

    sf::Clock PauseClock;


    /// Resources
    sf::Texture cross, circle, normal;
    cross.loadFromFile("./img/cross.png");
    circle.loadFromFile("./img/circle.png");
    normal.loadFromFile("./img/normal.png");

    /// Make the buttons
    for (int x=0; x<3; ++x)
    for (int y=0; y<3; ++y)
    {
        std::shared_ptr<Button> button(new Button);
        buttons.push_back(button);
        button->shape.setPosition(sf::Vector2f(140*x+40, 140*y+40));
        button->shape.setTexture(&normal);
        button->x = x;
        button->y = y;
    }

    /// Clear the map
    ClearMap(game_map);

    /// SFML
    sf::RenderWindow window(sf::VideoMode(460,460),"Tic Tac Toe", sf::Style::Close);

    while (window.isOpen())
    {
        /// Events
        sf::Event event;
        while (window.pollEvent(event))
        {
            switch (event.type)
            {
                case sf::Event::Closed:
                    window.close();
                    break;

                case sf::Event::MouseButtonPressed:
                    if (!GamePaused)
                        if (event.mouseButton.button == sf::Mouse::Left)
                            for (std::shared_ptr<Button> button : buttons) // Loop through the buttons and see which one is pressed
                                if (button->IsMouseInButton(window))
                                    if (game_map[button->x][button->y] == ' ') // If spot available
                                    {
                                        button->shape.setTexture(IsCrossesTurn?&cross:&circle); // Set new texture
                                        game_map[button->x][button->y] = IsCrossesTurn?'x':'o'; // Change the map
                                        IsCrossesTurn = !IsCrossesTurn;
                                    }
                    break;
            }
        }


        if (WhoWonTheGame(game_map, line)!=' ')
        {
            if (!GamePaused)
            {
                GamePaused = true;
                ShowLine = true;
                PauseClock.restart();
            } else {
                if (PauseClock.getElapsedTime().asSeconds() >= 2)
                {
                    ClearMap(game_map);
                    ClearButtons(buttons, normal);
                    GamePaused = false;
                    ShowLine = false;
                    IsCrossesTurn = true;
                }
            }
        }

        if (IsMapFull(game_map))
        {
            if (!GamePaused)
            {
                GamePaused = true;
                PauseClock.restart();
            } else {
                if (PauseClock.getElapsedTime().asSeconds() >= 2)
                {
                    ClearMap(game_map);
                    ClearButtons(buttons, normal);
                    GamePaused = false;
                    IsCrossesTurn = true;
                }
            }
        }


        /// Rendering
        window.clear(sf::Color(40,40,40,255));

        for (std::shared_ptr<Button> button : buttons)
            window.draw(button->shape);

        if (ShowLine)
            window.draw(line);

        window.display();
    }
}
