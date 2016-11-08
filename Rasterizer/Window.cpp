#include "Window.h"
#include "Config.h"
#include <iostream>

Window::Window()
	:
	frameSkip(0),
	running(0),
	window(NULL),
	renderer(NULL),
	canvas(Canvas(Config::windowWidth, Config::windowHeight))
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
		exit(0x13);
	}
	if (SDL_CreateWindowAndRenderer(Config::windowWidth, Config::windowHeight, flags, &window, &renderer))
	{
		exit(0x12);
	}
	screenTexture = SDL_CreateTexture(
		renderer, 
		SDL_PIXELFORMAT_RGBA8888,
		SDL_TEXTUREACCESS_STREAMING, 
		Config::windowWidth, 
		Config::windowHeight
	);

	if (screenTexture == NULL)
	{
		exit(0x11);
	}
	this->running = 1;
	run();
}

void set_pixel(SDL_Surface *surface, int x, int y, Uint32 pixel)
{
  Uint8* target_pixel = (Uint8*) surface->pixels + y * surface->pitch + x * sizeof(*target_pixel);
  *(Uint32*)target_pixel = pixel;
}

void Window::draw()
{
	canvas.draw();
	const Framebuffer& framebuffer = canvas.getFramebuffer();
	int hasError = SDL_UpdateTexture(
		screenTexture,
		NULL,
		framebuffer.getFramebuffer(),
		Config::windowWidth * sizeof(framebuffer.getPixel(0,0))
	);
	if (hasError == -1)
	{
		exit(0x10);
	}
	SDL_RenderCopy(renderer, screenTexture, NULL, NULL);
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

void Window::fpsChanged(int fps)
{
	char szFps[128];
	sprintf_s(szFps, "%s: %d FPS", "Rasterizer", fps);
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
				case SDL_QUIT:    onQuit();				break;
				case SDL_KEYDOWN: onKeyDown(&event);	break;
				case SDL_KEYUP:   onKeyUp(&event);		break;
				case SDL_MOUSEBUTTONDOWN:
				case SDL_MOUSEBUTTONUP:
				case SDL_MOUSEMOTION:
				break;
			}
		}
		// update/draw  
		timeElapsed = (now = SDL_GetTicks()) - past;
		if (timeElapsed >= Config::updateInterval)
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
	}
	else if (keys[SDLK_RIGHT])
	{
	}
	else if (keys[SDLK_UP])
	{
	}
	else if (keys[SDLK_DOWN])
	{
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