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

void* scp(void* ptr)
{
  if (!ptr)
  {
    fprintf(stderr, "SDL ERROR: %s\n", SDL_GetError());
    exit(1);
  }

  return ptr;
}

int main(void)
{
  scc(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window* window = scp(SDL_CreateWindow("Babel",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            1920, 1080, 0));
  
  SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE));
  SDL_Surface* surface = scp(SDL_LoadBMP("../assets/font.bmp"));
  SDL_Texture* texture = scp(SDL_CreateTextureFromSurface(renderer, surface));

  SDL_Rect rect;
  rect.x = 0;
  rect.y = 0;
  rect.w = 1024;
  rect.h = 1024;

  scc(SDL_RenderCopy(renderer, texture, NULL, &rect));
  SDL_RenderPresent(renderer);



  bool running = true;
  SDL_Event event;

  while (running)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_QUIT:
          running = false;
          break;
        case SDL_KEYDOWN:
          running = false;
          break;
        default:
          break;
      };
    }
  }

  SDL_Quit();
  return 0;
}
