#include <SDL.h>

class Window
{
private:
	SDL_Event m_event;
	SDL_Renderer *m_renderer;
	SDL_Window *m_window;

	int m_width, m_height;

public:
	Window(const int width, const int height);
	~Window();
	int open();
	int close();
};
