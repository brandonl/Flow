#ifndef OPENING_SCENE_H__
#define OPENING_SCENE_H__

#include "Core/App.h"
#include "Core/VertexArray.h"
#include "Core/BufferObject.h"
#include "Core/Mesh.h"
#include "Core/Texture2.h"
#include "Core/GPUProgram.h"

using namespace flow;

class Opening : public App
{
public:
	Opening();
	~Opening();

	void doInit();
	void doUpdate();
	void doDraw();

private:
	VertexArray vao;
	BufferObject vbo;
	BufferObject ibo;

	struct Model
	{
		Mesh mesh;
		Texture2 texture;
		GPUProgram shader;
		std::vector<unsigned short> indexes;
		unsigned minix, maxix;
	};
	Model model;
	GLuint texture1;
};

#endif