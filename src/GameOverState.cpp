#include "GameOverState.h"
#include "Definations.h"
#include "GameState.h"
#include <windows.h>
#include <string>
#include <fstream>

namespace vlc
{
        GameOverState::GameOverState(GameDataRef data,int score): _data(data),_score(score) {}

        void GameOverState::Init()
        {

            try
            {
                _data -> asset.LoadTexture("Game Over Background",GAME_OVER_BACKGROUND_FILEPATH);
                _data -> asset.LoadTexture("Game Over Title",GAME_OVER_TITLE_FILEPATH);
                _data -> asset.LoadTexture("Game Over Body",GAME_OVER_BODY_FILEPATH);

                _data -> asset.LoadTexture("Bronze",BRONZE_MEDAL_FILEPATH);
                _data -> asset.LoadTexture("Silver",SILVER_MEDAL_FILEPATH);
                _data -> asset.LoadTexture("Gold",GOLD_MEDAL_FILEPATH);
                _data -> asset.LoadTexture("Platinum",PLATINUM_MEDAL_FILEPATH);
            }
            catch(std::exception &err)
            {
                  MessageBox(NULL,err.what(),"Error: Loading files",MB_OK);
                  throw err;
            }

            _background.setTexture(_data -> asset.GetTexture("Game Over Background"));
            _background.setScale(SCALE_X,SCALE_Y);
            _gameOverContainer.setTexture(_data -> asset.GetTexture("Game Over Body"));
            _gameOverContainer.setScale(SCALE_X,SCALE_Y);
            _gameOverTitle.setTexture(_data -> asset.GetTexture("Game Over Title"));
            _gameOverTitle.setScale(SCALE_X,SCALE_Y);
            _retryButton.setTexture(_data -> asset.GetTexture("Play Button"));
            _retryButton.setScale(SCALE_X,SCALE_Y);

            _gameOverContainer.setPosition( (_data -> window.getSize().x/2) - (_gameOverContainer.getGlobalBounds().width/2),(_data -> window.getSize().y/2) - (_gameOverContainer.getGlobalBounds().height/2));
            _gameOverTitle.setPosition( (_data -> window.getSize().x/2) - (_gameOverTitle.getGlobalBounds().width/2),(_gameOverContainer.getPosition().y) - (_gameOverTitle.getGlobalBounds().height * 1.2) );
            _retryButton.setPosition( (_data -> window.getSize().x/2) - (_retryButton.getGlobalBounds().width/2),(_gameOverContainer.getPosition().y + _gameOverContainer.getGlobalBounds().height) + (_retryButton.getGlobalBounds().height * 0.2) );


            _scoreText.setFont( _data -> asset.GetFont("Flappy Font"));
            _scoreText.setString(std::to_string(_score));
            _scoreText.setCharacterSize(GAME_OVER_FONT_SCORE_SIZE * SCALE_Y);
            _scoreText.setFillColor( sf::Color::White );
            _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2,_scoreText.getGlobalBounds().height/2 );
            _scoreText.setPosition( _data -> window.getSize().x / 10 * 7.25, _data -> window.getSize().y / 2.16 );

            _highText.setFont( _data -> asset.GetFont("Flappy Font"));
            _highText.setCharacterSize(GAME_OVER_FONT_SCORE_SIZE * SCALE_Y);
            _highText.setFillColor( sf::Color::White );
            _highText.setOrigin(_highText.getGlobalBounds().width/2,_highText.getGlobalBounds().height/2 );
            _highText.setPosition( _data -> window.getSize().x / 10 * 7, _data -> window.getSize().y / 1.85 );

            std::fstream file(SAVE_FILE,std::ios::in);
            if(!file) {
                file.clear();
                file.open("save.dat",std::ios::out | std::ios::trunc);
                if(file) file << _score;
                file.close();
                file.open(SAVE_FILE,std::ios::in);
                if(!file) throw std::runtime_error("Unable to save or load high score");
            }
            file >> _highScore;
            if(_highScore < _score) {
                file.close();
                file.open(SAVE_FILE,std::ios::out | std::ios::trunc);
                _highScore = _score;
                file << _score;
            }
            _highText.setString(std::to_string(_highScore));


           if(_score >= PLATINUM_SCORE)
                _medal.setTexture(_data -> asset.GetTexture("Platinum"));
           else if(_score >= GOLD_SCORE)
                _medal.setTexture(_data -> asset.GetTexture("Gold"));
           else if(_score >= SILVER_SCORE)
                _medal.setTexture(_data -> asset.GetTexture("Silver"));
           else
                _medal.setTexture(_data -> asset.GetTexture("Bronze"));

            _medal.setScale(SCALE_X,SCALE_Y);
            _medal.setPosition(_data -> window.getSize().x/4,_data -> window.getSize().y/2.15);

            gameover_text_move = 0;
        }

        void GameOverState::HandleInput()
        {
            sf::Event event;
            while( _data -> window.pollEvent(event) )
            {
                if(sf::Event::Closed == event.type) _data -> window.close();
                if(_data -> input.IsSpriteClicked(_retryButton,sf::Mouse::Left,_data -> window) )
                {
                    _data -> machine.AddState(StateRef(new GameState(_data)),true);
                }
            }
        }

        void GameOverState::Update( float dt )
        {
            // temp  variable to store time
            float time = _clock.getElapsedTime().asSeconds();
            if(time <= 1) // for one second move it up
                 _gameOverTitle.move(0,-30* dt * SCALE_Y);
            else if(time <= 2) // for another seconds go down
                 _gameOverTitle.move(0,30* dt * SCALE_Y);
            else // time to repeat hence restart clock
                _clock.restart();
        }

        void GameOverState::Draw( float dt )
        {
            // draw Everything on the screen
            _data -> window.clear();
            _data-> window.draw(_background);
            _data-> window.draw(_gameOverTitle);
            _data-> window.draw(_gameOverContainer);
            _data-> window.draw(_retryButton);
            _data-> window.draw(_scoreText);
            _data-> window.draw(_highText);
            _data-> window.draw(_medal);
            _data -> window.display();
        }

}
