#include "scene.h"
#include <string>

Scene::Scene()
	:	entity_id_counter(0)
{
	std::cout << "Creating Scene..." << this << std::endl;
}

Scene::~Scene()
{
	std::cout << "Destroying Scene..." << this << std::endl;
}

void Scene::update()
{
	for( auto cit = entities.begin(); cit != entities.end(); ++cit )
	{
		if( (*cit)->condemned == true )
			cit = entities.erase( cit );
	}
	
	for( auto cit = entities.begin(); cit != entities.end(); ++cit )
		(*cit)->update();
}

void Scene::draw()
{
	for( auto cit = entities.cbegin(); cit != entities.cend(); ++cit )
		(*cit)->draw();
}

void Scene::add( Entity *ent )
{
	ent->id = entity_id_counter++;
	std::cout << "Creating " << ent->tag << " with id " << ent->id << std::endl;
	entities.push_back( std::shared_ptr<Entity>( ent ));
}

