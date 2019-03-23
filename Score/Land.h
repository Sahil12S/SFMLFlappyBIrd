#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "Game.h"

namespace SSEngine
{
    class Land
    {
    public:
        Land( GameDataRef data );

        void MoveLand( float dt );
        void DrawLand();

        const std::vector<sf::Sprite>& GetSprites() const;

    private:
        GameDataRef m_Data;
        std::vector<sf::Sprite> m_LandSprites;
    };
}