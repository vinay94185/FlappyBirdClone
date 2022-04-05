#ifndef GAME_H
#define GAME_H

#include <memory>
#include <string>
#include <SFML/Graphics.hpp>
#include "AssetManager.h"
#include "StateMeachine.h"
#include "InputManager.h"

namespace vlc
{
    struct GameData
    {
        sf::RenderWindow window;
        AssetManager asset;
        StateMachine machine;
        InputManager input;
    };

    typedef std::shared_ptr<GameData> GameDataRef;

    class Game
    {
    public:
        Game(int width,int height,std::string title);
    private:
        const float dt = 1.0f / 60.0f;
        sf::Clock _clock;
        GameDataRef _data = std::make_shared<GameData>();
        void Run();
    };
}

#endif // GAME_H
