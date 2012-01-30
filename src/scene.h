#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <iostream>
#include <glm/glm.hpp>

class Scene;

class Entity
{
	public:
		explicit Entity( const std::string tag = "" ) : tag(tag), condemned(false) {};
		virtual ~Entity() = 0;

		virtual void update() = 0;
		virtual void draw() const = 0;
		virtual void on_collission( Entity *collider ) = 0;
		virtual const glm::vec2& get_pos() const = 0;
	
		unsigned int id;
		std::string tag;
		bool condemned;
};

class Scene
{
	public:
		explicit Scene();
		virtual ~Scene();

		virtual void init() = 0;
		virtual void update();
		virtual void draw();

		void			add( Entity* ent );
		//void			remove( Entity* ent );
		//const Entity*	find( Entity *ent );
		//void			swap( Entity *ent );
		//void			clear();

		std::list< std::shared_ptr<Entity> > entities;

	private:
		unsigned int entity_id_counter;
};


#endif
