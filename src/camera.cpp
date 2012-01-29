#include "camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::set( const glm::vec3&  p, const glm::vec3&  v, const glm::vec3&  u )
{
	position = p;
	focus = v;
	up_direction = u;
}

void Camera::update( const glm::vec3& direction, float dir )
{
	position.x += direction.x * dir;
	position.z += direction.z * dir;

	focus.x += direction.x * dir;
	focus.z += direction.z * dir;
}

void Camera::move( float direction )
{
	glm::vec3 look_direction;
	look_direction = focus - position;
	look_direction = glm::normalize( look_direction );

	update( look_direction, direction );
}

void Camera::rotate( float angle, const glm::vec3&  speed )
{
	glm::vec3 new_look_direction, look_direction;
	float cos_angle = 0.0f, sin_angle = 0.0f;

	cos_angle = (float)glm::cos( angle );
	sin_angle = (float)glm::sin( angle );

	look_direction = focus - position;

	look_direction = glm::normalize( look_direction );

	// Calculate the new X position.
	new_look_direction.x = ( cos_angle + (1 - cos_angle) * speed.x) * look_direction.x;
	new_look_direction.x += ( ( 1 - cos_angle) * speed.x * speed.y - speed.z * sin_angle)* look_direction.y;
	new_look_direction.x += ( ( 1 - cos_angle) * speed.x * speed.z + speed.y * sin_angle) * look_direction.z;

	// Calculate the new Y position.
	new_look_direction.y = ( ( 1 - cos_angle ) * speed.x * speed.y + speed.z * sin_angle ) * look_direction.x;
	new_look_direction.y += ( cos_angle + ( 1 - cos_angle ) * speed.y ) * look_direction.y;
	new_look_direction.y += ( ( 1 - cos_angle ) * speed.y * speed.z - speed.x * sin_angle ) * look_direction.z;

	// Calculate the new Z position.
	new_look_direction.z = ( ( 1 - cos_angle ) * speed.x * speed.z - speed.y * sin_angle ) * look_direction.x;
	new_look_direction.z += ( ( 1 - cos_angle ) * speed.y * speed.z + speed.x * sin_angle ) * look_direction.y;
	new_look_direction.z += ( cos_angle + ( 1 - cos_angle ) * speed.z ) * look_direction.z;

	focus = position + new_look_direction;
}

void Camera::rotate( const glm::vec2& mouse_position, int mid_x, int mid_y )
{
	float y_dir = 0.0f;
	float y_rot = 0.0f;

	if( ( mouse_position.x == mid_x ) && ( mouse_position.y == mid_y ) )
		return;

	y_dir = (float)( mid_x - mouse_position.x ) / 1000.0f;
	y_rot = (float)( mid_y - mouse_position.y ) / 1000.0f;

	last_rotation_angle -= y_rot;

	if( last_rotation_angle > 1.0f )
	{
		last_rotation_angle = 1.0f;
		return;
	}
	if( last_rotation_angle < -1.0f )
	{
		last_rotation_angle = -1.0f;
		return;
	}

	glm::vec3 perp_focus_axis = glm::cross( ( focus - position ), up_direction );

	perp_focus_axis = glm::normalize( perp_focus_axis );
	rotate( y_rot, perp_focus_axis );
	rotate( y_dir, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

void Camera::strafe( float direction )
{
	calculate_strafe();
	update( strafe_direction, direction );
}

void Camera::calculate_strafe()
{
	glm::vec3 direction = focus - position;
	direction = glm::normalize( direction );

	glm::vec3 cross = glm::cross( direction, up_direction );
	strafe_direction = cross;
}
