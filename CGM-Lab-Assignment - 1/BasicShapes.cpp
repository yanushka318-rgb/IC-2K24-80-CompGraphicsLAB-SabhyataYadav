#include <SDL.h>
#include <iostream>

// Draw a circle using the Midpoint Circle Algorithm
void drawCircle(SDL_Renderer* renderer, int xc, int yc, int radius)
{
    int x = 0;
    int y = radius;
    int decision = 1 - radius;

    while (x <= y)
    {
        SDL_RenderDrawPoint(renderer, xc + x, yc + y);
        SDL_RenderDrawPoint(renderer, xc - x, yc + y);
        SDL_RenderDrawPoint(renderer, xc + x, yc - y);
        SDL_RenderDrawPoint(renderer, xc - x, yc - y);
        SDL_RenderDrawPoint(renderer, xc + y, yc + x);
        SDL_RenderDrawPoint(renderer, xc - y, yc + x);
        SDL_RenderDrawPoint(renderer, xc + y, yc - x);
        SDL_RenderDrawPoint(renderer, xc - y, yc - x);

        x++;

        if (decision < 0)
        {
            decision += 2 * x + 1;
        }
        else
        {
            y--;
            decision += 2 * (x - y) + 1;
        }
    }
}

int main(int argc, char* argv[])
{
    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        std::cout << "SDL Error: " << SDL_GetError();
        return 1;
    }

    // Create graphics window
    SDL_Window* window = SDL_CreateWindow(
        "Computer Graphics Lab - Assignment 1",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        900, 650,
        SDL_WINDOW_SHOWN
    );

    if (window == nullptr)
    {
        std::cout << "Window Error: " << SDL_GetError();
        SDL_Quit();
        return 1;
    }

    // Create renderer
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
        std::cout << "Renderer Error: " << SDL_GetError();
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Set white background
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);

    // 1. Draw a straight line (Blue)
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderDrawLine(renderer, 100, 130, 350, 130);

    // 2. Draw a circle using Midpoint Circle Algorithm (Red)
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    drawCircle(renderer, 650, 130, 70);

    // 3. Draw a rectangle (Green)
    SDL_SetRenderDrawColor(renderer, 0, 150, 0, 255);
    SDL_Rect rectangle = {150, 300, 220, 140};
    SDL_RenderDrawRect(renderer, &rectangle);

    // 4. Draw a triangle (Purple)
    SDL_SetRenderDrawColor(renderer, 150, 0, 150, 255);
    SDL_RenderDrawLine(renderer, 550, 440, 680, 280);
    SDL_RenderDrawLine(renderer, 680, 280, 810, 440);
    SDL_RenderDrawLine(renderer, 810, 440, 550, 440);

    // Display all shapes
    SDL_RenderPresent(renderer);

    std::cout << "All four shapes drawn successfully!" << std::endl;
    std::cout << "Close the graphics window to exit." << std::endl;

    // Keep window open until user closes it
    SDL_Event event;
    bool running = true;

    while (running)
    {
        while (SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                running = false;
            }
        }
    }

    // Clean up resources
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}