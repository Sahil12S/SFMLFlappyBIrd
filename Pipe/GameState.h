#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"

namespace SSEngine
{
    class GameState : public State
    {
    public:
        GameState(GameDataRef data);
        // ~GameState();

        void Init();

        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

    private:
        GameDataRef m_Data;

        sf::Sprite m_BackgroundSprite;

        Pipe* m_Pipe;
    };
}