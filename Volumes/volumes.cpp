#include <SDL.h>
#include <cmath>
#include <stdio.h>
#include <windows.h>

#include "Logger.h"
#include "Window.h"

#define WINDOW_WIDTH 1000.0
#define ANGLE_STEP 10.0
#define ROW_HEIGHT 20.0

double deg2rad(double angleDeg)
{
    return angleDeg * M_PI / 180.0;
}

void render(SDL_Renderer *renderer, double angleView)
{
    const char *profile[] = {
        "xxxxxx",
        "xxxxxxx",
        "xxxxxxxx",
        "xxxxxxxxx",
        "xxxxxxxxxx",
        "xxxxxxxxxxx",
        "xxxxxxxxxxxx",
        "xxxxxxxxxxxxx",
        "xxxxxxxxxxxxxx",
        "xxxxxxxxxxxxxxx",
        "xxxxxx",
        "xxxxxxxxxxxxxx",
        "xxxxxxxxxxxxx",
        "xxxxxxxxxxx",
        "xxxxxxx",
        "xxxxxxx",
        "xxx",
        "xxx",
        "xxx",
        "xxxxxxxxxx",
        "xxxxxxxxxxxxxx",
        "xxxxxxx",
        "xxx",
        "xxx",
        0};

#define NB_ROWS 20
    int rowId = 1;

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
    SDL_RenderClear(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);

    double y = WINDOW_WIDTH / 2.0 - (NB_ROWS / 2 * ROW_HEIGHT) * cos(deg2rad(angleView));
    double rowHeight = ROW_HEIGHT * cos(deg2rad(angleView));
    do
    {
        double width_l1 = strlen(profile[rowId - 1]) * 20.0;
        double width_l2 = strlen(profile[rowId]) * 20.0;
        // fprintf(stderr, "width_l1 = %2.2f width_ld2 = %2.2f\n", width_l1, width_l2);
        for (double i = 0; i <= 360.0; i += ANGLE_STEP)
        {
            int x1_l1 = WINDOW_WIDTH / 2.0 + width_l1 * cos(deg2rad(i));
            int y1_l1 = y + width_l1 * sin(deg2rad(i)) * sin(deg2rad(angleView));
            int x2_l1 = WINDOW_WIDTH / 2.0 + width_l1 * cos(deg2rad(i + ANGLE_STEP));
            int y2_l1 = y + width_l1 * sin(deg2rad(i + ANGLE_STEP)) * sin(deg2rad(angleView));
            int x1_l2 = WINDOW_WIDTH / 2.0 + width_l2 * cos(deg2rad(i));
            int y1_l2 = y + rowHeight + width_l2 * sin(deg2rad(i)) * sin(deg2rad(angleView));
            int x2_l2 = WINDOW_WIDTH / 2.0 + width_l2 * cos(deg2rad(i + ANGLE_STEP));
            int y2_l2 = y + rowHeight + width_l2 * sin(deg2rad(i + ANGLE_STEP)) * sin(deg2rad(angleView));
            SDL_Point points[5] =
                {
                    {x1_l1, y1_l1},
                    {x2_l1, y2_l1},
                    {x2_l2, y2_l2},
                    {x1_l2, y1_l2},
                    {x1_l1, y1_l1}};
            SDL_RenderDrawLines(renderer, points, sizeof(points) / sizeof(SDL_Point));
        }
        y += rowHeight;
        rowId++;
    } while (profile[rowId]);

    SDL_RenderPresent(renderer);
}

void eventHandler(const SDL_Event* event)
{
}

int SDL_main(int argc, char **argv)
{
    Window win(WINDOW_WIDTH, WINDOW_WIDTH);
	SDL_Event event;

    win.open();
    
    double angleView = 360.0;
    while (1)
    {
        if (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                break;
            }
            else
            {
                eventHandler(&event);
            }
            
        }
        render(win.getRender(), angleView);
        angleView--;
        if (angleView < 0.0)
        {
            angleView = 360.0;
        }
        SDL_Delay(10);
    }

    win.close();

    return EXIT_SUCCESS;
}
