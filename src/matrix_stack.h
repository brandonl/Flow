#ifndef __MATRIX_STACK_H__
#define __MATRIX_STACK_H__
#include <glm/glm.hpp>

class Matrix_Stack
{
	public:
		Matrix_Stack( int d = 32 );
		~Matrix_Stack();

		void load_identity();
		void save();
		void restore();
		void modify( const glm::mat4& m );

		void scale( float, float, float );
		void translate( float, float, float );

		void rotate( float, float, float, float );
		void rotate_about_x( float angle );
		void rotate_about_y( float angle );
		void rotate_about_z( float angle );

		const glm::mat4& get_matrix();

	private:
		int depth;
		int pointer;
		glm::mat4 *stack;
};

#endif
