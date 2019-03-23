#include <sstream>
#include <iostream>

#include "GameOverState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    GameOverState::GameOverState(GameDataRef data) : m_Data (std::move( data ))
    {
    }

    void GameOverState::Init()
    {
        // std::cout << "Game over state" << std::endl;
        m_Data->assests.LoadTexture( "Game Over Background",
                                     GAME_OVER_BACKGROUND_FILEPATH );
        m_Data->assests.LoadTexture( "Game Over Title",
                                     GAME_OVER_TITLE_FILEPATH );

        m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Game Over Background" ));
        m_GameOverTitle.setTexture( this->m_Data->assests.GetTexture( "Game Over Title" ));

        m_GameOverTitle.setPosition( (SCREEN_WIDTH / 2.0f) - (m_GameOverTitle.getGlobalBounds().width / 2.0f),
                                     (SCREEN_HEIGHT / 2.0f) - (m_GameOverTitle.getGlobalBounds().height / 2.0f) );
    }

    void GameOverState::HandleInput()
    {
        sf::Event event;

        while (m_Data->window.pollEvent( event ))
        {
            if ( sf::Event::Closed == event.type )
            {
                m_Data->window.close();
            }
        }
    }

    void GameOverState::Update(float dt)
    {

    }

    void GameOverState::Draw(float dt)
    {
        m_Data->window.clear();

        m_Data->window.draw( m_BackgroundSprite );
        m_Data->window.draw( m_GameOverTitle );
        m_Data->window.display();
    }

}