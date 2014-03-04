#include "Game.h"
#include <utils/init.h>
//#include "windows.h"
#include <iostream>
#include <stdlib.h>

const int FPS = 60;
const int DELAY_TIME = 1000.0f / FPS;

int main(int argc, char const **argv)
{
  dani::init::init(argc, argv);
    if (argc > 1 && strcmp(argv[1], "--randomize") == 0)
      srandom(time(NULL));

//	AllocConsole();
  //freopen("CON", "w", stdout);
    Uint32 frameStart, frameTime;

    std::cout << "game init attempt...\n";
    if(TheGame::Instance()->init("SDL_test", 100, 100, 755, 600, false))
    {
        std::cout << "game init success!\n";
        while(TheGame::Instance()->running())
        {
            frameStart = SDL_GetTicks();

            TheGame::Instance()->handleEvents();
            TheGame::Instance()->update();
            TheGame::Instance()->render();

            frameTime = SDL_GetTicks() - frameStart;

            if(frameTime < DELAY_TIME)
            {
                SDL_Delay((int)(DELAY_TIME - frameTime));
            }
        }
    }
    else
    {
        std::cout << "game init failure - " << SDL_GetError() << "\n";
        return -1;
    }

    std::cout << "game closing...\n";
    TheGame::Instance()->clean();

    return 0;
}
