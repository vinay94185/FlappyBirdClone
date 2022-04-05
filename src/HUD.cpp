#include "HUD.h"
#include <string>

namespace vlc
{
    HUD::HUD(GameDataRef data):_data(data)
    {
        _scoreText.setFont( _data -> asset.GetFont("Flappy Font"));
        _scoreText.setString("0");
        _scoreText.setCharacterSize(FONT_SCORE_SIZE * SCALE_Y);
        _scoreText.setFillColor( sf::Color::White );
        _scoreText.setOrigin(_scoreText.getGlobalBounds().width/2,_scoreText.getGlobalBounds().height/2 );
        _scoreText.setPosition( _data -> window.getSize().x / 2, _data -> window.getSize().y / (5 / SCALE_Y));
    }

    void HUD::Draw()
    {
        _data -> window.draw(this -> _scoreText);
    }

    void HUD::UpdateScore(int score)
    {
        _scoreText.setString(std::to_string(score));
    }
}
