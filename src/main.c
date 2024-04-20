#include <SDL.h>
#include <stdbool.h>

void scc(int code)
{
  if (code < 0)
  {
    fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    exit(1);
  }
}

void scp(void* ptr)
{
  if (!ptr)
  {
    fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    exit(1);
  }
}

int main(void)
{
  scc(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window* window = SDL_CreateWindow("Babel",
                                        SDL_WINDOWPOS_CENTERED,
                                        SDL_WINDOWPOS_CENTERED,
                                        1280, 720, 0);
  scp(window);

  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_KEYDOWN:
          running = false;
          break;
        default:
          break;
      };
    }
    
    SDL_Surface* surface = SDL_GetWindowSurface(window);
    scp(surface);
    scc(SDL_UpdateWindowSurface(window));
  }

  SDL_Quit();
  return 0;
}
