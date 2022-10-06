#include <iostream>
#include "Game.h"
#include "Graphics2D.h"
using namespace std;

int main()
{
    Game game;

    while (game.running){
        game.poll_events();
        game.calculate();
        game.draw();
        game.fps_calculation();
    }
 
    return 0;
}