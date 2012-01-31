#ifndef OPENING_SCENE_H__
#define OPENING_SCENE_H__

#include "Core/camera.h"
#include "Core/matrix_stack.h"
#include "Core/buffer_object.h"
#include "Core/shader.h"
#include "Core/mesh.h"
#include "Core/shapes.h"

#include "scene.h"
#include "Core/texture.h"

class Opening : public Scene
{
public:
	Opening() : Scene()  
	{
	}

	~Opening();

	void init();
	void update();
	void draw();

private:
	Matrix_Stack mv, p;
	Camera cam;
	Mesh obj;
	Texture texture;

	Buffer_Object vbo;
	Buffer_Object ibo;
	GLuint vao;
	Shader shader;
};

#endif