#include "Pipe.h"

namespace vlc
{
    Pipe::Pipe(GameDataRef data): _data(data)
    {
        _data -> asset.LoadTexture("Land",LAND_FILEPATH);
        _data -> asset.LoadTexture("Pipe Up",PIPE_UP_FILEPATH);
        _data -> asset.LoadTexture("Pipe Down",PIPE_DOWN_FILEPATH);
        _landHeight = _data -> asset.GetTexture("Land").getSize().y * SCALE_Y;
        _pipeSpawnYOffset = 0;
    }

    void Pipe::DrawPipes()
    {
        for(unsigned short i=0; i < pipeSprites.size();++i)
        {
            _data -> window.draw(pipeSprites.at(i));
        }
    }

    void Pipe::SpawnBottomPipe()
    {
        sf::Sprite sprite( _data -> asset.GetTexture("Pipe Up") );
        sprite.setScale(SCALE_X,SCALE_Y);
        sprite.setPosition(_data -> window.getSize().x, _data -> window.getSize().y - sprite.getGlobalBounds().height - _pipeSpawnYOffset);
        pipeSprites.push_back( sprite );
    }

    void Pipe::SpawnTopPipe()
    {
        sf::Sprite sprite( _data -> asset.GetTexture("Pipe Down") );
        sprite.setScale(SCALE_X,SCALE_Y);
        sprite.setPosition(_data -> window.getSize().x,-_pipeSpawnYOffset);
        pipeSprites.push_back( sprite );
    }

/*    void Pipe::SpawnInvisiblePipe()
    {
        sf::Sprite sprite( _data -> asset.GetTexture("Pipe Down") );
        sprite.setScale(SCALE_X,SCALE_Y);
        sprite.setPosition(_data -> window.getSize().x, _data -> window.getSize().y - sprite.getGlobalBounds().height);
        sprite.setColor( sf::Color(0,0,0,0) );

        pipeSprites.push_back( sprite );
    }
*/
    void Pipe::MovePipes( float dt )
    {
        for(unsigned short i=0; i < pipeSprites.size();++i)
        {
            float movement = (PIPE_MOVEMENT_SPEED * dt) * SCALE_X;
            pipeSprites.at(i).move( -movement,0);

        }

        if(!pipeSprites.empty() && pipeSprites.at(0).getPosition().x < (0 - pipeSprites.at(0).getGlobalBounds().width) )
                pipeSprites.pop_front();

        for(unsigned short i=0; i < scoringPipes.size();++i)
        {
            float movement = (PIPE_MOVEMENT_SPEED * dt) * SCALE_X;
            scoringPipes.at(i).move( -movement,0);
        }

    }

    void Pipe::RandomisePipeOffset()
    {
        _pipeSpawnYOffset = rand() % ( _landHeight + 1 );
    }

    const Pipe::Pipe_T &Pipe::GetSprites() const
    {
        return this -> pipeSprites;
    }

    const Pipe::Pipe_T &Pipe::GetScoringSprites() const
    {
        return this -> scoringPipes;
    }

    void Pipe::SpawnScoringPipe()
    {
        sf::Sprite sprite( _data -> asset.GetTexture("Scoring Pipe") );
        sprite.setScale(SCALE_X,SCALE_Y);
        sprite.setPosition(_data -> window.getSize().x, 0);
//        sprite.setColor( sf::Color(0,0,0,0) );
        scoringPipes.push_back( sprite );
    }

    void Pipe::pop_score()
    {
        if(!scoringPipes.empty())
        scoringPipes.pop_front();
    }

}
