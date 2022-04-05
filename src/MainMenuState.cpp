#include "MainMenuState.h"
#include "Definations.h"
#include "GameState.h"
#include <iostream>

namespace vlc
{
        MainMenuState::MainMenuState(GameDataRef data): _data(data) {}

        void MainMenuState::Init()
        {

            _data -> asset.LoadTexture("Main_Menu Background",MAIN_MENU_BACKGROUND_FILEPATH);
            _data -> asset.LoadTexture("Game Title",GAME_TITLE_FILEPATH);
            _data -> asset.LoadTexture("Play Button",PLAY_BUTTON_FILEPATH);
            _background.setTexture(_data -> asset.GetTexture("Main_Menu Background"));
            _title.setTexture(_data -> asset.GetTexture("Game Title"));
            _playButton.setTexture(_data -> asset.GetTexture("Play Button"));
            _background.setScale(SCALE_X,SCALE_Y);
            _title.setScale(SCALE_X,SCALE_Y);
            _playButton.setScale(SCALE_X,SCALE_Y);

            _title.setPosition((SCREEN_WIDTH/2)-(_title.getGlobalBounds().width/2),(_title.getGlobalBounds().height/2));
            _playButton.setPosition((SCREEN_WIDTH/2)-(_playButton.getGlobalBounds().width/2),(SCREEN_HEIGHT/2)-(_playButton.getGlobalBounds().height/2));

        }

        void MainMenuState::HandleInput()
        {
            sf::Event event;
            while( _data -> window.pollEvent(event) )
            {
                if(sf::Event::Closed == event.type) _data -> window.close();
                if(_data -> input.IsSpriteClicked(_playButton,sf::Mouse::Left,_data -> window) )
                {
                    _data -> machine.AddState( StateRef( new GameState(this -> _data) ) );
                }
            }
        }
        void MainMenuState::Update( float dt )
        {

        }
        void MainMenuState::Draw( float dt )
        {
            _data -> window.clear();
            _data-> window.draw(_background);
            _data-> window.draw(_title);
            _data-> window.draw(_playButton);
            _data -> window.display();
        }
}
