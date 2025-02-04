#ifndef __ROCKET_GAME__
#define __ROCKET_GAME__

#include "SDL.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game_lib.h"

#define SCREEN_WIDTH (1366)
#define SCREEN_HEIGHT (720)

using namespace game_t;

extern objects_allocator_type objects;

class rocket_t : public object_t 
{
	private:
		bool collided = false;

	private:
		bool check_collision ();
		inline bool check_lcorner_collision (object_t *object)
		{
			return ((this->pos.x) >= (object->get_pos().x) &&
				(this->pos.x) <= (object->get_pos().x + object->get_hitbox().w));
		}
		inline bool check_rcorner_collision (object_t *object)
		{
			return ((this->pos.x + this->hitbox.w) >= (object->get_pos().x) &&
				(this->pos.x + this->hitbox.w) <= (object->get_pos().x + object->get_hitbox().w));
		}
		inline bool check_base_collision (object_t *object)
		{
			return (this->check_lcorner_collision(object) || this->check_rcorner_collision(object));
		}
		inline bool check_object_collision (object_t *object)
		{
			return ((this->pos.y + this->hitbox.h) >= object->get_pos().y && 
				this->check_base_collision(object));
		}

	public:
		rocket_t () : object_t() {}
		rocket_t (
			const hitbox_t& hitbox, 
			const point_t& position, 
			const color_t& color
		) : object_t(hitbox, position, color) {}

	public:
		void handle_event (SDL_Event& e, float time);
		void physics (float time);
};

class mountain_t : public object_t 
{
	public:
		mountain_t () {}
		mountain_t (const hitbox_t& hitbox);
};

#endif