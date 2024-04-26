#include <SDL.h>
#include <stdbool.h>

#define NUM_FONT_COLS 16 
#define NUM_FONT_ROWS 16

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

void render_text(SDL_Renderer* renderer, SDL_Texture* texture, const char* text, int font_width, int font_height, float scale)
{
  int max_output_width = 0;
  int max_output_height = 0;

  scc(SDL_GetRendererOutputSize(renderer, &max_output_width, &max_output_height));

  for (size_t i = 0; i < strlen(text); ++i)
  {
    SDL_Rect srect; 
    srect.x = (int)text[i] % NUM_FONT_COLS * font_width;
    srect.y = (int)text[i] / NUM_FONT_ROWS * font_height;
    srect.w = font_width;
    srect.h = font_height;

    SDL_Rect drect;
    drect.x = i * (int)(font_width * scale) % max_output_width;
    drect.y = i * (int)(font_width * scale) / max_output_width * font_height * scale;
    drect.w = (int)(font_width * scale);
    drect.h = (int)(font_height * scale);

    scc(SDL_RenderCopy(renderer, texture, &srect, &drect));
  }
}

void draw_text_buffer(SDL_Renderer* renderer, SDL_Texture* texture, const char* text_buffer, int font_width, int font_height)
{
  SDL_RenderClear(renderer);
  render_text(renderer, texture, text_buffer, font_width, font_height, 1.f);
  SDL_RenderPresent(renderer);
}

bool EVENT_LOOP_RUNNING = true;

void terminate_event_loop(void)
{
  EVENT_LOOP_RUNNING = false;
}

int main(void)
{
  scc(SDL_Init(SDL_INIT_VIDEO));

  SDL_Window* window = scp(SDL_CreateWindow("Babel",
                                            SDL_WINDOWPOS_CENTERED,
                                            SDL_WINDOWPOS_CENTERED,
                                            1280, 720, 
                                            SDL_WINDOW_RESIZABLE));
  
  SDL_Renderer* renderer = scp(SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE));
  SDL_Surface* surface = scp(SDL_LoadBMP("../assets/font.bmp"));
  SDL_Texture* texture = scp(SDL_CreateTextureFromSurface(renderer, surface));

  int font_width = surface->w / NUM_FONT_COLS;
  int font_height = surface->h / NUM_FONT_ROWS;

  SDL_Event event;

  char text_buffer[65536] = {0};
  size_t text_buffer_pos = 0;

  while (EVENT_LOOP_RUNNING)
  {
    while (SDL_PollEvent(&event))
    {
      switch (event.type)
      {
        case SDL_TEXTINPUT:
          {
            for (size_t i = 0; i < SDL_TEXTINPUTEVENT_TEXT_SIZE; ++i)
            {
              if (event.text.text[i])
              {
                text_buffer[text_buffer_pos] = event.text.text[i];
                ++text_buffer_pos;
              }
              else
              {
                break;
              }
            }

            draw_text_buffer(renderer, texture, text_buffer, font_width, font_height);
          }
          break;

        case SDL_KEYDOWN:
          if (event.key.keysym.sym == 8)  
          {
            if (text_buffer_pos > 0)
            {
              --text_buffer_pos; 
            }

            text_buffer[text_buffer_pos] = 0;
            draw_text_buffer(renderer, texture, text_buffer, font_width, font_height);
          }
          else if(event.key.keysym.sym == 27) 
          {
            terminate_event_loop(); 
          }

          break;

        case SDL_WINDOWEVENT:
          draw_text_buffer(renderer, texture, text_buffer, font_width, font_height);
          break;

        case SDL_QUIT:
          terminate_event_loop();
          break;

        default:
          break;
      };
    }
  }

  SDL_Quit();
  return 0;
}

