#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace SSEngine
{
    class SplashState : public State
    {
    public:
        SplashState(GameDataRef data);
        // ~SplashState();

        void Init();

        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

    private:
        GameDataRef m_Data;

        sf::Clock m_Clock;

        sf::Sprite m_BackgroundSprite;
    };
}