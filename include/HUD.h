#ifndef HUD_H
#define HUD_H

#include "Definations.h"
#include "Game.h"

namespace vlc
{
    class HUD
    {
        public:
            HUD(GameDataRef data);


            void Draw();
            void UpdateScore(int score);
        private:
            GameDataRef _data;
            sf::Text _scoreText;
    };
}

#endif // HUD_H
