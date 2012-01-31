#ifndef __TEXTURE_H__
#define __TEXTURE_H__

#include <string>

class Texture
{
	public:
		explicit Texture();
		~Texture();

		bool load(	const std::string& filename, float anisotropic_amount = 16);
		unsigned int get_name() const;

	private:
		void unload();

		std::string filename;
		unsigned int name;
		float anisotropic_amount;
};

#endif