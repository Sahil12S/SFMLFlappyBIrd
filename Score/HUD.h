#pragma once

#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"

namespace SSEngine
{
    class HUD
    {
    public:
        HUD( GameDataRef data );

        void Draw();
        void UpdateScore( int score );

    private:
        GameDataRef m_Data;

        sf::Text m_ScoreText;
    };
}