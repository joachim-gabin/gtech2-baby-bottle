#include "window.h"

Bottle_Window::Bottle_Window(int window_width, int window_height)
{
	b_window_width = window_width;
	b_window_height = window_height;
	b_window = NULL;
	b_screenSurface = NULL;
}

Bottle_Window::~Bottle_Window() {
	//Destroy window
	SDL_DestroyWindow(b_window);
	SDL_Quit();

	TTF_CloseFont(font);
	TTF_Quit();
}
	
int Bottle_Window::Init()
{
	//Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		return 1;

	//Create window
	b_window = SDL_CreateWindow("Bottle Scheduler", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, b_window_width, b_window_height, SDL_WINDOW_SHOWN);
	if (b_window == NULL)
		return 2;

	//Initialize SDL_ttf (text rendering)
	if (TTF_Init() == -1)
		return 3;
	SetFont(TTF_OpenFont("fonts/Comic Gecko Pro.otf", 30));

	//Get window surface
	b_screenSurface = SDL_GetWindowSurface(b_window);
	SDL_FillRect(b_screenSurface, NULL, SDL_MapRGB(b_screenSurface->format, 100, 100, 100));
	return 0;
}

void Bottle_Window::Update()
{
	SDL_UpdateWindowSurface(b_window);
}

void Bottle_Window::Clear()
{
	SDL_FillRect(b_screenSurface, NULL, SDL_MapRGB(b_screenSurface->format, 100, 100, 100));
}

void Bottle_Window::drawText(string text, SDL_Rect rect, SDL_Color color, bool centered)
{
	if (text == "")
		return;
	SDL_Surface* textSurface = TTF_RenderText_Blended(font, text.c_str(), color);
	SDL_Rect textRect;
	//If centered, changes coordinates of the given rect
	if (centered)
	{
		textRect = {
		rect.x + (rect.w - textSurface->w) / 2,
		rect.y + (rect.h - textSurface->h) / 2,
		textSurface->w,
		textSurface->h
		};
	}
	else
	{
		textRect = {
		rect.x,
		rect.y,
		textSurface->w,
		textSurface->h
		};
	}
	//Draw
	SDL_BlitSurface(textSurface, NULL, b_screenSurface, &textRect);
	SDL_FreeSurface(textSurface);
}

void Bottle_Window::drawButton(Button button)
{
	SDL_Rect rect = button.getRect();
	SDL_Color bgColor = button.getBgColor();

	SDL_FillRect(b_screenSurface, &rect, SDL_MapRGB(b_screenSurface->format, bgColor.r, bgColor.g, bgColor.b));
	drawText(button.getText(), rect, button.getTextColor());
}

void Bottle_Window::drawInput(inputField input)
{
	SDL_Rect rect = input.getRect();
	SDL_Color bgColor = input.getBgColor();
	
	SDL_FillRect(b_screenSurface, &rect, SDL_MapRGB(b_screenSurface->format, bgColor.r, bgColor.g, bgColor.b));
	drawText(input.getData().c_str(), rect, input.getTextColor());
}

void Bottle_Window::drawShoppingList(vector<Item> list){
	SDL_Rect rect;
	size_t end;
	
	if (3 > list.size())
		end = list.size();
	else 
		end = 3;
	for (int i = 0; i < end; i++)
	{
		//Buffer the quantity number to a string
		char buffer[30];
		_itoa_s(list[i].quantity, buffer, 30, 10);
		
		rect.x = 100;
		rect.y = 830 + i * 40;
		rect.w = 200;
		rect.h = 15;
		
		//Draw
		SDL_FillRect(b_screenSurface, &rect, SDL_MapRGB(b_screenSurface->format, 100, 100, 100));
		drawText(list[i].name + " : " + buffer, rect, { 0, 0, 0 }, false);
	}
}

void Bottle_Window::drawTakes(vector<Take> takes)
{
	SDL_Rect rect;
	size_t end;

	if (11 > takes.size())
		end = takes.size();
	else
		end = 11;
	for (int i = 0; i < end; i++)
	{
		//Buffer the quatity number to a string
		char buffer[30];
		_itoa_s(takes[i].quantity, buffer, 30, 10);

		rect.x = 325;
		rect.y = 215 + i * 40;
		rect.w = 135;
		rect.h = 40;

		//Draw
		SDL_FillRect(b_screenSurface, &rect, SDL_MapRGB(b_screenSurface->format, 100, 100, 100));
		drawText(takes[i].date + " : " + buffer, rect, {0, 0, 0}, false);
	}
}
