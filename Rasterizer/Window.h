#pragma once
#include <SDL.h>
#include <map>
#include "Sprite.h"
#include "Color.h"
#include "Canvas.h"

enum {  
      DISPLAY_WIDTH  = 480  
    , DISPLAY_HEIGHT = 320  
    , UPDATE_INTERVAL = 1000/60  
    , HERO_SPEED = 2  
};  

class Window {  
public:  
    Window();  
    ~Window();  
    void start();  
    void stop();  
    void draw();  
    void fillRect(SDL_Rect* rc, int r, int g, int b );  
    void fpsChanged( int fps );  
    void onQuit();  
    void onKeyDown( SDL_Event* event );  
    void onKeyUp( SDL_Event* event );  
    void run();  
    void update();  
private:  
    std::map<int,int> keys; // No SDLK_LAST. SDL2 migration guide suggests std::map  
    int frameSkip;  
    int running;  
    SDL_Window* window;  
    SDL_Renderer* renderer;  
    Sprite hero;  
	Canvas canvas;
};  