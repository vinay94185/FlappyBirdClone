#ifndef GAMESTATE_H
#define GAMESTATE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "state.h"
#include "game.h"
#include "pipe.h"
#include "land.h"
#include "Bird.h"
#include "Collision.h"
#include "Flash.h"
#include "HUD.h"

namespace vlc
{
    class GameState:public State
    {
    public:
        void Init() override;

        void HandleInput() override;
        void Update( float dt ) override;
        void Draw( float dt ) override;

        GameState(GameDataRef data);
//       void Pause() {}
//       void Resume() {}
        ~GameState()
        {
            delete land;
            delete bird;
            delete flash;
            delete hud;
        }
    private:
        GameDataRef _data;
        sf::Sprite _background;

 //       Pipe *pipe;
        std::unique_ptr<Pipe> pipe;
        Land *land;
        Bird *bird;
        Bird *bird2;
        Flash *flash;
        HUD *hud;

        unsigned int _score;

        Collision collision;

        sf::Clock clock;

        int _GameState;

        sf::Sound _hitSound;
        sf::Sound _wingSound;
        sf::Sound _pointSound;
    };

}
#endif // GAMESTATE_H
