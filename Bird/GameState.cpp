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
        m_Data->assests.LoadTexture( "Land",
                                     LAND_FILEPATH );
        m_Data->assests.LoadTexture( "Bird Frame 1",
                                     BIRD_FRAME_1_FILEPATH );
        m_Data->assests.LoadTexture( "Bird Frame 2",
                                     BIRD_FRAME_2_FILEPATH );
        m_Data->assests.LoadTexture( "Bird Frame 3",
                                     BIRD_FRAME_3_FILEPATH );
        m_Data->assests.LoadTexture( "Bird Frame 4",
                                     BIRD_FRAME_4_FILEPATH );

        m_Pipe = new Pipe( m_Data );
        m_Land = new Land( m_Data );
        m_Bird = new Bird( m_Data );

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
                m_Bird->Tap();
            }
        }
    }

    void GameState::Update(float dt)
    {
        m_Pipe->MovePipes( dt );
        m_Land->MoveLand( dt );

        if ( m_Clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY )
        {
            m_Pipe->RandomizePipeOffset();
            // m_Pipe->SpawnInvisiblePipe();
            m_Pipe->SpawnBottomPipe();
            m_Pipe->SpawnTopPipe();

            m_Clock.restart();
        }
        m_Bird->Animate( dt );
        m_Bird->Update( dt );
    }

    void GameState::Draw(float dt)
    {
        m_Data->window.clear();

        m_Data->window.draw( m_BackgroundSprite );

        m_Pipe->DrawPipes();
        m_Land->DrawLand();
        m_Bird->Draw();

        m_Data->window.display();
    }

}