#pragma once

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "StateMachine.h"
#include "AssetManager.h"
#include "InputManager.h"

namespace SSEngine
{
    struct GameData
    {
        StateMachine machine;
        sf::RenderWindow window;
        AssetManager assets;
        InputManager input;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game
    {
    public:
        Game( int width, int height, std::string title );

    private:
        // Our frame rate
        const float dt = 1.0f / 60.0f;

        sf::Clock m_Clock;

        GameDataRef m_Data = std::make_shared<GameData>();

        void Run();
    };
}