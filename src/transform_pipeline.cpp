#include "transform_pipeline.h"
#include "debug.h"
#include <glm/gtc/matrix_transform.hpp>

Transform_Pipeline *Transform_Pipeline::instance = NULL;

Transform_Pipeline::Transform_Pipeline()
	: current_matrix(MODEL_VIEW)
{
	if( instance != NULL )
		debug() << "Only one instance may be active at a time.\n";
	instance = this;

	instance->model_view.load_identity();
	instance->projection.load_identity(); //@TODO: CHANGE TO ORTHO OR PROJ.(2d or 3d)
}

Transform_Pipeline::~Transform_Pipeline()
{

}
void Transform_Pipeline::modify( const glm::mat4& m )
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
		instance->model_view.modify( m);
		break;
	case( PROJECTION ):
		instance->projection.modify( m );
		break;
	}
}

void Transform_Pipeline::save()
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
        instance->model_view.save();
		instance->model_view.load_identity();
		break;
	case( PROJECTION ):
		instance->projection.save();
		instance->projection.load_identity();
		break;
	}
}

void Transform_Pipeline::restore()
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
		instance->model_view.restore();
		break;
	case( PROJECTION ):
		instance->projection.restore();
		break;
	}

}

void Transform_Pipeline::select( MATRIX_MODE mode )
{
	instance->current_matrix = mode == 0 ? MODEL_VIEW : PROJECTION;
}

void Transform_Pipeline::scale( float x, float y, float z )
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
		instance->model_view.scale( x, y, z );
		break;
	case( PROJECTION ):
		instance->projection.scale( x, y, z );
		break;
	}
}

void Transform_Pipeline::translate( float x, float y, float z )
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
		instance->model_view.translate( x, y, z );
		break;
	case( PROJECTION ):
		instance->projection.translate( x, y, z );
		break;
	}
}

void Transform_Pipeline::rotate( float theta, float x, float y, float z )
{
	switch( instance->current_matrix )
	{
	case( MODEL_VIEW ):
		instance->model_view.rotate( theta, x, y, z );
		break;
	case( PROJECTION ):
		instance->projection.rotate( theta, x, y, z );
		break;
	}
}

const glm::mat4& Transform_Pipeline::get_mvp()
{
	instance->mvp = instance->model_view.get_matrix() * instance->projection.get_matrix();
	return instance->mvp;
}

const glm::mat4& Transform_Pipeline::get_mv()
{
	return instance->model_view.get_matrix();
}

const glm::mat4& Transform_Pipeline::get_p()
{
	return instance->projection.get_matrix();
}

const glm::mat4& Transform_Pipeline::get_normal()
{
	return instance->normal;//@TODO: Find normal matrix for lighting stuff
}
