#include <sstream>
#include <iostream>

#include "GameOverState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    GameOverState::GameOverState(GameDataRef data, int score) : m_Data ( std::move( data ) ), m_Score ( score )
    {
    }

    void GameOverState::Init()
    {
        // std::cout << "Game over state" << std::endl;
        m_Data->assests.LoadTexture( "Game Over Background",
                                     GAME_OVER_BACKGROUND_FILEPATH );
        m_Data->assests.LoadTexture( "Game Over Title",
                                     GAME_OVER_TITLE_FILEPATH );
        m_Data->assests.LoadTexture( "Game Over Body",
                                     GAME_OVER_BODY_FILEPATH );

        m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Game Over Background" ));
        m_GameOverTitle.setTexture( this->m_Data->assests.GetTexture( "Game Over Title" ));
        m_GameOverContainer.setTexture( this->m_Data->assests.GetTexture( "Game Over Body" ));
        m_RetryButton.setTexture( this->m_Data->assests.GetTexture( "Play Button" ));

        m_GameOverContainer.setPosition( (
                m_Data->window.getSize().x / 2.0f - m_GameOverContainer.getGlobalBounds().width / 2.0f ),
                        (m_Data->window.getSize().y / 2.0f - m_GameOverContainer.getGlobalBounds().height / 2.0f ));

        m_GameOverTitle.setPosition( (
                m_Data->window.getSize().x / 2.0f - m_GameOverTitle.getGlobalBounds().width / 2.0f ),
                        ( m_GameOverContainer.getPosition().y - m_GameOverTitle.getGlobalBounds().height * 1.2f ) );

        m_RetryButton.setPosition( (
                m_Data->window.getSize().x / 2.0f - m_RetryButton.getGlobalBounds().width / 2.0f ),
                        m_GameOverContainer.getPosition().y + m_GameOverContainer.getGlobalBounds().height +
                        m_RetryButton.getGlobalBounds().height * 0.2f );

        m_ScoreText.setFont( m_Data->assests.GetFont( "Flappy Font" ) );
        m_ScoreText.setString( std::to_string( m_Score ) );
        m_ScoreText.setCharacterSize( 56 );
        m_ScoreText.setFillColor( sf::Color::White );
        m_ScoreText.setOrigin( m_ScoreText.getGlobalBounds().width / 2, m_ScoreText.getGlobalBounds().height / 2 );
        m_ScoreText.setPosition( m_Data->window.getSize().x / 10.0f * 7.25f, m_Data->window.getSize().y / 2.15f );

        m_HighScoreText.setFont( m_Data->assests.GetFont( "Flappy Font" ) );
        m_HighScoreText.setString( std::to_string( m_HighScore ) );
        m_HighScoreText.setCharacterSize( 56 );
        m_HighScoreText.setFillColor( sf::Color::White );
        m_HighScoreText.setOrigin( m_HighScoreText.getGlobalBounds().width / 2, m_HighScoreText.getGlobalBounds().height / 2 );
        m_HighScoreText.setPosition( m_Data->window.getSize().x / 10.0f * 7.25f, m_Data->window.getSize().y / 1.78f );

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

            if ( m_Data->input.IsSpriteClicked( m_RetryButton, sf::Mouse::Left, m_Data->window ) )
            {
                m_Data->machine.AddState( StateRef( new GameState( m_Data ) ), true );
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
        m_Data->window.draw( m_GameOverContainer );
        m_Data->window.draw( m_RetryButton );
        m_Data->window.draw( m_ScoreText );
        m_Data->window.draw( m_HighScoreText );
        m_Data->window.display();
    }

}