#include <SDL_image.h>
#include <SDL.h>
#include <iostream>

	const int SCREEN_WIDTH	= 640;
	const int SCREEN_HEIGHT = 480;
	const int SCREEN_BPP = 32;

// Dave put this here as part of the example
// I guess this uses the std namespace so I don't need to do stuffs like std::string
using namespace std;


/*
 * This function applies one surface onto another.
 */
void apply_surface (int x, int y, SDL_Surface *src, SDL_Surface *dest) {
	SDL_Rect offset;
	offset.x = x;
	offset.y = y;
	
	SDL_BlitSurface( src, NULL, dest, &offset );
}

/*
 * This function loads a image and return the correct bpp
 */
SDL_Surface *load_image (string filename) {
	SDL_Surface *loaded_image = NULL;
	SDL_Surface *optimized_image = NULL;
	
	loaded_image = IMG_Load(filename.c_str());
	if (loaded_image != NULL) {
		optimized_image = SDL_DisplayFormat(loaded_image);
		SDL_FreeSurface(loaded_image);
	}
	return optimized_image;
}


bool init (SDL_Surface **screen) {
	if (SDL_Init(SDL_INIT_EVERYTHING) == -1) {
		printf ("%s %d ERROR: Unable to SDL_Init.\n", __PRETTY_FUNCTION__, __LINE__);
		return false;
	}
	
	*screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE );
	if (! *screen) {
		printf ("%s %d ERROR: Unable to create screen.\n", __PRETTY_FUNCTION__, __LINE__);
		return false;
	}
	SDL_WM_SetCaption( "Dao", NULL );
	return true;
}



int main( int argc, char *argv[] ) {
	SDL_Event event;
    SDL_Surface *screen = NULL;
	SDL_Surface *dao = NULL;
	SDL_Surface *bg = NULL;
	
	//Make sure the program waits for a quit 
	bool quit = false;
	
	if (init (&screen) == false) {
			printf ("%s %d ERROR: Unable to init.\n", __PRETTY_FUNCTION__, __LINE__);
			return 1;
	}
	
	if (! screen) {
		printf ("%s %d ERROR: Unable to create screen.\n", __PRETTY_FUNCTION__, __LINE__);
		return 1;
	}
	
	dao = load_image("images/dao.png");
	if (! dao) {
		printf ("%s %d ERROR: Unable to load bitmap.\n", __PRETTY_FUNCTION__, __LINE__);
		return 1;
	}
	
	bg = load_image("images/background.png");
	if (! bg) {
		printf ("%s %d ERROR: Unable to load bitmap.\n", __PRETTY_FUNCTION__, __LINE__);
		return 1;
	}
	
	apply_surface (0, 0, bg, screen);
	apply_surface (0, SCREEN_HEIGHT/2, bg, screen);
	apply_surface (SCREEN_WIDTH/2, 0, bg, screen);
	apply_surface (SCREEN_WIDTH/2, SCREEN_HEIGHT/2, bg, screen);
	apply_surface (180, 140, dao, screen);
	
	if (SDL_Flip( screen ) == -1) {
		printf ("%s %d ERROR: Unable to flip screen.\n", __PRETTY_FUNCTION__, __LINE__);
		return 1;
	}
	
	while( quit == false ) {
		while( SDL_PollEvent( &event ) ) {
			if( event.type == SDL_QUIT ) {
				printf ("%s %d Quit event decected.\n", __PRETTY_FUNCTION__, __LINE__);
				quit = true;
			}
		}
	}
    // Just keep the main window open for 5 seconds then close.
    
//    SDL_Delay( 5000 );
	SDL_FreeSurface(dao);
	SDL_FreeSurface(bg);
    SDL_Quit();
    
	return 0;
}