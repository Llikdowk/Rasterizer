#include "Window.h"

Window::Window()
	:frameSkip(0), running(0), window(NULL), renderer(NULL)
{
}

Window::~Window()
{
	this->stop();
}

void Window::start()
{
	int flags = SDL_WINDOW_SHOWN;
	if (SDL_Init(SDL_INIT_EVERYTHING))
	{
		return;
	}
	if (SDL_CreateWindowAndRenderer(DISPLAY_WIDTH, DISPLAY_HEIGHT, flags, &window, &renderer))
	{
		return;
	}
	this->running = 1;
	run();
}


void Window::draw()
{
	/*
	SDL_Rect heroRect;

	// Clear screen  
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);

	// Render hero  
	heroRect.x = hero.x;
	heroRect.y = hero.y;
	heroRect.w = 1;
	heroRect.h = 1;
	fillRect(&heroRect, 255, 0, 0);

	SDL_RenderPresent(renderer);
	*/
	
	
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
	SDL_RenderClear(renderer);
	canvas.draw();
	SDL_RenderPresent(renderer);
}

void Window::stop()
{
	if (NULL != renderer)
	{
		SDL_DestroyRenderer(renderer);
		renderer = NULL;
	}
	if (NULL != window)
	{
		SDL_DestroyWindow(window);
		window = NULL;
	}
	SDL_Quit();
}

void Window::fillRect(SDL_Rect* rc, int r, int g, int b)
{
	SDL_SetRenderDrawColor(renderer, r, g, b, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, rc);
}

void Window::fpsChanged(int fps)
{
	char szFps[128];
	sprintf_s(szFps, "%s: %d FPS", "SDL2 Base C++ - Use Arrow Keys to Move", fps);
	SDL_SetWindowTitle(window, szFps);
}

void Window::onQuit()
{
	running = 0;
}

void Window::run()
{
	int past = SDL_GetTicks();
	int now = past, pastFps = past;
	int fps = 0, framesSkipped = 0;
	SDL_Event event;
	while (running)
	{
		int timeElapsed = 0;
		if (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT:    onQuit();            break;
			case SDL_KEYDOWN: onKeyDown(&event);   break;
			case SDL_KEYUP:   onKeyUp(&event);   break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_MOUSEBUTTONUP:
			case SDL_MOUSEMOTION:
				break;
			}
		}
		// update/draw  
		timeElapsed = (now = SDL_GetTicks()) - past;
		if (timeElapsed >= UPDATE_INTERVAL)
		{
			past = now;
			update();
			if (framesSkipped++ >= frameSkip)
			{
				draw();
				++fps;
				framesSkipped = 0;
			}
		}
		// fps  
		if (now - pastFps >= 1000)
		{
			pastFps = now;
			fpsChanged(fps);
			fps = 0;
		}
		// sleep?  
		SDL_Delay(1);
	}
}

void Window::update()
{
	if (keys[SDLK_LEFT])
	{
		hero.x -= HERO_SPEED;
	}
	else if (keys[SDLK_RIGHT])
	{
		hero.x += HERO_SPEED;
	}
	else if (keys[SDLK_UP])
	{
		hero.y -= HERO_SPEED;
	}
	else if (keys[SDLK_DOWN])
	{
		hero.y += HERO_SPEED;
	}
	else if (keys[SDLK_ESCAPE])
	{
		onQuit();
	}
}

void Window::onKeyDown(SDL_Event* evt)
{
	keys[evt->key.keysym.sym] = 1;
}

void Window::onKeyUp(SDL_Event* evt)
{
	keys[evt->key.keysym.sym] = 0;
}