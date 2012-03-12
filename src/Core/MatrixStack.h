#ifndef __MATRIX_STACK_H__
#define __MATRIX_STACK_H__
#include <glm/glm.hpp>

namespace flow
{
	class MatrixStack
	{
		public:
			MatrixStack( int d = 32 );
			~MatrixStack();

			void loadIdentity();
			void save();
			void restore();
			void modify( const glm::mat4& m );

			void scale( float, float, float );
			void translate( float, float, float );
			void rotate( float, float, float, float );
		
			void set( const glm::mat4& m );
			const glm::mat4& top();

		private:
			int depth;
			int pointer;
			glm::mat4 *stack;
	};
};
#endif
