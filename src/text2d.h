#ifndef TEXT2D_H__
#define TEXT2D_H__

namespace Text
{
	void init(const char * texturePath);
	void print(const char * text, int x, int y, int size);
	void clean();
};

#endif