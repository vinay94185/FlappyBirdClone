#ifndef COLLISION_H
#define COLLISION_H

#include "Game.h"

namespace vlc
{
    class Collision
    {
        public:
            //Collision(GameDataRef Data);
            bool CheckSpriteCollision(const sf::Sprite &sprite1,const sf::Sprite &sprite2) const;
            bool CheckSpriteCollision(sf::Sprite sprite1,float scale1,const sf::Sprite &sprite2) const;
            bool CheckSpriteCollision(sf::Sprite sprite1,float scale1,sf::Sprite sprite2,float scale2) const;
        private:
           // GameDataRef _Data

    };
}

#endif // COLLISION_H
