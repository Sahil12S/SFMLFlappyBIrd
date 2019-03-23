#pragma once

#include <vector>
#include <SFML/Graphics.hpp>
#include "DEFINITIONS.h"
#include "Game.h"

namespace SSEngine
{
    class Bird
    {
    public:
        Bird( GameDataRef data);
        void Draw();
        void Animate( float dt );

        void Update( float dt );

        void Tap();

        const sf::Sprite& GetSprites() const;

    private:
        GameDataRef m_Data;
        sf::Sprite m_BirdSprite;

        std::vector<sf::Texture> m_AnimationFrames;

        unsigned int m_AnimationIterator;

        sf::Clock m_Clock;
        sf::Clock m_MovementClock;

        int m_BirdState;

        float m_Rotation;

    };
}