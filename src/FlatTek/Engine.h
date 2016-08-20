#pragma once

#include <allegro5/allegro.h>

#include "input.h"
#include "scene.h"



class Engine
{
	public:
		Input input;

		Engine(double timestep);
		~Engine(void);

		//void run(void);
		void run(Scene* scene);
		//void load_scene();

	private:
		bool running;

		ALLEGRO_EVENT_QUEUE* event_queue;
		ALLEGRO_TIMER* timer;


		SceneManager scene;

		void testing_display(); // FIXME
		//bool update();
		void output(){}; // placeholder for render
};
