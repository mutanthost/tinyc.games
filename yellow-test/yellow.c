#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <SDL.h>
#include <SDL_ttf.h>

#define W 301
#define H 301

enum colors {CLEAR, YELLOW, BLACK};

int x = 0;
int y = 0;
int grid[3][3] = {};

SDL_Event event;
SDL_Renderer *renderer;

void setup();
void draw_stuff();


//the entry point and main game loop
int main()
{
        setup();

        draw_stuff();

        while (y < 3)
        {
                while (x < 3)
                {
                        if (y != x)
                                grid[y][x] = YELLOW;
                        draw_stuff();
                        x = x + 1;
                }
                x = 0;
                y = y + 1;
        }
        y = 1;
        grid[y][x] = BLACK;

        for(;;)
        {
                while(SDL_PollEvent(&event)) switch(event.type)
                {
                        case SDL_QUIT: exit(0);
                }

                draw_stuff();
        }
}

//initial setup to get the window and rendering going
void setup()
{
        srand(time(NULL));

        SDL_Init(SDL_INIT_VIDEO);
        SDL_Window *win = SDL_CreateWindow("Yellow",
                SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, W, H, SDL_WINDOW_SHOWN);
        renderer = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
        if(!renderer) exit(fprintf(stderr, "Could not create SDL renderer\n"));
}

//draw everything in the game on the screen
void draw_stuff()
{
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);
        SDL_Rect dest = {0, 0, W, H};

        for(int y = 0; y < 3; y++) for(int x = 0; x < 3; x++)
        {
                if(grid[y][x] == YELLOW)
                        SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
                else if(grid[y][x] == BLACK)
                        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                else
                        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);

                SDL_RenderFillRect(renderer, &(SDL_Rect){1 + x*100, 1 + y*100, 99, 99});
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000);
}
