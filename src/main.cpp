#define WIN32_LEAN_AND_MEAN   // This trims down the libraries.
#define VC_LEANMEAN           // Trims even farther.
#include <GL/glew.h>

#include "input.h"
#include "window.h"

#include "scene.h"
#include "debug.h"
#include "app.h"

#include "mesh.h"
#include "camera.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

using namespace std;

namespace
{
	const float CAM_UP				=	0.11f;             // Forward speed.
	const float CAM_DOWN			=	-0.11f;            // Backward speed.
	const float CAM_LEFT			=	0.05f;            // Left speed.
	const float CAM_RIGHT			=	-0.05f;            // Right speed.
	const float STRAFE_LEFT		=	-0.05f;
	const float STRAFE_RIGHT	=	0.05f;
}


class Grey : public Scene
{
public:
	Grey() : Scene()  
	{
	}

	~Grey(){}

	void init()
	{
		debug() << "Started scene" << endl;
	}
	void update()
	{
	}
	
	void draw()
	{
	}

private:

};

int main(int argc, char * argv[])
{
	Grey *scene = new Grey();
	scene->init();

	App app;
	app.init( "T H E g R E Y" );
	app.set( scene );
	app.run();

	delete scene;
	return 0;
}
