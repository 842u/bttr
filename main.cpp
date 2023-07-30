#include <iostream>
#include <SDL.h>

int main(int argc, char *argv[])
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) != 0)
  {
    std::cerr << "SDL initialization failed: " << SDL_GetError() << std::endl;
    return 1;
  }

  // Create a window for video playback
  SDL_Window *window = SDL_CreateWindow("MPEG Video", SDL_WINDOWPOS_UNDEFINED,
                                        SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
  if (!window)
  {
    std::cerr << "Window creation failed: " << SDL_GetError() << std::endl;
    SDL_Quit();
    return 1;
  }

  // Create a renderer for the window
  SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, 0);
  if (!renderer)
  {
    std::cerr << "Renderer creation failed: " << SDL_GetError() << std::endl;
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Load the MPEG file
  SDL_Surface *videoSurface = SDL_LoadBMP("path_to_your_mpeg_file.mpg");
  if (!videoSurface)
  {
    std::cerr << "Video loading failed: " << SDL_GetError() << std::endl;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 1;
  }

  // Convert the surface to a texture for rendering
  SDL_Texture *videoTexture = SDL_CreateTextureFromSurface(renderer, videoSurface);
  SDL_FreeSurface(videoSurface);

  // Play the video
  bool quit = false;
  SDL_Event event;
  while (!quit)
  {
    while (SDL_PollEvent(&event))
    {
      if (event.type == SDL_QUIT)
      {
        quit = true;
      }
    }

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, videoTexture, NULL, NULL);
    SDL_RenderPresent(renderer);
  }

  // Cleanup and quit
  SDL_DestroyTexture(videoTexture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
