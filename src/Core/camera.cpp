#include "Camera.h"
#include <glm/gtx/rotate_vector.hpp>
#include <glm/gtc/quaternion.hpp>
#include "Input.h"
#include "Window.h"

using namespace flow;

Camera::Camera()
{
	CAM_UP		=	0.11f;        
	CAM_DOWN	=	-0.11f;     
	CAM_LEFT	=	 0.02f;         
	CAM_RIGHT	=	-0.02f;          
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
	upDir = u;
}

void Camera::update()
{
	glm::vec2 mp = Input::getMousePosition();
	Input::setMousePosition(  Window::getWidth() >> 1, Window::getHeight() >> 1 );
	rotate( mp, Window::getWidth() >> 1, Window::getHeight() >> 1 );

	if( Input::isKeyHeld( 'W' ) ) 
		move( CAM_UP );

	if( Input::isKeyHeld( 'S' ) ) 
		move( CAM_DOWN );

	if( Input::isKeyHeld( 'A' ) )
		rotate( CAM_LEFT, glm::vec3( 0.0f, 1.0f, 0.0f ) ); 

	if( Input::isKeyHeld('D' ) )
		rotate( CAM_RIGHT, glm::vec3( 0.0f, 1.0f, 0.0f ) );

	if( Input::isKeyHeld( 'Q' ) )
		strafe( STRAFE_LEFT ); 

	if( Input::isKeyHeld( 'E' ) )
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

void Camera::rotate( const glm::vec2& mousePos, int mid_x, int mid_y )
{
	float y_dir = 0.0f;
	float y_rot = 0.0f;

	if( ( mousePos.x == mid_x ) && ( mousePos.y == mid_y ) )
		return;

	y_dir = (float)( mid_x - mousePos.x ) / 1000.0f;
	y_rot = (float)( mid_y - mousePos.y ) / 1000.0f;

	lastRotAngle -= y_rot;

	if( lastRotAngle > 1.0f )
	{
		lastRotAngle = 1.0f;
		return;
	}
	if( lastRotAngle < -1.0f )
	{
		lastRotAngle = -1.0f;
		return;
	}

	glm::vec3 perp_focus_axis = glm::cross( ( focus - position ), upDir );

	perp_focus_axis = glm::normalize( perp_focus_axis );
	rotate( y_rot, perp_focus_axis );
	rotate( y_dir, glm::vec3( 0.0f, 1.0f, 0.0f ) );
}

void Camera::strafe( float direction )
{
	calculateStrafe();
	update( strafeDir, direction );
}

void Camera::calculateStrafe()
{
	glm::vec3 direction = focus - position;
	direction = glm::normalize( direction );

	glm::vec3 cross = glm::cross( direction, upDir );
	strafeDir = cross;
}
