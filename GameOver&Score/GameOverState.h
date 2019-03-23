#pragma once

#include <SFML/Graphics.hpp>
#include "State.h"
#include "Game.h"

namespace SSEngine
{
    class GameOverState : public State
    {
    public:
        GameOverState(GameDataRef data, int score);

        void Init();

        void HandleInput();
        void Update( float dt );
        void Draw( float dt );

    private:
        GameDataRef m_Data;

        sf::Sprite m_BackgroundSprite;
        sf::Sprite m_GameOverTitle;
        sf::Sprite m_GameOverContainer;
        sf::Sprite m_RetryButton;

        sf::Text m_ScoreText;
        sf::Text m_HighScoreText;

        int m_Score;
        int m_HighScore;
    };
}