#ifndef PARTICLE_SCENE_H__
#define PARTICLE_SCENE_H__

#include "Scene.h"
#include "VertexArray.h"
#include "Core/BufferObject.h"
#include "Core/Shader.h"
#include "Core/Mesh.h"
#include "Core/Texture.h"

class Particles : public Scene
{
public:
	Particles();
	~Particles();

	void init();
	void update();
	void draw();

private:
	VertexArray vao;
	BufferObject vbo;
	BufferObject ibo;

	struct Model
	{
		Shader shader;
		Texture texture;
		Mesh mesh;
		std::vector<unsigned short> indexes;
		unsigned minix, maxix;
	} obj;

	GLuint texture1D;
};

#endif