#include "Graphics2D.h"
#include <iostream>
#include <string>
using namespace std;

class Player{
public:
    double x, y, width, height, angle;
    CoordinateD origin;
};

class Game{
public:
    Window window = Window("Window", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 16*70, 9*70, WINDOW_FLAG_RESIZEABLE);
    bool running = true;
    Renderer renderer = Renderer(window);
    Font font = LoadFont("ARLRDBD.ttf", 30);
    int fpms = 1000.0 / 60.0;
    unsigned int begin_ticks;
    unsigned int delta;

    bool move_left = false, move_right = false, move_up = false, move_down = false;

    double speed = 0.5;
    Texture player_texture;
    Texture FPSTexture;
    Player player;
    Game(){
        player_texture = renderer.load_texture("image.png");
        
        player.width = player_texture.width * 0.1;
        player.height = player_texture.height * 0.1;
        player.x = 100;
        player.y = 100;
        player.origin.x = player.width/2;
        player.origin.y = player.height/2;

        double speed = 20;

        int fpms = 1000.0 / 60.0;
        bool running = true;
        bool move_left = false, move_right = false, move_up = false, move_down = false;
        FPSTexture = renderer.load_texture("wow", Color(0, 255, 0), font);
    }
    void poll_events(){
        begin_ticks = GetTicks();
        
        SDL_Event event;
        PollWindowEvents(event);

        switch (event.type)
        {
            case SDL_QUIT:
                running = false;
                break;
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    move_up = true;
                    break;
                case SDLK_DOWN:
                    move_down = true;
                    break;
                case SDLK_LEFT:
                    move_left = true;
                    break;
                case SDLK_RIGHT:
                    move_right = true;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (event.key.keysym.sym)
                {
                case SDLK_UP:
                    move_up = false;
                    break;
                case SDLK_DOWN:
                    move_down = false;
                    break;
                case SDLK_LEFT:
                    move_left = false;
                    break;
                case SDLK_RIGHT:
                    move_right = false;
                    break;
                }
                break;
        }
    }
    void calculate(){
        if (move_left) player.x -= speed * delta;
        if (move_right) player.x += speed * delta;
        if (move_up) player.y -= speed * delta;
        if (move_down) player.y += speed * delta;
    }
    void draw(){
        renderer.clear(Color(0, 0, 0));

        SDL_Rect srcrect = {player_texture.x, player_texture.x, player_texture.width, player_texture.height};
        SDL_Rect dstrect = {(int) player.x, (int) player.y, (int) player.width, (int) player.height};
        SDL_Point center = {(int) player.origin.x, (int) player.origin.y};
        SDL_RendererFlip sdl_flip = SDL_FLIP_NONE;
        if (move_right) sdl_flip = SDL_FLIP_HORIZONTAL;

        renderer.draw(player_texture.sdl_texture, srcrect, dstrect, player.angle, center, sdl_flip);
        
        FPSTexture = renderer.load_texture(get_fps().c_str(), Color(0, 255, 0), font);
        renderer.draw_texture(FPSTexture, Rectangle(5, 2, FPSTexture.width, FPSTexture.height));

        renderer.update();
    }
    void fps_calculation(){
        delta = GetTicks() - begin_ticks;
    }
    string get_fps(){
        string fps_string = "FPS: ";
        unsigned int fps = (int)(1.0 / (delta / 1000.0));
        if (fps == 2147483648) fps = 1000;
        fps_string.append(to_string(fps));
        return fps_string;
    }
    ~Game(){
        Quit();
    }
};