#include "Scene.h"
#include <string>

Scene::Scene()
	:	entityIdCount(0)
{
}

Scene::~Scene()
{
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
	ent->id = entityIdCount++;
	std::cout << "Creating " << ent->tag << " with id " << ent->id << std::endl;
	entities.push_back( std::shared_ptr<Entity>( ent ));
}

