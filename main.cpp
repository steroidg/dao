

#include <SDL.h>
#include <iostream>


using namespace std;




int main( int argc, char *argv[] )
{
    
    SDL_Init( SDL_INIT_EVERYTHING );
    
    SDL_Surface *screen = SDL_SetVideoMode( 640, 480, 24, SDL_HWSURFACE );

    // Just keep the main window open for 5 seconds then close.
    SDL_Delay( 5000 );
    
    SDL_Quit();
    
	return 0;
}
