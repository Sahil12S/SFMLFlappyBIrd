#pragma once

#include <SFML/Graphics.hpp>

namespace SSEngine
{
    class InputManager
    {
    public:
        InputManager() {}
        ~InputManager() {}

        bool IsSpriteClicked ( sf::Sprite object, sf::Mouse::Button button, sf::RenderWindow& window );
        bool isUpArrowClick( sf::Keyboard::Key key );

        sf::Vector2i GetMousePosition ( sf::RenderWindow& window );
    };
}
