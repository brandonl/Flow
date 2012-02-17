#ifndef SCENE_H
#define SCENE_H

#include <list>
#include <iostream>
#include <glm/glm.hpp>

#include "Core/Uncopyable.h"
#include "Core/App.h"

class Scene;

class Entity : private Uncopyable
{
	public:
		explicit Entity( const std::string tag = "" ) : tag(tag), condemned(false) {};
		virtual ~Entity() = 0;

		virtual void update() = 0;
		virtual void draw() const = 0;
		virtual void onCollission( Entity *collider ) = 0;
		virtual const glm::vec2& pos() const = 0;
	
		unsigned int id;
		std::string tag;
		bool condemned;
};

class Scene : private Uncopyable
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
		unsigned int entityIdCount;
};


#endif
