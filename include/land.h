#ifndef LAND_H
#define LAND_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "Game.h"
#include "Definations.h"

namespace vlc
{
    class Land
    {
        public:
            typedef std::vector<sf::Sprite> Land_T;
            Land(GameDataRef data);

            void MoveLand(float dt);
            void DrawLand();
            const Land_T &GetSprites() const;
        private:
            GameDataRef _data;
            Land_T _landSprites;
    };

}
#endif // LAND_H
