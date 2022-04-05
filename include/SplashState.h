#ifndef SPLASHSTATE_H
#define SPLASHSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"

namespace vlc
{
    class SplashState: public State
    {
    public:
        void Init() override;

        void HandleInput() override;
        void Update( float dt ) override;
        void Draw( float dt ) override;

        SplashState(GameDataRef data);
//        void Pause() {}
//       void Resume() {}
    private:
        GameDataRef _data;

        sf::Clock _clock;

        sf::Sprite _background;
    };
}

#endif // SPLASHSTATE_H
