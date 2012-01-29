#ifndef __TRANSFORM_PIPELINE__
#define __TRANSFORM_PIPELINE__
#include "matrix_stack.h"


class Transform_Pipeline
{
	public:
		enum MATRIX_MODE
		{
			MODEL_VIEW = 0,
			PROJECTION
		};

		Transform_Pipeline();
		~Transform_Pipeline();
	
		static void modify( const glm::mat4& m );
		static void save();
		static void restore();
		static void select( MATRIX_MODE );
		static void scale( float, float, float );
		static void translate( float, float, float );
		static void rotate( float, float, float, float );
		static const glm::mat4& get_mvp();
		static const glm::mat4& get_mv();
		static const glm::mat4& get_p();
		static const glm::mat4& get_normal();
		
	private:
		MATRIX_MODE		current_matrix;
		glm::mat4		mvp;
		glm::mat4		normal;
		Matrix_Stack 	model_view;
		Matrix_Stack 	projection;
		static Transform_Pipeline *instance;
};

#endif
