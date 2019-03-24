#include <sstream>
#include <iostream>
#include <time.h>

#include "GameState.h"
#include "GameOverState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    GameState::GameState(GameDataRef data) : m_Data (std::move( data ))
    {
    }

    void GameState::Init()
    {
        // Load sound files
        m_Data->assets.LoadSound( "Gameplay Background Sound", GAMEPLAY_BACKGROUND_SOUND_FILEPATH );
        m_Data->assets.LoadSound( "Hit Sound", HIT_SOUND_FILEPATH );
        m_Data->assets.LoadSound( "Point Sound", POINT_SOUND_FILEPATH );
        m_Data->assets.LoadSound( "Wing Sound", WING_SOUND_FILEPATH );

        m_BackgroundSound.setBuffer( m_Data->assets.GetSoundBuffer( "Gameplay Background Sound" ) );
        m_HitSound.setBuffer( m_Data->assets.GetSoundBuffer( "Hit Sound" ) );
        m_PointSound.setBuffer( m_Data->assets.GetSoundBuffer( "Point Sound" ) );
        m_WingSound.setBuffer( m_Data->assets.GetSoundBuffer( "Wing Sound" ) );

        // std::cout << "Game state" << std::endl;
        m_Data->assets.LoadTexture( "Game Background",
                                     GAME_BACKGROUND_FILEPATH );
        m_Data->assets.LoadTexture( "Pipe Up",
                                     PIPE_UP_FILEPATH );
        m_Data->assets.LoadTexture( "Pipe Down",
                                     PIPE_DOWN_FILEPATH );
        m_Data->assets.LoadTexture( "Land",
                                     LAND_FILEPATH );
        m_Data->assets.LoadTexture( "Bird Frame 1",
                                     BIRD_FRAME_1_FILEPATH );
        m_Data->assets.LoadTexture( "Bird Frame 2",
                                     BIRD_FRAME_2_FILEPATH );
        m_Data->assets.LoadTexture( "Bird Frame 3",
                                     BIRD_FRAME_3_FILEPATH );
        m_Data->assets.LoadTexture( "Bird Frame 4",
                                     BIRD_FRAME_4_FILEPATH );
        m_Data->assets.LoadTexture( "Scoring Pipe",
                                     SCORING_PIPE_FILEPATH );
        m_Data->assets.LoadFont( "Flappy Font",
                                     FLAPPY_FONT_FILEPATH );

        m_Pipe = new Pipe( m_Data );
        m_Land = new Land( m_Data );
        m_Bird = new Bird( m_Data );
        m_Flash = new Flash( m_Data );
        m_Hud = new HUD( m_Data );

        m_BackgroundSprite.setTexture( this->m_Data->assets.GetTexture( "Game Background" ));

        m_Score = 0;
        m_Hud->UpdateScore( m_Score );

        m_Difficulty = PIPE_SPAWN_FREQUENCY;

        m_GameState = GameStates::eReady;
        m_BackgroundSound.setLoop( true );
        m_BackgroundSound.play();
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

            // if ( m_Data->input.IsSpriteClicked( m_BackgroundSprite, sf::Mouse::Left,
            //         m_Data->window ))
            if ( m_Data->input.isUpArrowClick( sf::Keyboard::Up ) )
            {
                if ( GameStates::eGameOver != m_GameState )
                {
                    m_GameState = GameStates ::ePlaying;
                    m_Bird->Tap();
                    m_WingSound.play();
                }
            }
        }
    }

    void GameState::Update(float dt)
    {
        if ( GameStates::eGameOver != m_GameState )
        {
            m_Bird->Animate( dt );
            m_Land->MoveLand( dt );
        }

        if ( GameStates::ePlaying == m_GameState )
        {
            // m_BackgroundSound.setLoop(true);

            m_Pipe->MovePipes(dt);

            if ( m_Clock.getElapsedTime().asSeconds() > m_Difficulty )
            {
                m_Pipe->RandomizePipeOffset();
                m_Pipe->SpawnInvisiblePipe();
                m_Pipe->SpawnBottomPipe();
                m_Pipe->SpawnTopPipe();
                m_Pipe->SpawnScoringPipe();

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
                    m_Clock.restart();
                    m_HitSound.play();
                    m_BackgroundSound.pause();
                }
            }

            std::vector<sf::Sprite> pipeSprites = m_Pipe->GetSprites();

            for ( unsigned int i = 0; i < pipeSprites.size(); i++ )
            {
                if ( collision.CheckSpriteCollision(m_Bird->GetSprites(), 0.625f, pipeSprites.at( i ), 1.0f ) )
                {
                    m_GameState = GameStates::eGameOver;
                    m_Clock.restart();
                    m_HitSound.play();
                    m_BackgroundSound.pause();
                }
            }

            if ( GameStates::ePlaying == m_GameState )
            {
                std::vector<sf::Sprite> &scoringSprites = m_Pipe->GetScoringSprites();
                for (unsigned int i = 0; i < scoringSprites.size(); i++)
                {
                    if (collision.CheckSpriteCollision(m_Bird->GetSprites(), 0.625f, scoringSprites.at(i), 1.0f))
                    {
                        m_Score++;
                        m_Hud->UpdateScore( m_Score );
                        m_PointSound.play();

                        scoringSprites.erase(scoringSprites.begin() + i);

                        if ( m_Score == BRONZE_MEDAL_SCORE || m_Score == SILVER_MEDAL_SCORE ||
                             m_Score == GOLD_MEDAL_SCORE || m_Score == PLATINUM_MEDAL_SCORE )
                        {
                            m_Difficulty *= DIFFICULTY_MULTIPLIER;
                        }
                    }
                    // m_PointSound.stop();
                }
            }
        }

        if ( GameStates::eGameOver == m_GameState )
        {
            m_Flash->Show( dt );

            if ( m_Clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS )
            {
                m_Data->machine.AddState( StateRef( new GameOverState( m_Data, m_Score ) ), true );
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
        m_Flash->Draw();

        m_Hud->Draw();

        m_Data->window.display();
    }
}