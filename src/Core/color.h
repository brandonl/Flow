#ifndef COLOR_H
#define COLOR_H

#include <string>

namespace flow
{
	struct Color
	{
		Color();
		Color( float r, float g, float b, float a );
		explicit Color( const std::string &hexValue );

		bool operator ==( const Color& rhs ) const;
		bool operator !=( const Color& rhs ) const;

		float r, g, b, a;

		static Color black;
		static Color orange;
		static Color grey;
		static Color purple;
		static Color yellow;
		static Color xred;
		static Color red;
		static Color cyan;
		static Color green;
		static Color blue;

	};

	inline bool Color::operator ==( const Color& rhs ) const
	{
		return (	( fabs( this->r	- rhs.r ) < 0.00001f ) &&
					( fabs( this->g	- rhs.g ) < 0.00001f ) && 
					( fabs( this->b	- rhs.b ) < 0.00001f ) && 
					( fabs( this->a	- rhs.a ) < 0.00001f ) );
	}

	inline bool Color::operator !=( const Color& rhs ) const
	{
		return !operator==( rhs );
	}
};
#endif
