#include "Window.h"
#include "Config.h"
#include <stdio.h>

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
	unsigned int flags = SDL_WINDOW_SHOWN;
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

void Window::draw(s_t deltaTime)
{
	canvas.draw(deltaTime);
	const FrameBuffer& frameBuffer = canvas.getFrameBuffer();
	int hasError = SDL_UpdateTexture(
		screenTexture,
		NULL,
		frameBuffer.getFrameBuffer(),
		Config::windowWidth * sizeof(frameBuffer.getPixel(0,0))
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

void Window::setTitle(fps_t fps, ms_t deltaTime)
{
	static char title[128];
	snprintf(title, 128, "%s: %d fps | %d ms", "Rasterizer_test", fps, deltaTime);
	SDL_SetWindowTitle(window, title);
}

void Window::onQuit()
{
	running = 0;
}



void Window::run()
{
	s_t deltaTime = 0.0f;
	SDL_Event event;

	while (running)
	{
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

		s_t elapsedTime = SDL_GetTicks() / 1000.0f;
		update();
		draw(deltaTime);
		if (Config::fpsLimit != 0 && to_fps(deltaTime) > Config::fpsLimit)
		{
			ms_t waitTime = to_ms(to_fps(deltaTime) - Config::fpsLimit);
			SDL_Delay(waitTime);
		}
		deltaTime = SDL_GetTicks() / 1000.0f - elapsedTime;		
		setTitle(to_fps(deltaTime), deltaTime*1000.0f);
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

auto Window::to_fps(ms_t deltaTime) -> fps_t
{
	return 1.0f / (deltaTime / 1000.0f);
}

auto Window::to_fps(s_t deltaTime) -> fps_t
{
	return 1.0f / deltaTime;
}

auto Window::to_ms(fps_t fps) -> ms_t
{
	return 1000.0f/fps;
}

auto Window::to_s(fps_t fps) -> s_t
{
	return 1.0f / fps;
}