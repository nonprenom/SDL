#include <SDL.h>

class Window
{
private:
	Window();
	SDL_Event m_event = {};
	SDL_Renderer *m_renderer = nullptr;
	SDL_Window *m_window = nullptr;

	int m_width, m_height;

public:
	Window(const int width, const int height);
	~Window();
	int open();
	void close();
	SDL_Renderer* getRender() const {return m_renderer;};
	SDL_Event& getEvent() {return m_event;};
};
