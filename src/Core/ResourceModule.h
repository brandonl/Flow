#ifndef RESOURCE_MODULE_H
#define RESOURCE_MODULE_H

#include <unordered_map>
#include "Utils.h"
#include "Settings.h"
#include <memory>
#include <cstdio>

namespace flow
{
	class Resource;

	class Resources : private Uncopyable
	{
		public:
			template <class T>
			static void request( const std::string& filename, std::shared_ptr<T> &rsrc )
			{
				static Resources tmpResLoader;
				tmpResLoader.processRequest( filename, rsrc );
			}

		private:
			template <class T>
			void	processRequest( const std::string& filename, std::shared_ptr<T> &rsrc );

		private:
			std::unordered_map< std::string, std::shared_ptr<Resource> > cache;
	};

	template <class T>
	void Resources::processRequest( const std::string& filename, std::shared_ptr<T> &rsrc )
	{
		auto ix = cache.find( filename );

		if( ix != cache.end() ) //Found
		{
			rsrc = std::dynamic_pointer_cast<T>( ix->second );
			printf( "Resource found cached: %s.\n", filename.c_str() );
		}

		else //Not found in cache
		{
			printf( "New resource created: %s.\n", filename.c_str() );
			rsrc = std::make_shared<T>( std::string( RESOURCE_DIR ) + filename );
			cache.emplace( std::make_pair( filename, rsrc ) );
		}
	}
};


#endif
