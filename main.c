
#include "lib/chained.h"
#include "src/mainfunc.h"

int main(int argc, char **argv) {

	time_t time1;
	time(&time1);
	//Starting SL2
	SDL_Init(SDL_INIT_VIDEO);

	//set antialiasing
	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");

	//starting TTF (to display text))
    TTF_Init();
    TTF_Font *police = NULL;
    police = TTF_OpenFont("/usr/share/fonts/TTF/Vera.ttf", 65);

	//main tools of SDL
	SDL_Renderer *renderer = NULL;
	SDL_Window *window = NULL;

	//auto resolution
	SDL_DisplayMode Screen;
	SDL_GetCurrentDisplayMode(1, &Screen);
	int WIDTH = Screen.w;
	int HEIGHT = Screen.h;

	//set window and renderer
	window = SDL_CreateWindow("name",0,0,WIDTH,HEIGHT,0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

	//set event var to store events
	SDL_Event event;

	//main var
	int run = 1;
	int timer = 0;
	int MaxTime = 10;
	int NumberLine = 50;
	int space = 0;
	int click = 0;
	int MapState = 0;
	int *MapState_p = &MapState;

	//init displacement
	location loc;
	loc.scale = 30;
	loc.locx = 0;
	loc.locy = 0;

	//init Cases
	Case *DiffCase = NULL;
	Case **ListCase = NULL;
	ListCase = LoadCase(NumberLine);

	Couple Compare;

	//displacement var
	float Hzt = 0;
	float Vtc = 0;
	float Zm = 0;

	//Buttons var
	int cornx;
	int corny;

	//init Buttons
	Button *ListButton = NULL;
	ListButton = malloc(12*sizeof(Button));
	assert(ListButton);
	LoadButton(ListButton);

	while (run && ListButton[0].state == 0) {

		//load events
		SDL_PollEvent(&event);
		//place new cells

		if (event.type == SDL_MOUSEBUTTONDOWN) {
			if (event.button.button == SDL_BUTTON_LEFT && click == 0) {
                /*methode 1 (WIP)
				Compare = CompareChunk(ListCase,NumberLine, loc, event.button.x,event.button.y);
				if (Compare.x != -1) {
					if (ListCase[Compare.y][Compare.x].state == 0) ListCase[Compare.y][Compare.x].nextstate = 1;
					else ListCase[Compare.y][Compare.x].nextstate = 0;
					click = 1;
				}*/
                //methode 2
                for (int i=0; i<NumberLine; i++) {
                    for (int j=0; j<NumberLine; j++) {
                        if ((ListCase[i][j].posx+loc.locx)*(loc.scale+1) <= event.button.x
                        && (ListCase[i][j].posx+loc.locx)*(loc.scale+1)+loc.scale >= event.button.x
                        && (ListCase[i][j].posy+loc.locy)*(loc.scale+1) <= event.button.y
                        && (ListCase[i][j].posy+loc.locy)*(loc.scale+1)+loc.scale >= event.button.y) {
                            if (ListCase[i][j].state == 0) ListCase[i][j].nextstate = 1;
                            else ListCase[i][j].nextstate = 0;
                            click = 1;
                        }
                    }
                }

                cornx = (ListCase[0][NumberLine-1].posx+loc.locx)*(loc.scale+1)+loc.scale+10;
				corny = (ListCase[0][0].posy+loc.locy)*(loc.scale+1);
                for (int j=0; j<11; j++) {
                    if (cornx <= event.button.x && event.button.x <= cornx+ListButton[j].sizex
                    && corny+j*50+j <= event.button.y && event.button.y <= corny+j*50+j+ListButton[j].sizey) {
                    	if (ListButton[j].state == 0) ListButton[j].state = 1;
                        else ListButton[j].state = 0;
                        click = 1;
                    }
                }
			}
		}
		if (event.type == SDL_MOUSEBUTTONUP) {
			if (event.button.button == SDL_BUTTON_LEFT) click = 0;
		}
		//detect keys pressed
		if (event.type == SDL_KEYDOWN) {

			// quit
			if (event.key.keysym.sym == SDLK_ESCAPE) {
				run = 0;
			}

			//start / Stop
			if (event.key.keysym.sym == SDLK_SPACE && space == 0) {
				if (timer == 0) timer = 1 ;
				else timer = 0;
				space = 1;
			}

			//reload
			if (event.key.keysym.sym == SDLK_r) {
				ListCase = LoadCase(NumberLine);
			}

			//Save map
			if (event.key.keysym.sym == SDLK_k) {
				SaveMap(ListCase, NumberLine,"map/buffer.txt");
			}

			//Load map
			if (event.key.keysym.sym == SDLK_l) {
				NumberLine = LoadMap(ListCase, NumberLine,"map/buffer.txt");
				PrintScene(renderer,ListCase,ListButton,loc,NumberLine,timer,police);
			}

			// timer
			if (event.key.keysym.sym == SDLK_RSHIFT) {
				MaxTime ++;
			}

			if (event.key.keysym.sym == SDLK_RCTRL && MaxTime > 2) {
				MaxTime --;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				Hzt = 1;
			}
			else if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				Hzt = -1;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				Vtc = 1;
			}
			else if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				Vtc = -1;
			}
			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				Zm = 0.1;
				Hzt = -0.4;
				Vtc = -0.4;
			}
			else if (event.key.keysym.sym == SDLK_LCTRL) {
				Zm = -0.1;
				Hzt = -0.1;
				Vtc = -0.1;
			}
		}

		//detect keys released
		if (event.type == SDL_KEYUP) {

			//start stop
			if (event.key.keysym.sym == SDLK_SPACE) space = 0;

			if (event.key.keysym.sym == SDLK_c) {
                loc.scale = 30;
                loc.locx = 0;
                loc.locy = 0;
			}

			//arrows
			if (event.key.keysym.sym == SDLK_LEFT || event.key.keysym.sym == SDLK_q) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_RIGHT || event.key.keysym.sym == SDLK_d) {
				Hzt = 0;
			}
			if (event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) {
				Vtc = 0;
			}
			if (event.key.keysym.sym == SDLK_DOWN || event.key.keysym.sym == SDLK_s) {
				Vtc = 0;
			}

			//zoom
			if (event.key.keysym.sym == SDLK_LSHIFT) {
				Zm = 0;
				Hzt = 0;
				Vtc = 0;

			}
			if (event.key.keysym.sym == SDLK_LCTRL) {
				Zm = 0;
				Hzt = 0;
				Vtc = 0;

			}
		}

		//displacement
		loc.locx += Hzt;
		loc.locy += Vtc;
		loc.scale += Zm;

		//button application 
		NumberLine = ButtonFunc(renderer,ListButton,ListCase, NumberLine, MapState_p,loc,timer,police);

		if (timer >= MaxTime) {
			if (MapState == 0) LifeThor(ListCase, NumberLine);
			else LifeClosed(ListCase, NumberLine);
			timer = 1;
		}

		if (timer != 0) timer ++;

		PrintScene(renderer, ListCase, ListButton, loc, NumberLine, timer, police);

	}

	/*Don't work for now
	element *element_1 = ch_insert(NULL,1,NULL);
	//element *element_2 = ch_insert(NULL,2,NULL);
	//element *element_3 = ch_insert(element_2,3,NULL);
	//element *element_4 = ch_insert(NULL,4,NULL);

	printf("%d\n",element_1->content );
	ch_print(element_1);
	*/






	return 0;
}
