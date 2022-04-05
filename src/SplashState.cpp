#include "SplashState.h"
#include "Definations.h"
#include "MainMenuState.h"

namespace vlc
{
        SplashState::SplashState(GameDataRef data): _data(data)
        {

        }
        void SplashState::Init()
        {
            _data -> asset.LoadTexture("Splash Background",SPLASH_SCENE_BACKGROUND_FILEPATH);
            _background.setTexture(_data -> asset.GetTexture("Splash Background"));
            _background.setScale(SCALE_X,SCALE_Y);
        }

        void SplashState::HandleInput()
        {
            sf::Event event;
            while( _data -> window.pollEvent(event) )
            {
                if(sf::Event::Closed == event.type) _data -> window.close();
            }
        }
        void SplashState::Update( float dt )
        {
            if(_clock.getElapsedTime().asSeconds() > SPLASH_STATE_SHOW_TIME)
            {
               _data -> machine.AddState(StateRef(new MainMenuState( this -> _data)));
            }
        }
        void SplashState::Draw( float dt )
        {
            _data -> window.clear();
            _data-> window.draw(_background);
            _data -> window.display();
        }
}
