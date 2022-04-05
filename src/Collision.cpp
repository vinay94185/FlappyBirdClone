#include "Collision.h"


namespace vlc
{
    bool Collision::CheckSpriteCollision(const sf::Sprite &sprite1,const sf::Sprite &sprite2) const
    {
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        return rect1.intersects(rect2);
    }

    bool Collision::CheckSpriteCollision(sf::Sprite sprite1,float scale1,const sf::Sprite &sprite2) const
    {
        sprite1.scale(scale1,scale1);
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        return rect1.intersects(rect2);
    }


    bool Collision::CheckSpriteCollision(sf::Sprite sprite1,float scale1,sf::Sprite sprite2,float scale2) const
    {
        sprite1.scale(scale1,scale1);
        sprite2.scale(scale2,scale2);
        sf::Rect<float> rect1 = sprite1.getGlobalBounds();
        sf::Rect<float> rect2 = sprite2.getGlobalBounds();

        return rect1.intersects(rect2);
    }

}
