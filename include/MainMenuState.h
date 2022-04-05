#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"

namespace vlc
{
    class MainMenuState:public State
    {
    public:
        void Init() override;

        void HandleInput() override;
        void Update( float dt ) override;
        void Draw( float dt ) override;

        MainMenuState(GameDataRef data);
//       void Pause() {}
//       void Resume() {}
    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _title;
        sf::Sprite _playButton;
    };

}
#endif // MAINMENUSTATE_H
