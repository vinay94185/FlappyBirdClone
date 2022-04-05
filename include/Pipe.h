#ifndef PIPE_H
#define PIPE_H

#include <SFML/Graphics.hpp>
#include <deque>
#include "Game.h"
#include "Definations.h"

namespace vlc
{
    class Pipe
    {
    public:
        typedef std::deque<sf::Sprite> Pipe_T;
        Pipe(GameDataRef data);

        void SpawnBottomPipe();
        void SpawnTopPipe();
        void SpawnScoringPipe();
        //void SpawnInvisiblePipe();
        void MovePipes( float dt );
        void DrawPipes();
        void RandomisePipeOffset();
        void pop_score();
        const Pipe_T& GetSprites() const;
        const Pipe_T& GetScoringSprites() const;
    private:
        GameDataRef _data;
        unsigned short _landHeight;
        unsigned short _pipeSpawnYOffset;
        Pipe_T  pipeSprites;
        Pipe_T  scoringPipes;
    };
}


#endif // PIPE_H
