#include "Flash.h"



namespace vlc
{
    Flash::Flash(GameDataRef Data):_Data(Data)
    {
        _shape = sf::RectangleShape(sf::Vector2f(_Data -> window.getSize()));
        _shape.setFillColor(sf::Color(255,255,255,0));

        _flashOn = true;
    }

    void Flash::Show(float dt)
    {
        if(_flashOn)
        {
            int alpha = (int)_shape.getFillColor().a + (FLASH_SPEED * dt);
            if(alpha >= 255.0f)
            {
                _flashOn = false;
                alpha = 255.0f;
            }

            _shape.setFillColor(sf::Color(255,255,255,alpha));
        }
        else
        {
            int alpha = (int)_shape.getFillColor().a;
            if(alpha > 0)
            {
                alpha -= (FLASH_SPEED * dt);
                if(alpha < 0) alpha = 0;

                _shape.setFillColor(sf::Color(255,255,255,alpha));
            }
        }
    }

    void Flash::Draw()
    {
        _Data -> window.draw(_shape);
    }

}
