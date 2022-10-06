#include "Graphics2D.h"
#include <SDL_image.h>
#include <iostream>

void Quit(){
    SDL_Quit();
    TTF_Quit();
    IMG_Quit();
}

Size::Size(){};

Size::Size(const int& width, const int& height){
    this->width = width;
    this->height = height;
}

Coordinate::Coordinate(){};

Coordinate::Coordinate(const int& x, const int& y){
    this->x = x;
    this->y = y;
}

CoordinateD::CoordinateD(){};

CoordinateD::CoordinateD(const double& x, const double& y){
    this->x = x;
    this->y = y;
}

Color::Color(){};

Color::Color(const unsigned char& r, const unsigned char& g, const unsigned char& b, const unsigned char& a){
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
}

Rectangle::Rectangle(){};

Rectangle::Rectangle(const int& x, const int& y, const int& width, const int& height){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

bool loaded = false;

Window::Window(const char* title, const int& x, const int& y, const int& width, const int& height, const unsigned int& flags){
    if (!loaded){
        SDL_Init(SDL_INIT_EVERYTHING);
        IMG_Init(IMG_INIT_PNG | IMG_INIT_JPG | IMG_INIT_WEBP);
        TTF_Init();
    }
    sdl_window = SDL_CreateWindow(title, x, y, width, height, flags);
}

void Window::icon(const char* icon_path){
    SDL_Surface* icon = IMG_Load(icon_path);
    SDL_SetWindowIcon(sdl_window, icon);
    SDL_FreeSurface(icon);
}

void Window::title(const char* title){
    SDL_SetWindowTitle(sdl_window, title);
}

void Window::resizeable(const bool& resizeable){
    if (resizeable) SDL_SetWindowResizable(sdl_window, SDL_TRUE);
    else SDL_SetWindowResizable(sdl_window, SDL_FALSE);
}

void Window::decorated(const bool& decorated){
    if (decorated) SDL_SetWindowBordered(sdl_window, SDL_TRUE);
    else SDL_SetWindowBordered(sdl_window, SDL_FALSE);
}

void Window::show(){
    SDL_ShowWindow(sdl_window);
}

void Window::hide(){
    SDL_HideWindow(sdl_window);
}

void Window::maximize(){
    SDL_MaximizeWindow(sdl_window);
}

void Window::minimize(){
    SDL_MinimizeWindow(sdl_window);
}

void Window::minimum_size(const int& width, const int& height){
    SDL_SetWindowMinimumSize(sdl_window, width, height);
}

void Window::maximum_size(const int& width, const int& height){
    SDL_SetWindowMaximumSize(sdl_window, width, height);
}

void Window::size(const int& width, const int& height){
    SDL_SetWindowSize(sdl_window, width, height);
}

Size Window::size(){
    int width, height;
    SDL_GetWindowSize(sdl_window, &width, &height);
    return Size(width, height);
}

Coordinate Window::position(){
    int x, y;
    SDL_GetWindowPosition(sdl_window, &x, &y);
    return Coordinate(x, y);
}

Size Window::minimum_size(){
    int width, height;
    SDL_GetWindowMinimumSize(sdl_window, &width, &height);
    return Size(width, height);
}

Size Window::maximum_size(){
    int width, height;
    SDL_GetWindowMaximumSize(sdl_window, &width, &height);
    return Size(width, height);
}

void Window::position(const int& x, const int& y){
    SDL_SetWindowPosition(sdl_window, x, y);
}

void Window::brightness(const float& brightness){
    SDL_SetWindowBrightness(sdl_window, brightness);
}

void Window::opacity(const float& opacity){
    SDL_SetWindowOpacity(sdl_window, opacity);
}

void Window::always_on_top(const bool& BOOL){
    if (BOOL) SDL_SetWindowAlwaysOnTop(sdl_window, SDL_TRUE);
    else  SDL_SetWindowAlwaysOnTop(sdl_window, SDL_FALSE);
}

void Window::fullscreen_desktop(const bool& fullscreen_desktop){
    if (fullscreen_desktop) SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN_DESKTOP);
    else SDL_SetWindowFullscreen(sdl_window, 0);
}

void Window::fullscreen(const bool& fullscreen){
    if (fullscreen) SDL_SetWindowFullscreen(sdl_window, SDL_WINDOW_FULLSCREEN);
    else SDL_SetWindowFullscreen(sdl_window, 0);
}

void Window::destroy(){
    SDL_DestroyWindow(sdl_window);
}

Window::~Window(){
    SDL_DestroyWindow(sdl_window);
}

void PollWindowEvents(SDL_Event& sdl_event){
    SDL_PollEvent(&sdl_event);
}

Coordinate GetCursorPositionToWindow(){
    int x, y;
    SDL_GetMouseState(&x, &y);
    return Coordinate(x, y);
}

void ShowCursor(){
    SDL_ShowCursor(SDL_ENABLE);
}

void HideCursor(){
    SDL_ShowCursor(SDL_DISABLE);
}

Renderer::Renderer(const Window& window, const bool& vsync, const int& gpu_index){
    if (vsync) sdl_renderer = SDL_CreateRenderer(window.sdl_window, gpu_index, SDL_RENDERER_PRESENTVSYNC);
    else sdl_renderer = SDL_CreateRenderer(window.sdl_window, gpu_index, 0);
}

void Renderer::destroy(){
    SDL_DestroyRenderer(sdl_renderer);
}

Renderer::~Renderer(){
    SDL_DestroyRenderer(sdl_renderer);
}

void Renderer::clear(const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderClear(sdl_renderer);
}

