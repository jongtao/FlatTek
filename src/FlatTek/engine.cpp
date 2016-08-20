#include "engine.h"

// test printing
#include<iostream>

// testing_display
#include <allegro5/allegro_font.h>
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define WINDOW_TITLE "HELOW WORLD"



Engine::Engine(double timestep): running(false), scene(this)
{
	// Base System
	if(!al_init())
		throw std::runtime_error("Failed to initialize base system");

	// Timer tick rate
	if(!(timer = al_create_timer(timestep)))
		throw std::runtime_error("Failed to create timer");

	// Event Queue
	if(!(event_queue = al_create_event_queue()))
		throw std::runtime_error("Failed to create event queue");

	// Listen for timer events
	al_register_event_source(event_queue, al_get_timer_event_source(timer));

	input.init(event_queue);

	testing_display(); // FIXME: replace with renderer
	input.set_disp(SCREEN_WIDTH, SCREEN_HEIGHT);
}



Engine::~Engine(void)
{
	al_uninstall_system();
}



void Engine::run(Scene* new_scene)
{
	running = true;
	bool redraw = false;
	ALLEGRO_EVENT event;

	scene.req_change(new_scene);

	al_start_timer(timer);

	while(running)
	{
		al_wait_for_event(event_queue, &event); // block until stuff to do

		if(event.type == ALLEGRO_EVENT_TIMER) // need to update at rate of timestep
		{
			running = scene.update();
			redraw = true;
		}
		else if(input.is_input(&event)) // inputs are read
		{
			input.update(&event);
		}
		else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) // window X button
			running = false;


		if(redraw && al_is_event_queue_empty(event_queue)) // need to redraw
		{
			output();
			redraw = false;
		}


	} // main loop
}




// FIXME: Do not leave testing_display here
void Engine::testing_display()
{
	ALLEGRO_DISPLAY_MODE display_data;
	ALLEGRO_FONT* base_font;

	ALLEGRO_DISPLAY* display;
	ALLEGRO_FONT* font;
	int screen_width, screen_height;


	bool fullscreen = false;
	al_inhibit_screensaver(true);


	// (enable this before creating display)
	// Force vsync: 1=on, 2=off
	al_set_new_display_option(ALLEGRO_VSYNC, 1, ALLEGRO_SUGGEST);

	if(!fullscreen)
	{
		screen_width = SCREEN_WIDTH;
		screen_height = SCREEN_HEIGHT;

		// Display set to fixed window
		al_set_new_display_flags(ALLEGRO_WINDOWED);

		// Display sized 800 x 400
		if (!(display = al_create_display(SCREEN_WIDTH, SCREEN_HEIGHT)))
			throw std::runtime_error("Failed to create windowed display");
	}
	else // fullscreen
	{
		// Fullscreen
		al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);
		al_get_display_mode(al_get_num_display_modes() - 1, &display_data);
		screen_width = display_data.width;
		screen_height = display_data.height;

		// Fullscreen	
		if (!(display = al_create_display(display_data.width, display_data.height)))
			throw std::runtime_error("Failed to create fullscreen display");
	}


	// loading screen
	//if(!al_init_image_addon())
		//stop_early("Failed to initialize image", ERROR_INIT);
									  
	if(!(base_font = al_create_builtin_font()))
		throw std::runtime_error("Failed to create font");

	al_clear_to_color(al_map_rgb(0, 0, 0));
	al_draw_text(base_font, al_map_rgb(255, 255, 255),
		screen_width/2, screen_height/2,
		ALLEGRO_ALIGN_CENTER, "FlatTek Engine");
	al_flip_display();
	
	al_set_window_title(display, WINDOW_TITLE);

	//al_grab_mouse(display);
}

