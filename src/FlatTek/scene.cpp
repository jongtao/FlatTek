#include "scene.h"
#include "engine.h"


SceneManager::SceneManager(Engine* engine):
	parent_engine(engine),
	current_scene(NULL), next_scene(NULL),
	request_exists(false),
	change_requested(false), hard_requested(false),
	halt_requested(false), soft_halt_requested(false)
{
	//create placeholder scene for "nothing"
	current_scene = new Scene; 
	current_scene->scene_manager = this;
}




/* Ask politely for a scene change.
 * If scene does not exist, this cancels all previous valid requests
 */
void SceneManager::req_soft_change(Scene* new_scene)
{
	if(new_scene == NULL)
		throw std::runtime_error("NULL scene requested");

	next_scene = new_scene;
	next_scene->scene_manager = this;

	change_requested = true;
	request_exists = true;
}


void SceneManager::req_halt()
{
	halt_requested = true;
	request_exists = true;
}

void SceneManager::req_soft_halt()
{
	halt_requested = true;
	soft_halt_requested = true;
	request_exists = true;
}


void SceneManager::req_change(Scene* new_scene)
{
	req_soft_change(new_scene);
	hard_requested = true;
	request_exists = true;
}


Input* SceneManager::req_input(void)
{
	return &(parent_engine->input);
}







void SceneManager::change(bool is_hard)
{
	if(is_hard) // delete old scene
	{
		delete current_scene;
		hard_requested = false;
	}

	current_scene = next_scene;	
	next_scene = NULL;

	current_scene->init();
	change_requested = false;
}


void SceneManager::clear_scenes(void)
{
	if(current_scene != NULL)
		delete current_scene;

	if(next_scene != NULL)
		delete next_scene;
}


bool SceneManager::update(void)
{
	if(request_exists)
	{
		if(change_requested)
			change(hard_requested);

		if(halt_requested)
		{
			if(!soft_halt_requested)
				clear_scenes();

			return false;
		}

		request_exists = false;
	}

	current_scene->update();

	return true;
}
