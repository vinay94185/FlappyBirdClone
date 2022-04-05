#include "land.h"

namespace vlc
{
   Land::Land(GameDataRef data): _data(data)
   {
       _data -> asset.LoadTexture("Land",LAND_FILEPATH);
       sf::Sprite sprite(_data -> asset.GetTexture("Land"));
       sf::Sprite sprite2(_data -> asset.GetTexture("Land"));

       sprite.setScale(SCALE_X,SCALE_Y);
       sprite2.setScale(SCALE_X,SCALE_Y);

       sprite.setPosition(0,_data -> window.getSize().y - sprite.getGlobalBounds().height);
       sprite2.setPosition(sprite.getGlobalBounds().width,_data -> window.getSize().y - sprite.getGlobalBounds().height);

       _landSprites.reserve(2);
       _landSprites.push_back(sprite);
       _landSprites.push_back(sprite2);
   }

   void Land::MoveLand(float dt)
   {
        for(unsigned short i = 0; i< _landSprites.size();++i)
        {
            float movement = (PIPE_MOVEMENT_SPEED * dt) * SCALE_X;

            _landSprites.at(i).move( -movement,0.0f);\

            if(_landSprites.at(i).getPosition().x < 0 - _landSprites.at(i).getGlobalBounds().width)
            {
                _landSprites.at(i).setPosition(sf::Vector2f( _data -> window.getSize().x,_landSprites.at(i).getPosition().y) );
            }
        }
   }

   void Land::DrawLand()
   {
        for(unsigned short i = 0; i< _landSprites.size();++i)
        {
            _data -> window.draw(_landSprites.at(i));
        }
   }

   const Land::Land_T &Land::GetSprites() const
   {
        return this -> _landSprites;
   }
}
