#include "Collision.h"

namespace SSEngine
{
    Collision::Collision()
    {

    }

    bool Collision::CheckSpriteCollision(sf::Sprite sprite1, sf::Sprite sprite2)
    {
        // Rectangle around sprite
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        if ( rect1.intersects( rect2 ) )
        {
            return true;
        }
        return false;
    }

    bool Collision::CheckSpriteCollision(sf::Sprite sprite1, float scale1, sf::Sprite sprite2, float scale2)
    {
        sprite1.setScale( scale1, scale2 );
        sprite2.setScale( scale1, scale2 );

        // Rectangle around sprite
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        if ( rect1.intersects( rect2 ) )
        {
            return true;
        }
        return false;
    }
}