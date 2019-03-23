#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"
#include "Pipe.h"
#include "Land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"

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
        Land* m_Land;
        Bird* m_Bird;

        Collision collision;
        Flash* m_Flash;

        sf::Clock m_Clock;

        // In which state the game is
        int m_GameState;
    };
}