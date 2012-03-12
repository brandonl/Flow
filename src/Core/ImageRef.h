#ifndef __IMAGE_REF_H__
#define __IMAGE_REF_H__

#include "Image.h"
#include "ResourceModule.h"

namespace flow
{
	class ImageRef
	{
		public:
			explicit ImageRef( const std::string& fn = "" )
			{
				if( fn.size() )
					Resources::request( fn, image );
			}

			ImageRef( ImageRef&& m )
				:	image( std::move( m.image ) )
			{
			}

			ImageRef& operator=( ImageRef&& m )
			{
				image.swap( m.image );
				return *this;
			}

			operator bool() const
			{
				return static_cast<bool>( image );
			}

			const void* referencedData() const;
			const std::string& getImageName() const;
			const int getImageWidth() const;
			const int getImageHeight() const;

		private:
			std::shared_ptr< Image > image;
	};

	inline const void* ImageRef::referencedData() const
	{
		return image->getData();
	}

	inline const std::string& ImageRef::getImageName() const
	{
		return image->getFileName();
	}
	inline const int ImageRef::getImageWidth() const
	{
		return image->getWidth();
	}

	inline const int ImageRef::getImageHeight() const
	{
		return  image->getHeight();
	}
};

#endif