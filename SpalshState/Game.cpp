#include "Game.h"
#include "SplashState.h"

namespace SSEngine
{
    Game::Game(int width, int height, std::string title)
    {
        m_Data->window.create( sf::VideoMode( width, height ), title, sf::Style::Close | sf::Style::Titlebar );
        m_Data->machine.AddState( StateRef(new SplashState( this-> m_Data ) ) );
        this->Run();
    }

    void Game::Run()
    {
        float newTime, frameTime, interpolation;

        float currentTime = this->m_Clock.getElapsedTime().asSeconds();

        float accumulator = 0.0f;

        while ( this->m_Data->window.isOpen() )
        {
            this->m_Data->machine.ProcessStateChange();

            newTime  = this->m_Clock.getElapsedTime().asSeconds();

            // To handle different frame rates.
            frameTime = newTime - currentTime;

            if ( frameTime > 0.25f )
            {
                frameTime = 0.25f;
            }

            currentTime = newTime;
            accumulator += frameTime;

            while ( accumulator >= dt )
            {
                this->m_Data->machine.GetActiveState()->HandleInput();
                this->m_Data->machine.GetActiveState()->Update( dt );

                accumulator -= dt;
            }

            interpolation = accumulator / dt;
            this->m_Data->machine.GetActiveState()->Draw( interpolation );
        }
    }
}