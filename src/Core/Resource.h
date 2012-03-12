#ifndef RESOURCE_H
#define RESOURCE_H

#include <string>
#include "Utils.h"

namespace flow
{
	class Resource : private Uncopyable
	{
		friend class Resources;

		protected:
			Resource( std::string fn = "" ) : filename(fn) {}
			virtual ~Resource() = 0;

		public:
			const std::string& getFileName() const;

		private:
			std::string filename;
	};

	inline const std::string& Resource::getFileName() const
	{ 
		return filename;
	}
};
#endif
