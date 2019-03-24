#include "Land.h"
#include "DEFINITIONS.h"


namespace SSEngine
{
    Land::Land(GameDataRef data) : m_Data (std::move( data ))
    {
        sf::Sprite sprite1( m_Data->assets.GetTexture( "Land" ) );
        sf::Sprite sprite2( m_Data->assets.GetTexture( "Land" ) );

        sprite1.setPosition( 0, m_Data->window.getSize().y - sprite1.getGlobalBounds().height );
        sprite2.setPosition( sprite1.getGlobalBounds().width,
                m_Data->window.getSize().y - sprite2.getGlobalBounds().height );

        m_LandSprites.push_back(sprite1);
        m_LandSprites.push_back(sprite2);
    }

    void Land::MoveLand(float dt)
    {
        for (unsigned short int i = 0; i < m_LandSprites.size(); i++)
        {
            float movement = PIPE_MOVEMENT_SPEED * dt;
            m_LandSprites.at( i ).move( -movement, 0.0f );

            if ( m_LandSprites.at( i ).getPosition().x  < 0 - m_LandSprites.at(i).getGlobalBounds().width )
            {
                sf::Vector2f position( m_Data->window.getSize().x, m_LandSprites.at(i).getPosition().y );

                m_LandSprites.at( i ).setPosition( position );
            }
        }
    }

    void Land::DrawLand()
    {
        for (unsigned short int i = 0; i < m_LandSprites.size(); i++)
        {
            m_Data->window.draw( m_LandSprites.at(i) );
        }
    }

    const std::vector<sf::Sprite>& Land::GetSprites() const
    {
        return m_LandSprites;
    }
}

