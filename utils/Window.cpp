#include <SDL_error.h>
#include "Window.h"
#include "Logger.h"

Window::Window(const int width, const int height) : m_width(width), m_height(height)
{
}

int Window::open()
{
	int rc = 0;

	if ((rc = SDL_Init(SDL_INIT_VIDEO)) != 0)
	{
		LOG_INFO("SDL_Init error : %s", SDL_GetError());
		return rc;
	}
	if ((rc = SDL_CreateWindowAndRenderer(m_width, m_height, 0, &m_window, &m_renderer)) != 0)
	{
		LOG_INFO("SDL_CreateWindowAndRenderer error : %s", SDL_GetError());
		return rc;
	}

	SDL_RaiseWindow(m_window);
	LOG_INFO("New window opened correctly");
	return rc;
}

void Window::close()
{
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyWindow(m_window);
	SDL_Quit();

	m_renderer = nullptr;
	m_window = nullptr;

	LOG_INFO("Window closed correctly");
}

Window::~Window()
{
	if (m_window != nullptr)
	{
		close();
	}
}
