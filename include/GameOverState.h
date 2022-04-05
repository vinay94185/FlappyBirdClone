#ifndef GAMEOVERSTATE_H
#define GAMEOVERSTATE_H

#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"

namespace vlc
{
    class GameOverState: public State
    {
    public:
        void Init() override;

        void HandleInput() override;
        void Update( float dt ) override;
        void Draw( float dt ) override;

        GameOverState(GameDataRef data,int score);
//       void Pause() {}
//       void Resume() {}
    private:
        GameDataRef _data;
        sf::Sprite _background;
        sf::Sprite _gameOverTitle;
        sf::Sprite _gameOverContainer;
        sf::Sprite _retryButton;
        sf::Sprite _medal;

        sf::Text _scoreText;
        sf::Text _highText;
        unsigned short gameover_text_move;

        int _score;
        int _highScore;
        sf::Clock _clock;
    };

}

#endif // GAMEOVERSTATE_H
