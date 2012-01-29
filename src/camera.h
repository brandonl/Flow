#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

class Camera
{
	public:
		Camera();
		~Camera();

		void set( const glm::vec3& p, const glm::vec3& v, const glm::vec3& u );
		void update( const glm::vec3& direction, float dir );

		void move( float direction );
		void rotate( float angle, const glm::vec3& speed );
		void rotate( const glm::vec2& mouse_position, int mid_x, int mid_y );
		void strafe( float direction );

		void calculate_strafe();

		glm::vec3 position;
		glm::vec3 focus;
		glm::vec3 up_direction;
		glm::vec3 strafe_direction;
		float last_rotation_angle;
};

#endif