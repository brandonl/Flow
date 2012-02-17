#ifndef OPENING_SCENE_H__
#define OPENING_SCENE_H__

#include "Scene.h"
#include "VertexArray.h"
#include "Core/BufferObject.h"
#include "Core/Shader.h"
#include "Core/Mesh.h"
#include "Core/Texture.h"

class Opening : public Scene
{
public:
	Opening();
	~Opening();

	void init();
	void update();
	void draw();

private:
	VertexArray vao;
	BufferObject vbo;
	BufferObject ibo;

	struct Model
	{
		Shader *shader;
		Texture texture;
		Texture bumpMap;
		Mesh mesh;
		std::vector<unsigned short> indexes;
		unsigned minix, maxix;
	} obj;

	Shader s1, s2;

	Texture floorTexture;
	VertexArray vaoFloor;
	BufferObject vboFloor;
	Mesh floorMesh;
};

#endif