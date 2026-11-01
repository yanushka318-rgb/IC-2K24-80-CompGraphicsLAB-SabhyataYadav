#include <SDL.h>
#include <iostream>
#include <cmath>
#include <algorithm>

using namespace std;

void drawDDA(SDL_Renderer* renderer,
             int x1, int y1, int x2, int y2)
{
    int dx = x2 - x1;
    int dy = y2 - y1;

    int steps = max(abs(dx), abs(dy));

    float xIncrement = (float)dx / steps;
    float yIncrement = (float)dy / steps;

    float x = x1;
    float y = y1;

    for (int i = 0; i <= steps; i++)
    {
        SDL_RenderDrawPoint(
            renderer,
            round(x),
            round(y)
        );

        x += xIncrement;
        y += yIncrement;
    }
}

int main(int argc, char* argv[])
{
    int x1, y1, x2, y2;

    cout << "DDA Line Drawing Algorithm\n";
    cout << "Enter starting point (x1 y1): ";
    cin >> x1 >> y1;

    cout << "Enter ending point (x2 y2): ";
    cin >> x2 >> y2;

    if (x1 == x2 && y1 == y2)
    {
        cout << "Both points are identical. "
             << "A single pixel will be plotted.\n";
    }

    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cout << "SDL Error: " << SDL_GetError();
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "DDA Line Drawing Algorithm",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        800, 600,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        cout << "Window Error: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window, -1, SDL_RENDERER_ACCELERATED
    );

    if (renderer == nullptr)
    {
        renderer = SDL_CreateRenderer(
            window, -1, SDL_RENDERER_SOFTWARE
        );
    }

    if (renderer == nullptr)
    {
        cout << "Renderer Error: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // Draw coordinate axes
    SDL_SetRenderDrawColor(renderer, 200, 200, 200, 255);
    SDL_RenderDrawLine(renderer, 0, 300, 800, 300);
    SDL_RenderDrawLine(renderer, 400, 0, 400, 600);

    // Convert mathematical coordinates to screen coordinates
    int screenX1 = 400 + x1;
    int screenY1 = 300 - y1;
    int screenX2 = 400 + x2;
    int screenY2 = 300 - y2;

    // Draw DDA line in blue
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);

    drawDDA(renderer, screenX1, screenY1,
            screenX2, screenY2);

    SDL_RenderPresent(renderer);

    int dx = x2 - x1;
    int dy = y2 - y1;
    int steps = max(abs(dx), abs(dy));

    cout << "\nDDA Calculation:\n";
    cout << "dx = " << dx << endl;
    cout << "dy = " << dy << endl;
    cout << "Steps = " << steps << endl;

    if (steps != 0)
    {
        cout << "X Increment = "
             << (float)dx / steps << endl;
        cout << "Y Increment = "
             << (float)dy / steps << endl;
    }

    cout << "\nLine displayed successfully!\n";
    cout << "Close the graphics window to exit.\n";

    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                running = false;
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}