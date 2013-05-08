

#include <SDL_image.h>
#include <SDL.h>
#include <iostream>


// Dave put this here as part of the example
// I guess this uses the std namespace so I don't need to do stuffs like std::string
using namespace std;

void apply_surface (int x, int y, SDL_Surface *src, SDL_Surface *dest) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( src, NULL, dest, &offset );
}

SDL_Surface *load_image( string filename ) {
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	
	loaded_image = IMG_Load(filename.c_str());
	if (loaded_image != NULL) {
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);
	}
	return optimized_image;
}

int main( int argc, char *argv[] ) {
    SDL_Init( SDL_INIT_EVERYTHING );
	
	const int SCREEN_WIDTH	= 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;
	
    SDL_Surface *screen = NULL;
	SDL_Surface *dao = NULL;
	SDL_Surface *bg = NULL;
	
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
	if (! screen) {
		printf ("ERROR: Unable to create screen.");
		return 1;
	}
	SDL_WM_SetCaption( "Dao", NULL );
	
	dao = load_image("images/dao.png");
	if (! dao) {
		printf ("ERROR: Unable to load bitmap.");
		return 1;
	}
	
	bg = load_image("images/background.png");
	if (! bg) {
		printf ("ERROR: Unable to load bitmap.");
		return 1;
	}
	
	apply_surface (0, 0, bg, screen);
	apply_surface (0, SCREEN_HEIGHT/2, bg, screen);
	apply_surface (SCREEN_WIDTH/2, 0, bg, screen);
	apply_surface (SCREEN_WIDTH/2, SCREEN_HEIGHT/2, bg, screen);
	apply_surface (180, 140, dao, screen);
	
	SDL_Flip( screen );
	
    // Just keep the main window open for 5 seconds then close.
    SDL_Delay( 5000 );
    
	SDL_FreeSurface(dao);
	SDL_FreeSurface(bg);
    SDL_Quit();
    
	return 0;
}