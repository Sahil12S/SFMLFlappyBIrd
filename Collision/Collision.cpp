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
}