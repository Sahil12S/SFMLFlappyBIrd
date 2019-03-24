#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    class Flash
    {
    public:
        Flash( GameDataRef data );

        void Show( float dt );
        void Draw();

    private:
        GameDataRef m_Data;

        sf::RectangleShape m_Shape;

        bool m_FlashOn;
    };
}