void Renderer::update(){
    SDL_RenderPresent(sdl_renderer);
}

void Renderer::draw_line(const Coordinate& value1, const Coordinate& value2, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLine(sdl_renderer, value1.x, value1.y, value2.x, value2.y);
}

void Renderer::draw_lines(const SDL_Point* points, const int& count, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawLines(sdl_renderer, points, count);
}

void Renderer::draw_pixel(const Coordinate& coordinate, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoint(sdl_renderer, coordinate.x, coordinate.y);
}

void Renderer::draw_pixels(const SDL_Point* points, const int& count, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawPoints(sdl_renderer, points, count);
}

void Renderer::draw_rectangle(const Rectangle& rectangle, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
    SDL_RenderDrawRect(sdl_renderer, &rect);
}

void Renderer::draw_rectangles(const SDL_Rect* rects, const int& count, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderDrawRects(sdl_renderer, rects, count);
}

void Renderer::draw_filled_rectangle(const Rectangle& rectangle, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_Rect rect = {rectangle.x, rectangle.y, rectangle.width, rectangle.height};
    SDL_RenderFillRect(sdl_renderer, &rect);
}

void Renderer::draw_filled_rectangles(const SDL_Rect* rects, const int& count, const Color& color){
    SDL_SetRenderDrawColor(sdl_renderer, color.r, color.g, color.b, color.a);
    SDL_RenderFillRects(sdl_renderer, rects, count);
}

void Renderer::draw_texture(const Texture& texture, const Rectangle& destination_rectangle, const double& angle, const Coordinate& origin, const unsigned char& flip){
    SDL_Rect srcrect = {texture.x, texture.y, texture.width, texture.height};
    SDL_Rect dstrect = {destination_rectangle.x, destination_rectangle.y, destination_rectangle.width, destination_rectangle.height};
    SDL_Point sdl_center = {origin.x, origin.y};
    if (flip == 0) SDL_RenderCopyEx(sdl_renderer, texture.sdl_texture, &srcrect, &dstrect, angle, &sdl_center, SDL_FLIP_NONE);
    else if (flip == 1) SDL_RenderCopyEx(sdl_renderer, texture.sdl_texture, &srcrect, &dstrect, angle, &sdl_center, SDL_FLIP_HORIZONTAL);
    else if (flip == 2) SDL_RenderCopyEx(sdl_renderer, texture.sdl_texture, &srcrect, &dstrect, angle, &sdl_center, SDL_FLIP_VERTICAL);
}

void Renderer::draw(SDL_Texture* texture, const SDL_Rect& srcrect, const SDL_Rect& dstrect, const double& angle, const SDL_Point& center, const SDL_RendererFlip& flip){

    SDL_RenderCopyEx(sdl_renderer, texture, &srcrect, &dstrect, angle, &center, flip);
}

SDL_Texture* Renderer::load_texture(const char* image_path){
    SDL_Surface* surface = IMG_Load(image_path);
    SDL_Texture* texture = SDL_CreateTextureFromSurface(sdl_renderer, surface);
    SDL_FreeSurface(surface);
    return texture;
}

void Texture::destroy(){
    SDL_DestroyTexture(sdl_texture);
}

Texture::~Texture(){
    SDL_DestroyTexture(sdl_texture);
}

Texture::Texture(){};

Texture::Texture(SDL_Texture* sdl_texture){
    this->sdl_texture = sdl_texture;
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
    this->x = 0;
    this->y = 0;
}

void Texture::operator = (SDL_Texture* sdl_texture){
    this->sdl_texture = sdl_texture;
    SDL_QueryTexture(sdl_texture, nullptr, nullptr, &width, &height);
    this->x = 0;
    this->y = 0;
}

TTF_Font* LoadFont(const char* ttf_path, const int& size){
    return TTF_OpenFont(ttf_path, size);
}

Font::Font(){}

Font::Font(TTF_Font* ttf_font){
    this->ttf_font = ttf_font;
}

void Font::operator = (TTF_Font* ttf_font){
    this->ttf_font = ttf_font;
}

void Font::size(const int& size){
    TTF_SetFontSize(ttf_font, size);
}

void Font::style(const int& style){
    TTF_SetFontStyle(ttf_font, style);
}

void Font::destroy(){
    TTF_CloseFont(ttf_font);
}

Font::~Font(){
    TTF_CloseFont(ttf_font);
}

SDL_Texture* Renderer::load_texture(const char* text, const Color& color, const Font& font, const unsigned int& wrap_lenght){
    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};
    SDL_Surface* sdl_surface = TTF_RenderText_Blended_Wrapped(font.ttf_font, text, sdl_color, wrap_lenght);
    SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);
    SDL_FreeSurface(sdl_surface);
    return sdl_texture;
}

SDL_Texture* Renderer::load_texture(const char* text, const Color& color, const Color& background_color, const Font& font, const unsigned int& wrap_lenght){
    SDL_Color sdl_color = {color.r, color.g, color.b, color.a};
    SDL_Color sdl_background_color = {background_color.r, background_color.g, background_color.b, background_color.a};
    SDL_Surface* sdl_surface = TTF_RenderText_LCD_Wrapped(font.ttf_font, text, sdl_color, sdl_background_color, wrap_lenght);
    SDL_Texture* sdl_texture = SDL_CreateTextureFromSurface(sdl_renderer, sdl_surface);
    SDL_FreeSurface(sdl_surface);
    return sdl_texture;
}

unsigned int GetTicks(){
    return SDL_GetTicks();
}

void Delay(const unsigned int& milliseconds){
    SDL_Delay(milliseconds);
}