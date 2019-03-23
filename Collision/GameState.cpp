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

        m_GameState = GameStates::eReady;
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
                if ( GameStates::eGameOver != m_GameState )
                {
                    m_GameState = GameStates ::ePlaying;
                    m_Bird->Tap();
                }
            }
        }
    }

    void GameState::Update(float dt)
    {
        if ( GameStates::eGameOver != m_GameState )
        {
            m_Bird->Animate( dt );
            m_Land->MoveLand(dt);
        }

        if ( GameStates::ePlaying == m_GameState )
        {
            m_Pipe->MovePipes(dt);
            if (m_Clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
            {
                m_Pipe->RandomizePipeOffset();
                m_Pipe->SpawnInvisiblePipe();
                m_Pipe->SpawnBottomPipe();
                m_Pipe->SpawnTopPipe();

                m_Clock.restart();
            }
            m_Bird->Update( dt );

            // After bird is updated, check if there's a collision.
            std::vector<sf::Sprite> landSprites = m_Land->GetSprites();

            for ( unsigned int i = 0; i < landSprites.size(); i++ )
            {
                if ( collision.CheckSpriteCollision(m_Bird->GetSprites(), 0.8f, landSprites.at( i ), 1.0f ) )
                {
                    m_GameState = GameStates::eGameOver;
                }
            }

            std::vector<sf::Sprite> pipeSprites = m_Pipe->GetSprites();

            for ( unsigned int i = 0; i < pipeSprites.size(); i++ )
            {
                if ( collision.CheckSpriteCollision(m_Bird->GetSprites(), 0.625f, pipeSprites.at( i ), 1.0f ) )
                {
                    m_GameState = GameStates::eGameOver;
                }
            }
        }
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