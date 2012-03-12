#ifndef __CAMERA_H__
#define __CAMERA_H__

#include <glm/glm.hpp>

namespace flow
{
	class Camera
	{
		public:
			Camera();
			~Camera();

			void set( const glm::vec3& p, const glm::vec3& v, const glm::vec3& u );
			void update();
			void update( const glm::vec3& direction, float dir );

			void move( float direction );
			void rotate( float angle, const glm::vec3& speed );
			void rotate( const glm::vec2& mousePos, int mid_x, int mid_y );
			void strafe( float direction );

			void calculateStrafe();

			glm::vec3 position;
			glm::vec3 focus;
			glm::vec3 upDir;
			glm::vec3 strafeDir;
			float lastRotAngle;

		private:
			float CAM_UP;
			float CAM_DOWN;
			float CAM_LEFT;
			float CAM_RIGHT;
			float STRAFE_LEFT;
			float STRAFE_RIGHT;
	};
};

#endif