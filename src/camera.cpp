#include "camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include "input.h"
#include "window.h"

Camera::Camera()
{
	CAM_UP		=	0.11f;        
	CAM_DOWN	=	-0.11f;     
	CAM_LEFT	=	 0.05f;         
	CAM_RIGHT	=	-0.05f;          
	STRAFE_LEFT	=	-0.05f;
	STRAFE_RIGHT=	0.05f;
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

void Camera::update()
{
	glm::vec2 mp = Input::get_mouse_position();
	Input::set_mouse_position(  Window::get_width() >> 1, Window::get_height() >> 1 );
	rotate( mp, Window::get_width() >> 1, Window::get_height() >> 1 );

	if( Input::is_key_held( 'W' ) ) 
		move( CAM_UP );

	if( Input::is_key_held( 'S' ) ) 
		move( CAM_DOWN );

	if( Input::is_key_held( 'A' ) )
		rotate( CAM_LEFT, glm::vec3( 0.0f, 1.0f, 0.0f ) ); 

	if( Input::is_key_held('D' ) )
		rotate( CAM_RIGHT, glm::vec3( 0.0f, 1.0f, 0.0f ) );

	if( Input::is_key_held( 'Q' ) )
		strafe( STRAFE_LEFT ); 

	if( Input::is_key_held( 'E' ) )
		strafe( STRAFE_RIGHT );
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
