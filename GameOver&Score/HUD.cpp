#include "HUD.h"
#include <string>

namespace SSEngine
{
    HUD::HUD(GameDataRef data) : m_Data ( move ( data ) )
    {
        m_ScoreText.setFont( m_Data->assests.GetFont( "Flappy Font" ) );
        m_ScoreText.setString( "0" );
        m_ScoreText.setCharacterSize( 128 );
        m_ScoreText.setFillColor( sf::Color::White );
        m_ScoreText.setOrigin( m_ScoreText.getGlobalBounds().width / 2,
                m_ScoreText.getGlobalBounds().height / 2 );
        m_ScoreText.setPosition( m_Data->window.getSize().x / 2, m_Data->window.getSize().y / 5 );
    }

    void HUD::Draw()
    {
        m_Data->window.draw( m_ScoreText );
    }

    void HUD::UpdateScore(int score)
    {
        m_ScoreText.setString( std::to_string( score  ) );
    }
}