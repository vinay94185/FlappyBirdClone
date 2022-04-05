#include "Bird.h"

namespace vlc
{
    Bird::Bird(GameDataRef data):_data( data)
    {
        _animationIterator = 0;
        _animationFrames.reserve(3);
        _animationFrames.push_back(_data -> asset.GetTexture("Bird Frame 1"));
        _animationFrames.push_back(_data -> asset.GetTexture("Bird Frame 2"));
        _animationFrames.push_back(_data -> asset.GetTexture("Bird Frame 3"));
        _animationFrames.push_back(_data -> asset.GetTexture("Bird Frame 4"));
        _birdSprite.setTexture( _animationFrames.at(_animationIterator) );
        _birdSprite.setScale(SCALE_X,SCALE_Y);
        _birdSprite.setPosition((_data -> window.getSize().x / 4 - (_birdSprite.getGlobalBounds().width / 2) ),(_data -> window.getSize().y / 2 - (_birdSprite.getGlobalBounds().height / 2) ));
        _birdState = BIRD_STATE_STILL;
        _birdSprite.setOrigin(
                sf::Vector2f(
                             _birdSprite.getGlobalBounds().width / 2,
                             _birdSprite.getGlobalBounds().height / 2
                             ));
        _rotation = 0;
    }

    void Bird::Draw()
    {
        _data -> window.draw(_birdSprite);
    }

    void Bird::Animate(float dt)
    {
        // check if enough time has elapsed or not
        if(_clock.getElapsedTime().asSeconds() > (BIRD_ANIMATION_DURATION / _animationFrames.size() ))
        {
            // reset animation iterator to 0 if greater than no og frames else increment
            _animationIterator = (_animationIterator < _animationFrames.size()-1)? _animationIterator + 1 : 0;
            _birdSprite.setTexture( _animationFrames.at(_animationIterator) ); // change texture
            _clock.restart(); // reset clock
        }
    }
    void Bird::Update(float dt)
    {
        switch(_birdState)
        {
        case BIRD_STATE_FALLING:
            _birdSprite.move(0,GRAVITY * dt * SCALE_Y);
            if(_rotation < MAX_ROTATION)
                _rotation += ROTATION_SPEED * dt;
            _birdSprite.setRotation(_rotation);
            break;

        case BIRD_STATE_FLYING:
            if(_birdSprite.getPosition().y  > 10)
                _birdSprite.move(0,-FLYING_SPEED * dt * SCALE_Y);
            if(_rotation > MIN_ROTATION)
                _rotation -= ROTATION_SPEED * dt;
            _birdSprite.setRotation(_rotation);
            break;
        }

        if(_movementClock.getElapsedTime().asSeconds() > FLYING_DURATION )
        {
            _birdState = BIRD_STATE_FALLING;
            _movementClock.restart();
        }
    }

    void Bird::Tap()
    {
        _movementClock.restart();
        _birdState = BIRD_STATE_FLYING;
    }

    const sf::Sprite &Bird::GetSprite() const
    {
        return this -> _birdSprite;
    }

}
