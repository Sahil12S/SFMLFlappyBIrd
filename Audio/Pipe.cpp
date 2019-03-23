#include "Pipe.h"
#include <iostream>

namespace SSEngine
{
    Pipe::Pipe(GameDataRef data) : m_Data (std::move(data))
    {
        m_LandHeight = m_Data->assests.GetTexture( "Land" ).getSize().y;
        m_PipeSpawnYOffset = 0;
    }

    void Pipe::SpawnBottomPipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Pipe Up" ) );
        sprite.setPosition( m_Data->window.getSize().x,
                m_Data->window.getSize().y - sprite.getGlobalBounds().height -
                m_PipeSpawnYOffset );

        m_PipeSprites.push_back( sprite );
    }

    void Pipe::SpawnTopPipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Pipe Down" ) );
        sprite.setPosition( m_Data->window.getSize().x, -m_PipeSpawnYOffset );

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

    void Pipe::SpawnScoringPipe()
    {
        sf::Sprite sprite( m_Data->assests.GetTexture( "Scoring Pipe" ) );
        sprite.setPosition( m_Data->window.getSize().x, 0 );

        sprite.setColor(sf::Color( 0, 0, 0, 0 ) );

        m_ScoringPipes.push_back( sprite );
    }

    void Pipe::MovePipes(float dt)
    {
        for (unsigned short int i = 0; i < m_PipeSprites.size(); i++)
        {
            if ( m_PipeSprites.at( i ).getPosition().x < 0 - m_PipeSprites.at( i ).getGlobalBounds().width )
            {
                m_PipeSprites.erase( m_PipeSprites.begin() + i );
            }
            // sf::Vector2f position = m_PipeSprites.at( i ).getPosition();
            float movement = PIPE_MOVEMENT_SPEED * dt;

            m_PipeSprites.at( i ).move( -movement, 0 );
        }
        // std::cout << m_PipeSprites.size() << std::endl;

        for (unsigned short int i = 0; i < m_ScoringPipes.size(); i++)
        {
            if ( m_ScoringPipes.at( i ).getPosition().x < 0 - m_ScoringPipes.at( i ).getGlobalBounds().width )
            {
                m_ScoringPipes.erase( m_ScoringPipes.begin() + i );
            }
            // sf::Vector2f position = m_ScoringPipes.at( i ).getPosition();
            float movement = PIPE_MOVEMENT_SPEED * dt;

            m_ScoringPipes.at( i ).move( -movement, 0 );
        }
    }

    void Pipe::DrawPipes()
    {
        for (unsigned short int i = 0; i < m_PipeSprites.size(); i++)
        {
            m_Data->window.draw( m_PipeSprites.at(i) );
        }
    }

    void Pipe::RandomizePipeOffset()
    {
        m_PipeSpawnYOffset = rand() % ( m_LandHeight + 1 );
    }

    const std::vector<sf::Sprite>& Pipe::GetSprites() const
    {
        return m_PipeSprites;
    }

    std::vector<sf::Sprite>& Pipe::GetScoringSprites()
    {
        return m_ScoringPipes;
    }
}
