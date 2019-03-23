#include "Flash.h"

namespace SSEngine
{
    Flash::Flash(GameDataRef data) : m_Data( move( data ) )
    {
        m_Shape = sf::RectangleShape( sf::Vector2f( m_Data->window.getSize() ) );

        // Make it invisible while we are playing or start of game.
        m_Shape.setFillColor( sf::Color( 255, 255, 255, 0 ) );

        m_FlashOn = true;
    }

    void Flash::Show(float dt)
    {
        if ( m_FlashOn )
        {
            int alpha = ( int )( m_Shape.getFillColor().a + ( FLASH_SPEED * dt ) );

            if ( alpha >= 255 )
            {
                alpha = 255;
                m_FlashOn = false;
            }

            m_Shape.setFillColor( sf::Color( 255, 255, 255, alpha ) );
        }
        else
        {
            int alpha = ( int )( m_Shape.getFillColor().a - ( FLASH_SPEED * dt ) );

            if ( alpha < 0 )
            {
                alpha = 0;
                m_FlashOn = false;
            }

            m_Shape.setFillColor( sf::Color( 255, 255, 255, alpha ) );
        }
    }

    void Flash::Draw()
    {
        m_Data->window.draw( m_Shape );
    }
}