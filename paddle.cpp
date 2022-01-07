#include <SDL.h>

#include "paddle.h"
#include "physics.h"
#include "walls.h"

Paddle::Paddle(SDL_Renderer* renderer, int x, int y)
{
	this->renderer = renderer;

    velocity_y = 0;

    collider = { x - (WIDTH / 2), y - (LENGTH / 2), WIDTH, LENGTH};
}

void Paddle::handle_event(SDL_Event& event)
{
    if (event.type == SDL_KEYDOWN && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP: 
            velocity_y -= VELOCITY; 
            break;

        case SDLK_DOWN: 
            velocity_y += VELOCITY; 
            break;
        }
    }
    else if (event.type == SDL_KEYUP && event.key.repeat == 0)
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP: 
            velocity_y += VELOCITY; 
            break;
        case SDLK_DOWN: 
            velocity_y -= VELOCITY; 
            break;
        }
    }
}

void Paddle::move(Walls& walls)
{
    collider.y += velocity_y;

    if (Physics::is_collision(collider, walls.get_top()) ||
        Physics::is_collision(collider, walls.get_bottom()))
    {
        collider.y -= velocity_y;
    }
}

void Paddle::render()
{
    SDL_RenderFillRect(renderer, &collider);
}

SDL_Rect& Paddle::get_collider()
{
    return collider;
}