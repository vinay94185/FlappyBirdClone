#include "GameState.h"
#include "Definations.h"
#include "GameOverState.h"
#include "SplashState.h"
#include <windows.h>
#include <iostream>

namespace vlc
{
        GameState::GameState(GameDataRef data): _data(data),pipe(new Pipe(data)) {}

        void GameState::Init()
        {
            try
            {
                _data -> asset.LoadTexture("Game Background",GAME_BACKGROUND_FILEPATH);
                _data -> asset.LoadTexture("Bird Frame 1",BIRD_FRAME_1_FILEPATH);
                _data -> asset.LoadTexture("Bird Frame 2",BIRD_FRAME_2_FILEPATH);
                _data -> asset.LoadTexture("Bird Frame 3",BIRD_FRAME_3_FILEPATH);
                _data -> asset.LoadTexture("Bird Frame 4",BIRD_FRAME_4_FILEPATH);
                _data -> asset.LoadTexture("Scoring Pipe",SCORING_PIPE_FILEPATH);
                _data -> asset.LoadFont("Flappy Font",FLAPPY_FONT_FILEPATH);
                _data -> asset.LoadSound("Wing",WING_SOUND_FILEPATH);
                _data -> asset.LoadSound("Point",POINT_SOUND_FILEPATH);
                _data -> asset.LoadSound("Hit",HIT_SOUND_FILEPATH);
            }
            catch(std::exception &err)
            {
                  MessageBox(NULL,err.what(),"Error: Loading files",MB_OK);
                  throw err;
            }

            land = new Land(_data);
            bird = new Bird(_data);
            flash = new Flash(_data);
            hud = new HUD(_data);

            _score = 0;

            _GameState = GameStates::eReady;

            try
            {
                _hitSound.setBuffer(_data -> asset.GetSound("Hit"));
                _pointSound.setBuffer(_data -> asset.GetSound("Point"));
                _wingSound.setBuffer(_data -> asset.GetSound("Wing"));
                _background.setTexture(_data -> asset.GetTexture("Game Background"));
                _background.setScale(SCALE_X,SCALE_Y);
            }
            catch(std::exception &er)
            {
                  MessageBox(NULL,er.what(),"Error: Data was not loaded properly",MB_OK);
                  throw er;
            }
        }

        void GameState::HandleInput()
        {
            sf::Event event;
            while( _data -> window.pollEvent(event) )
            {
                if(sf::Event::Closed == event.type) _data -> window.close();
                if(_data -> input.IsSpriteClicked(_background,sf::Mouse::Left,_data -> window) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space) )
                {
                    if(GameStates::eGameOver != _GameState) {
                        bird -> Tap();
                        _GameState = GameStates::ePlaying;
                        _wingSound.play();
                    }
                }
            }
        }

        void GameState::Update( float dt )
        {
            if(GameStates::eGameOver != _GameState)
            {
                bird -> Animate(dt);
                land -> MoveLand(dt);
            }

            if(GameStates::ePlaying == _GameState)
            {
                pipe -> MovePipes(dt);

                if(clock.getElapsedTime().asSeconds() > PIPE_SPAWN_FREQUENCY)
                {
                    pipe -> RandomisePipeOffset();
                    pipe -> SpawnBottomPipe();
                    pipe -> SpawnTopPipe();
                    pipe -> SpawnScoringPipe();

                    clock.restart();
                }
                bird -> Update(dt);

                const Land::Land_T &landSprites = land -> GetSprites();
                const Pipe::Pipe_T &pipeSprites = pipe -> GetSprites();
                const Pipe::Pipe_T &pipsScoringSprites = pipe -> GetScoringSprites();
                const sf::Sprite &birdSprite = bird -> GetSprite();

                for(unsigned int i = 0; i < landSprites.size(); ++i)
                {
                    if(collision.CheckSpriteCollision( birdSprite, landSprites.at(i)))
                    {
                        _hitSound.play();
                        _GameState = GameStates::eGameOver;
                    }
                }

                for(unsigned int i = 0; i < pipeSprites.size(); ++i)
                {
                    if(collision.CheckSpriteCollision(birdSprite,0.7f,pipeSprites.at(i)))
                    {
                        _hitSound.play();
                        _GameState = GameStates::eGameOver;
                    }
                }

                if(GameStates::ePlaying == _GameState)
                {
                    for(unsigned int i = 0; i < pipsScoringSprites.size(); ++i)
                    {
                        if(collision.CheckSpriteCollision(birdSprite,pipsScoringSprites.at(i)))
                        {
                            ++_score;
                            pipe -> pop_score();
                            hud -> UpdateScore(_score);
                            _pointSound.play();
                        }
                    }
                }
            }

            if(_GameState == GameStates::eGameOver)
            {
                flash -> Show(dt);
                if(clock.getElapsedTime().asSeconds() > TIME_BEFORE_GAME_OVER_APPEARS)
                    _data -> machine.AddState(StateRef(new GameOverState(this -> _data, _score) ),true);
            }

        }

        void GameState::Draw( float dt )
        {
            _data -> window.clear();
            _data -> window.draw(_background);
             pipe -> DrawPipes();
             land -> DrawLand();
             bird -> Draw();
             flash -> Draw();
             hud -> Draw();
            _data -> window.display();
        }
}
