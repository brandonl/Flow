#ifndef __TEXTURE_2D_H__
#define __TEXTURE_2D_H__

#include <string>
#include <windows.h>
#include <gl/gl.h>
#include "ImageRef.h"
#include "Utils.h"

namespace flow
{
	class Texture2 : public Uncopyable
	{
		public:
			Texture2(){}
			~Texture2();

			void load( const std::string &imageFileName );
			void use( bool douse = true ) const;

			const int		getHWidth() const;
			const int		getHHeight() const;
			const GLuint	getGLname() const;

		private:
			void load( const ImageRef &&iref );
		private:
			GLuint name;
			int hwidth;
			int hheight;
	};

	inline void Texture2::use( bool douse ) const
	{
		glBindTexture( GL_TEXTURE_2D, ( douse ? name : 0 ) );
	}

	inline const int Texture2::getHWidth() const
	{
		return hwidth;
	}

	inline const int Texture2::getHHeight() const
	{
		return hheight;
	}

	inline const GLuint Texture2::getGLname() const
	{
		return name;
	}
};


#endif
