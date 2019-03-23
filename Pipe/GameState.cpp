#include <sstream>
#include <iostream>

#include "GameState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    GameState::GameState(GameDataRef data) : m_Data (std::move( data ))
    {
    }

    void GameState::Init()
    {
        std::cout << "Game state" << std::endl;
        m_Data->assests.LoadTexture( "Game Background",
                                     GAME_BACKGROUND_FILEPATH );
        m_Data->assests.LoadTexture( "Pipe Up",
                                     PIPE_UP_FILEPATH );
        m_Data->assests.LoadTexture( "Pipe Down",
                                     PIPE_DOWN_FILEPATH );

        m_Pipe = new Pipe( m_Data );

        m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Game Background" ));
        // m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Game Background" ));
    }

    void GameState::HandleInput()
    {
        sf::Event event;

        while (m_Data->window.pollEvent( event ))
        {
            if ( sf::Event::Closed == event.type )
            {
                m_Data->window.close();
            }

            if ( m_Data->input.IsSpriteClicked( m_BackgroundSprite, sf::Mouse::Left,
                    m_Data->window ))
            {
                m_Pipe->SpawnInvisiblePipe();
                m_Pipe->SpawnBottomPipe();
                m_Pipe->SpawnTopPipe();
            }
        }
    }

    void GameState::Update(float dt)
    {
        m_Pipe->MovePipes(dt);
    }

    void GameState::Draw(float dt)
    {
        m_Data->window.clear();

        m_Data->window.draw( m_BackgroundSprite );
        // m_Data->window.draw( );
        m_Pipe->DrawPipes();
        m_Data->window.display();
    }

}