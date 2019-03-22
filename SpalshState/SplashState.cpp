#include <sstream>
#include <iostream>

#include "SplashState.h"
#include "DEFINITIONS.h"

namespace SSEngine
{
    SplashState::SplashState(GameDataRef data) : m_Data (std::move( data ))
    {
    }

    void SplashState::Init()
    {
        m_Data->assests.LoadTexture( "Splash State Background",
                SPLASH_SCENE_BACKGROUND_FILEPATH );

        m_BackgroundSprite.setTexture( this->m_Data->assests.GetTexture( "Splash State Background" ));
    }

    void SplashState::HandleInput()
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

    void SplashState::Update(float dt)
    {
        if ( m_Clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME )
        {
            std::cout << "Go to Main Menu" << std::endl;
        }
    }

    void SplashState::Draw(float dt)
    {
        m_Data->window.clear();

        m_Data->window.draw( m_BackgroundSprite );
        m_Data->window.display();
    }

}