#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#undef main

#define WINDOW_POSITION_CENTERED SDL_WINDOWPOS_CENTERED
#define WINDOW_FLAG_FULLSCREEN SDL_WINDOW_FULLSCREEN
#define WINDOW_FLAG_FULLSCREEN_DESKTOP SDL_WINDOW_FULLSCREEN_DESKTOP
#define WINDOW_FLAG_SHOWN SDL_WINDOW_SHOWN
#define WINDOW_FLAG_HIDDEN SDL_WINDOW_HIDDEN
#define WINDOW_FLAG_UNDECORATED SDL_WINDOW_BORDERLESS
#define WINDOW_FLAG_RESIZEABLE SDL_WINDOW_RESIZABLE
#define WINDOW_FLAG_MINIMIZED SDL_WINDOW_MINIMIZED
#define WINDOW_FLAG_MAXIMIZED SDL_WINDOW_MAXIMIZED
#define WINDOW_FLAG_ALWAYS_ON_TOP SDL_WINDOW_ALWAYS_ON_TOP
#define WINDOW_FLAG_SKIP_TASKBAR SDL_WINDOW_SKIP_TASKBAR

#define TEXTURE_FLIP_NONE 0
#define TEXTURE_FLIP_HORIZONTAL 1
#define TEXTURE_FLIP_VERTICAL 2

class Size{
public:
    int width, height;
    Size();
    Size(const int& width, const int& height);
};

class Coordinate{
public:
    int x, y;
    Coordinate();
    Coordinate(const int& width, const int& height);
};

class CoordinateD{
public:
    double x, y;
    CoordinateD();
    CoordinateD(const double& width, const double& height);
};

class Color{
public:
    unsigned char r, g, b, a;
    Color();
    Color(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a = 255);
};

class Rectangle{
public:
    int x, y, width, height;
    Rectangle();
    Rectangle(const int& x, const int& y, const int& width, const int& height);
};

void Init();
void Quit();

class Window
{
public:
    SDL_Window* sdl_window;
    Window(const char* title, const int& x, const int& y, const int& width, const int& height, const unsigned int& flags);
    void resizeable(const bool& resizeable);
    void decorated(const bool& decorated);
    void title(const char* title);
    void icon(const char* icon_path);
    void show();
    void hide();
    void maximize();
    void minimize();
    void minimum_size(const int& width, const int& height);
    Size minimum_size();
    void maximum_size(const int& width, const int& height);
    Size maximum_size();
    void fullscreen_desktop(const bool& fullscreen_desktop);
    void fullscreen(const bool& fullscreen);
    void size(const int& width, const int& height);
    Size size();
    void position(const int& x, const int& y);
    Coordinate position();
    void brightness(const float& brightness);
    void opacity(const float& opacity);
    void always_on_top(const bool& BOOL);
    void destroy();
    ~Window();
};

void PollWindowEvents(SDL_Event& sdl_event);
Coordinate GetCursorPositionToWindow();
void HideCursor();
void ShowCursor();

class Texture{
public:
    Texture();
    Texture(SDL_Texture* sdl_texture);
    void operator = (SDL_Texture* sdl_texture);
    SDL_Texture* sdl_texture;
    int x, y, width, height;
    void destroy();
    ~Texture();
};

TTF_Font* LoadFont(const char* ttf_path, const int& size);

class Font{
public:
    Font();
    Font(TTF_Font* ttf_font);
    void operator = (TTF_Font* ttf_font);
    void size(const int& size);
    void style(const int& style);
    TTF_Font* ttf_font;
    void destroy();
    ~Font();
};

class GameObject{
public:
    Texture texture;
    double x, y, width, height;
    double angle;
    CoordinateD origin;
    unsigned char flip;
    GameObject(const Texture& texture, const double& angle = 0.0, const CoordinateD& origin = CoordinateD(0, 0), const unsigned char& flip = 0);
    GameObject(SDL_Texture* sdl_texture, const double& angle = 0.0, const CoordinateD& origin = CoordinateD(0, 0), const unsigned char& flip = 0);
};

class Renderer{
public:
    SDL_Renderer* sdl_renderer;
    Renderer(const Window& window, const bool& vsync = false, const int& gpu_index = -1);
    void clear(const Color& color);
    void update();
    void draw_line(const Coordinate& value1, const Coordinate& value2, const Color& color);
    void draw_lines(const SDL_Point* points, const int& count, const Color& color);
    void draw_pixel(const Coordinate& coordinate, const Color& color);
    void draw_pixels(const SDL_Point* points, const int& count, const Color& color);
    void draw_rectangle(const Rectangle& rectangle, const Color& color);
    void draw_rectangles(const SDL_Rect* rects, const int& count, const Color& color);
    void draw_filled_rectangle(const Rectangle& rectangle, const Color& color);
    void draw_filled_rectangles(const SDL_Rect* rects, const int& count, const Color& color);
    void draw_texture(const Texture& texture, const Rectangle& destination_rectangle, const double& angle = 0.0, const Coordinate& origin = Coordinate(0, 0), const unsigned char& flip = 0);
    void draw(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect, const double& angle, const SDL_Point& center, const SDL_RendererFlip& flip);
    SDL_Texture* load_texture(const char* image_path);
    SDL_Texture* load_texture(const char* text, const Color& color, const Font& font, const unsigned int& wrap_lenght = 0);
    SDL_Texture* load_texture(const char* text, const Color& color, const Color& background_color, const Font& font, const unsigned int& wrap_lenght = 0);
    void destroy();
    ~Renderer();
};

unsigned int GetTicks();
void Delay(const unsigned int& milliseconds);