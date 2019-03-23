#include <sstream>
#include <iostream>

#include "MainMenuState.h"
#include "GameState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    MainMenuState::MainMenuState(GameDataRef data) : m_Data (std::move( data ))
    {
    }

    void MainMenuState::Init()
    {
        std::cout << "Main menu state" << std::endl;
        m_Data->assests.LoadTexture( "Main Menu Background",
                                     MAIN_MENU_BACKGROUND_FILEPATH );
        m_Data->assests.LoadTexture( "Game Title",
                                     GAME_TITLE_FILEPATH );
        m_Data->assests.LoadTexture( "Play Button",
                                     PLAY_BUTTON_FILEPATH );

        m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Main Menu Background" ));
        m_TitleSprite.setTexture( this->m_Data->assests.GetTexture( "Game Title" ));
        m_PlayButtonSprite.setTexture( this->m_Data->assests.GetTexture( "Play Button" ));

        m_TitleSprite.setPosition( (SCREEN_WIDTH / 2.0f) - (m_TitleSprite.getGlobalBounds().width / 2.0f),
                m_TitleSprite.getGlobalBounds().height / 2.0f );

        m_PlayButtonSprite.setPosition( (SCREEN_WIDTH / 2.0f) - (m_PlayButtonSprite.getGlobalBounds().width / 2.0f),
                                        (SCREEN_HEIGHT / 2.0f) - m_TitleSprite.getGlobalBounds().height / 2.0f );
    }

    void MainMenuState::HandleInput()
    {
        sf::Event event;

        while (m_Data->window.pollEvent( event ))
        {
            if ( sf::Event::Closed == event.type )
            {
                m_Data->window.close();
            }

            if ( m_Data->input.IsSpriteClicked( m_PlayButtonSprite, sf::Mouse::Left, m_Data->window ) )
            {
                // Create a new state machine and mark true for replacing existing one
                m_Data->machine.AddState( StateRef( new GameState ( m_Data ) ), true );
            }
        }
    }

    void MainMenuState::Update(float dt)
    {

    }

    void MainMenuState::Draw(float dt)
    {
        m_Data->window.clear();

        m_Data->window.draw( m_BackgroundSprite );
        m_Data->window.draw( m_TitleSprite );
        m_Data->window.draw( m_PlayButtonSprite );
        m_Data->window.display();
    }

}