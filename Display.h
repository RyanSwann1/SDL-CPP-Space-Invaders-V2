#pragma once
#include <SDL.h>
struct Laser;
class Media;
class Entity;
class Display
{
public:

	~Display();
	bool init(); //Initialize SDL

	SDL_Surface* getWindowSurface() const { return m_windowSurface; } 
	SDL_Window* getWindow() const { return m_window; }


	static const int WINDOW_SIZE_H = 800;
	static const int WINDOW_SIZE_W = 800;
private:
	SDL_Window* m_window = nullptr;
	SDL_Surface* m_windowSurface = nullptr;
};

