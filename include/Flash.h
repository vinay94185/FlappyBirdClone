#ifndef FLASH_H
#define FLASH_H

#include "Game.h"
#include "Definations.h"
#include <SFML/Graphics.hpp>

namespace vlc
{
    class Flash
    {
        public:
            Flash(GameDataRef Data);
            void Show(float dt);
            void Draw();
        private:
            GameDataRef _Data;
            sf::RectangleShape _shape;
            bool _flashOn;
    };
}

#endif // FLASH_H
