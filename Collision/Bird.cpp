#include "Bird.h"

namespace SSEngine
{
    Bird::Bird(GameDataRef data) : m_Data ( std::move(data) )
    {
        m_AnimationIterator = 0;

        m_AnimationFrames.push_back( m_Data->assests.GetTexture( "Bird Frame 1" ) );
        m_AnimationFrames.push_back( m_Data->assests.GetTexture( "Bird Frame 2" ) );
        m_AnimationFrames.push_back( m_Data->assests.GetTexture( "Bird Frame 3" ) );
        m_AnimationFrames.push_back( m_Data->assests.GetTexture( "Bird Frame 4" ) );

        m_BirdSprite.setTexture( m_AnimationFrames.at( m_AnimationIterator ) );

        m_BirdSprite.setPosition( ( m_Data->window.getSize().x / 4.0f ) - ( m_BirdSprite.getGlobalBounds().width / 2.0f ),
                                  ( m_Data->window.getSize().y / 2.0f ) - ( m_BirdSprite.getGlobalBounds().height / 2.0f ) );

        m_BirdState = BIRD_STATE_STILL;

        // Transformations are related to origin
        sf::Vector2f origin = sf::Vector2f( m_BirdSprite.getGlobalBounds().width / 2,
                                            m_BirdSprite.getGlobalBounds().height / 2 );

        m_BirdSprite.setOrigin( origin );
        m_Rotation = 0;
    }

    void Bird::Draw()
    {
        m_Data->window.draw( m_BirdSprite );
    }

    void Bird::Animate(float dt)
    {
        if ( m_Clock.getElapsedTime().asSeconds() > BIRD_ANIMATION_DURATION / m_AnimationFrames.size() )
        {
            if ( m_AnimationIterator < m_AnimationFrames.size() - 1 )
            {
                m_AnimationIterator++;
            }
            else
            {
                m_AnimationIterator = 0;
            }

            /* Another way to animate
                m_AnimationIterator++;
                 m_AnimationIterator %= m_AnimationFrames.size();
             */

            m_BirdSprite.setTexture( m_AnimationFrames.at( m_AnimationIterator ) );
            m_Clock.restart();

        }
    }

    void Bird::Update( float dt )
    {
        if ( BIRD_STATE_FALLING == m_BirdState )
        {
            m_BirdSprite.move( 0, GRAVITY * dt );
            m_Rotation += ROTATION_SPEED * dt;

            if ( m_Rotation > MAX_ROTATION )
            {
                m_Rotation = MAX_ROTATION;
            }

            m_BirdSprite.setRotation( m_Rotation );
        }
        else if ( BIRD_STATE_FLYING == m_BirdState )
        {
            m_BirdSprite.move( 0, -FLYING_SPEED * dt );
            m_Rotation -= ROTATION_SPEED * dt;

            if ( m_Rotation < -MAX_ROTATION )
            {
                m_Rotation = -MAX_ROTATION;
            }

            m_BirdSprite.setRotation( m_Rotation );
        }

        if ( m_MovementClock.getElapsedTime().asSeconds() > FLYING_DURATION )
        {
            m_MovementClock.restart();
            m_BirdState = BIRD_STATE_FALLING;
        }
    }

    void Bird::Tap()
    {
        m_MovementClock.restart();
        m_BirdState = BIRD_STATE_FLYING;
    }

    const sf::Sprite& Bird::GetSprites() const
    {
        return m_BirdSprite;
    }
}