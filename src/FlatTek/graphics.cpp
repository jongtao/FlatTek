#include "graphics.h"


Graphics::Graphics(): event_queue(NULL)
{
}


void Graphics::create_windowed_display(std::string name, std::string title,
	bool vsync, int width, int height)
{
	Display new_display;

	new_display.title = title;
	new_display.is_fullscreen = false;
	new_display.vsync_enabled = vsync;
	new_display.width = width;
	new_display.height = height;

	// (enable this before creating display)
	// Force vsync: 1=on, 2=off
	int vsync_val = vsync ? 1 : 2;
	al_set_new_display_option(ALLEGRO_VSYNC, vsync_val, ALLEGRO_SUGGEST);

	// Display set to fixed window
	al_set_new_display_flags(ALLEGRO_WINDOWED);

	// CREATE IT
	new_display.display = al_create_display(width, height);

	if (!new_display.display)
		throw std::runtime_error("Failed to create windowed display");


	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(new_display.display, title.c_str());

	if(event_queue != NULL)
	{
		al_register_event_source(
			event_queue,
			al_get_display_event_source(new_display.display));
	}

	displays.insert({name, new_display});
	names.insert({(void*)new_display.display, name});
}



void Graphics::create_fullscreen_display(std::string name, std::string title,
	bool vsync)
{
	ALLEGRO_DISPLAY_MODE display_data;
	Display new_display;

	new_display.is_fullscreen = true;
	new_display.vsync_enabled = vsync;

	// (enable this before creating display)
	// Force vsync: 1=on, 2=off
	
	int vsync_val = vsync ? 1 : 2;
	al_set_new_display_option(ALLEGRO_VSYNC, vsync_val, ALLEGRO_SUGGEST);

	al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

	// Get monitor size
	al_get_display_mode(al_get_num_display_modes() - 1, &display_data);

	new_display.width = display_data.width;
	new_display.height = display_data.height;

	// CREATE IT
	new_display.display = al_create_display(display_data.width, display_data.height);

	if (!new_display.display)
		throw std::runtime_error("Failed to create fullscreen display");

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_set_window_title(new_display.display, title.c_str());

	if(event_queue != NULL)
	{
		al_register_event_source(
			event_queue,
			al_get_display_event_source(new_display.display));
	}

	displays.insert({name, new_display});
	names.insert({(void*)new_display.display, name});
}


void Graphics::init(ALLEGRO_EVENT_QUEUE* event_queue)
{
	this->event_queue = event_queue;
	al_inhibit_screensaver(true);
}
