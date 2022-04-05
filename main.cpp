//#include <SFML/Graphics.hpp>
#include <iostream>
#include "Game.h"
#include "Definations.h"
#include "SplashState.h"
#include <time.h>
#include <stdlib.h>
#include <windows.h>

int main()
{
    srand(time(NULL));
    vlc::Game game(SCREEN_WIDTH ,SCREEN_HEIGHT ,GAME_TITLE);
    return EXIT_SUCCESS;
}
