#ifndef __SHADER_SOURCE_H__
#define __SHADER_SOURCE_H__

#include "Resource.h"
#include <memory>

namespace flow
{
	class ShaderSource : public Resource
	{
		public:
			ShaderSource( const std::string& fn );
			ShaderSource& operator=( ShaderSource&& m );

			const std::string& getSource() const;
			
		private:
			std::string source;
	};

	inline const std::string& ShaderSource::getSource() const
	{
		return source;
	}
};
#endif