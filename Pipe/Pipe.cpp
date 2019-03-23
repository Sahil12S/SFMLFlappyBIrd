#include "Pipe.h"

namespace SSEngine
{
    Pipe::Pipe(GameDataRef data) : m_Data (std::move(data))
    {
    }

    void Pipe::SpawnBottomPipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Pipe Up" ) );
        sprite.setPosition( m_Data->window.getSize().x,
                m_Data->window.getSize().y - sprite.getGlobalBounds().height );

        m_PipeSprites.push_back( sprite );
    }

    void Pipe::SpawnTopPipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Pipe Down" ) );
        sprite.setPosition( m_Data->window.getSize().x, 0 );

        m_PipeSprites.push_back( sprite );
    }

    void Pipe::SpawnInvisiblePipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Pipe Up" ) );
        sprite.setPosition( m_Data->window.getSize().x,
                            m_Data->window.getSize().y - sprite.getGlobalBounds().height );

        sprite.setColor(sf::Color( 0, 0, 0, 0 ) );

        m_PipeSprites.push_back( sprite );
    }

    void Pipe::MovePipes(float dt)
    {
        for (unsigned short int i = 0; i < m_PipeSprites.size(); i++)
        {
            sf::Vector2f position = m_PipeSprites.at( i ).getPosition();
            float movement = PIPE_MOVEMENT_SPEED * dt;

            m_PipeSprites.at( i ).move( -movement, 0 );
        }
    }

    void Pipe::DrawPipes()
    {
        for (unsigned short int i = 0; i < m_PipeSprites.size(); i++)
        {
            m_Data->window.draw( m_PipeSprites.at(i) );
        }
    }
}
