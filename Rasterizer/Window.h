#pragma once
#include <SDL.h>
#include <map>
#include "Sprite.h"
#include "Color.h"
#include "Canvas.h"

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
    std::map<int,int> keys;
    int frameSkip;  
    int running;  
    SDL_Window* window;  
    SDL_Renderer* renderer;  
	SDL_Texture* screenTexture;
	Canvas canvas;
};  