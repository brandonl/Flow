#ifndef __SHADER_REF_H__
#define __SHADER_REF_H__

#include "ShaderSource.h"
#include "ResourceModule.h"

namespace flow
{
	class ShaderRef
	{
		public:
			explicit ShaderRef( const std::string& fn = "" )
			{
				if( fn.size() )
					Resources::request( fn, shaderSrc );
			}

			ShaderRef( ShaderRef&& m )
				:	shaderSrc( std::move( m.shaderSrc ) )
			{
			}

			ShaderRef& operator=( ShaderRef&& m )
			{
				shaderSrc.swap( m.shaderSrc );
				return *this;
			}

			const std::string& getFileName() const;
			operator bool() const;
			const std::string& referencedData() const;

		private:
			std::shared_ptr< ShaderSource > shaderSrc;
	};

	inline const std::string& ShaderRef::getFileName() const
	{
		return shaderSrc->getFileName();
	}

	inline const std::string& ShaderRef::referencedData() const
	{
		return shaderSrc->getSource();
	}

	inline ShaderRef::operator bool() const
	{
		return static_cast<bool>( shaderSrc );
	}
};

#endif