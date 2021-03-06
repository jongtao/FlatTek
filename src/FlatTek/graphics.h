#pragma once

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

#include <string>
#include <unordered_map>


class Display;



class Graphics
{
	public:
		Graphics();
		//~Graphics();

		void create_windowed_display(std::string name, std::string title,
			bool vsync, int width, int height);

		void create_fullscreen_display(std::string name, std::string title,
			bool vsync);

		void destroy_display(std::string name);

		//void create_canvas(std::string name, int width, int height);
		//void draw_canvas_to();
	
	private:
		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_FONT* base_font;

		std::unordered_map<std::string, Display> displays;
		std::unordered_map<void*, std::string> names;

		std::unordered_map<std::string, ALLEGRO_BITMAP*> canvases;

		void init(ALLEGRO_EVENT_QUEUE* event_queue);

		std::string get_name(ALLEGRO_DISPLAY* display);

	friend class Engine;
	friend class Input;
};



class Display
{
	public:
		Display(): display(NULL), is_fullscreen(false), vsync_enabled(false),
			width(1), height(1)
		{}

		std::string title;
		ALLEGRO_DISPLAY* display;
		bool is_fullscreen;
		bool vsync_enabled;
		int width;
		int height;
};
