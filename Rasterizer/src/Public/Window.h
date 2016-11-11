#pragma once
#include <SDL2/SDL.h>
#include <map>
#include "Color.h"
#include "Canvas.h"

class Window {  
public:  
	using s_t = float;
	using ms_t = Uint32;
	using fps_t = Uint32;

    Window();  
    ~Window();  
    void start();  
    void stop();  
    void draw(s_t deltaTime);  
    void setTitle( fps_t fps, ms_t deltaTime );
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
	inline fps_t to_fps(ms_t deltaTime);
	inline fps_t to_fps(s_t deltaTime);
	inline ms_t to_ms(fps_t fps);
	inline s_t to_s(fps_t fps);
};  