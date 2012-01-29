#define WIN32_LEAN_AND_MEAN   // This trims down the libraries.
#define VC_LEANMEAN           // Trims even farther.
#include <GL/glew.h>
#include "input.h"
#include "window.h"
#include "asset_manager.h"
#include "debug.h"
#include "color.h"
#include "gl_renderer.h"
#include "mesh.h"
#include "camera.h"

#include "Systems/system_renderable_2d.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
     

#define CAM_UP			 0.11f             // Forward speed.
#define CAM_DOWN		-0.11f            // Backward speed.
#define CAM_LEFT		 0.05f             // Left speed.
#define CAM_RIGHT		-0.05f            // Right speed.
#define STRAFE_LEFT		-0.05f
#define STRAFE_RIGHT	0.05f


std::vector< const GLSL_Shader* >       shaders;
std::vector< const Texture* >           textures;
Texture                                 mutable_texture;
     
//-------------------------------------
// Singletons
Asset_Manager assets;
GL_Renderer renderer;
/////////////////////////////////////////

int main(int argc, char * argv[])
{
		assets.set_working_dir( "../../Content/Shaders/" );
        Debug::prepare();
        Debug::report( "<h3>Entry Point</h3>" );
     
		Window::open();
        Input::prepare();
        renderer.initialize();
		System_Renderable_2D system;
		Component_Index cid = system.create_new_component();
		Renderable_2D* component = system.get_component<Renderable_2D>( cid );
		srand ( time( NULL ) );
		
		component->upper_left.x = -20;
		component->upper_left.y = -20;
		component->width = 50;
		component->height = 50;

		Camera camera;
		camera.set( glm::vec3( 0.0f, 0.5f, -2.0f ), 
					glm::vec3( 0.0f, 0.5f, 0.0f ), 
					glm::vec3( 0.0f, 1.0f, 0.0f ) );

        //------------------------------------------------------------------
        // Asset Loading
        ////////////////////////////////////////////////////////////////////
        Asset_Id shader1 = assets.load_shader( "texture" );
        shaders.push_back( assets.grab<GLSL_Shader>( shader1 ) );

        shader1 = assets.load_shader( "flat" );
        shaders.push_back( assets.grab<GLSL_Shader>( shader1 ) );


		GL_Renderer::use_shader( shaders[0] );
		shaders[0]->set_int( "tex_unit0", 0 );

        assets.set_working_dir( "../../Content/Textures/" );
        Asset_Id texture1 = assets.load_texture( "uvmap.tga" );
        Asset_Id texture2 = assets.load_texture( "grass.tga" );

		Asset_Id tid = assets.load_texture( "Block.tga" );
		system.set_value( cid, "Texture_Id", (void*)&tid );

        textures.push_back( assets.grab<Texture>( texture1 ) );
        textures.push_back( assets.grab<Texture>( texture2 ) );     
        ///////////////////////////////////////////////////////////////////////////
        Mesh::set_working_dir( "../../Content/Models/" );
        Mesh obj;
		obj.import_obj( "Suzanne.obj" );

		Mesh terrain;
		terrain.import_obj( "grass.obj" );	

		Mesh light;
		light.build_sphere( 0.2f, 5, 5, Color::yellow );

		Mesh rect( Mesh::TRI_FAN_MESH );
		{
			Polygon quad;
			quad.add_vertex( (float)-0.2, (float)0.2, 0, 0, 0 );
			quad.add_vertex( (float)0.2, (float)0.2, 0, 1, 0 );
			quad.add_vertex( (float)0.2, (float)-0.2, 0, 1, 1 );
			quad.add_vertex( (float)-0.2, (float)-0.2, 0, 0, 1 );
			rect.add_poly( quad );
			GL_Renderer::add_stream( rect );
		}

     	Mesh axis;
		{
			axis.mesh_type = Mesh::LINE_MESH;
			axis.poly_mode = Mesh::LINES;
			Polygon xaxis, yaxis, zaxis;
			xaxis.add_vertex( 0.0f, 0.0f, 0.0f, Color::xred );
			xaxis.add_vertex( 1.0f, 0.0f, 0.0f, Color::xred );
			yaxis.add_vertex( 0.0f, 0.0f, 0.0f, Color( 0.0f, 1.0f, 0.0f, 1.0f ) );
			yaxis.add_vertex( 0.0f, 1.0f, 0.0f, Color( 0.0f, 1.0f, 0.0f, 1.0f ) );
			zaxis.add_vertex( 0.0f, 0.0f, 0.0f, Color( 0.0f, 0.0f, 1.0f, 1.0f ) );
			zaxis.add_vertex( 0.0f, 0.0f, 1.0f, Color( 0.0f, 0.0f, 1.0f, 1.0f ) );
			axis.add_poly( xaxis );
			axis.add_poly( yaxis );
			axis.add_poly( zaxis );
			GL_Renderer::add_dynamic( axis );
		}

		Input::bind_action_to_input( "Look Left", Input::WHILE_DOWN, 'a' );
		Input::bind_action_to_input( "Look Right", Input::WHILE_DOWN, 'd' );
		Input::bind_action_to_input( "Move Forward", Input::WHILE_DOWN, 'w' );
		Input::bind_action_to_input( "Move Backward", Input::WHILE_DOWN, 's' );
		Input::bind_action_to_input( "Strafe Left", Input::WHILE_DOWN, 'q' );
		Input::bind_action_to_input( "Strafe Right", Input::WHILE_DOWN, 'e' );
		Input::bind_action_to_input( "x", Input::ON_PRESS, 'x' );
		Input::bind_action_to_input( "y", Input::ON_PRESS, 'y' );
		Input::bind_action_to_input( "move", Input::ON_PRESS, 'm' );
		Input::bind_action_to_input( "Texture", Input::ON_PRESS, 't' );
		Input::bind_action_to_input( "Rotate", Input::WHILE_DOWN, 'r' );

		glm::mat4 projection	= glm::perspective( 35.0f, (float)Window::get_window_width() / Window::get_window_height(), 0.1f, 100.0f );
		glm::mat4 view;
		glm::mat4 model			= glm::mat4();
		glm::mat4 mv;
		glm::mat4 mvp;

        while( Window::is_open() )
		{
			Input::update();
			Window::update();

			view = glm::lookAt( camera.position, camera.focus, camera.up_direction );

			if( Input::is_happening( "Move Forward" ) ) 
				camera.move( CAM_UP );

		    if( Input::is_happening( "Move Backward" ) ) 
			   camera.move( CAM_DOWN );

			if( Input::is_happening( "Look Left" ) )
				camera.rotate( CAM_LEFT, glm::vec3( 0.0f, 1.0f, 0.0f ) ); 

		   if( Input::is_happening( "Look Right" ) )
				 camera.rotate( CAM_RIGHT, glm::vec3( 0.0f, 1.0f, 0.0f ) );

			if( Input::is_happening( "Strafe Left" ) )
				camera.strafe( STRAFE_LEFT ); 

		   if( Input::is_happening( "Strafe Right" ) )
				 camera.strafe( STRAFE_RIGHT );

		   if( Input::is_happening( "x" ) )
		   {
				Polygon quad;
				quad.add_vertex( (float)-1.2, (float)0.2, 0, 0, 1 );
				quad.add_vertex( (float)0.2, (float)0.2, 0, 1, 1 );
				quad.add_vertex( (float)0.2, (float)-1.2, 0, 1, 0 );
				quad.add_vertex( (float)-0.2, (float)-0.2, 0, 0, 0 );
				rect.reset_mesh();
				rect.add_poly( quad );
				GL_Renderer::update_stream_buffer( rect );

				component->width = 2;
		   }
		   if( Input::is_happening( "y" ) )
		   {
				Polygon quad;
				quad.add_vertex( (float)-0.2, (float)0.2, 0, 0, 0 );
				quad.add_vertex( (float)0.2, (float)0.2, 0, 1, 0 );
				quad.add_vertex( (float)0.2, (float)-0.2, 0, 1, 1 );
				quad.add_vertex( (float)-0.2, (float)-0.2, 0, 0, 1 );
				rect.reset_mesh();
				rect.add_poly( quad );
				GL_Renderer::update_stream_buffer( rect );

				component->height = 2;
		   }
		   if( Input::is_happening( "move" ) )
			   component->upper_left.x = component->upper_left.y = 0;
		   if( Input::is_happening( "Texture" ) )
			   component->texture_id = texture1;
		   if( Input::is_happening( "Rotate" ) )
			   component->degree_of_rotation += 2;

			camera.rotate( Input::get_mouse_position(), Window::get_window_width() >> 1, Window::get_window_height() >> 1 );
			glfwSetMousePos( Window::get_window_width() >> 1, Window::get_window_height() >> 1 );

			
			
			glEnable( GL_BLEND );
			GL_Renderer::begin_frame();

			//---------------------------------------------------------
			// Transformation Matrices
			///////////////////////////////////////////////////////////
			mv	= view * model;  
     		mvp	= projection * mv;

			//---------------------------------------------------------
			// Axis ( Move it up alil when matrix stack )
			///////////////////////////////////////////////////////////		
			GL_Renderer::use_shader( shaders[1] );
			shaders[1]->set_mat4( "mvp_matrix", mvp );
   			GL_Renderer::draw_mesh( &axis );  


			//---------------------------------------------------------
			// Light Box
			///////////////////////////////////////////////////////////
			glm::mat4 last_mvp = mvp;
			glm::mat4 last_model = model;
			model = glm::translate( model, glm::vec3( 0, 10, 0 ) );
			mv	= view * model;  
     		mvp	= projection * mv;
			shaders[1]->set_mat4( "mvp_matrix", mvp );
			GL_Renderer::draw_mesh( &light );
			mvp = last_mvp;
			model = last_model;

			//---------------------------------------------------------
			// Terrain And Model
			///////////////////////////////////////////////////////////
			GL_Renderer::use_shader( shaders[0] );
			shaders[0]->set_mat4( "mvp_matrix", mvp );
			GL_Renderer::bind_texture( textures[1] );
			GL_Renderer::draw_mesh( &terrain );
			GL_Renderer::bind_texture( textures[0] );
			last_mvp = mvp;
			last_model = model;
			model = glm::translate( model, glm::vec3( 0, 1, 0 ) );
			mv	= view * model;  
     		mvp	= projection * mv;
			shaders[0]->set_mat4( "mvp_matrix", mvp );
			GL_Renderer::draw_mesh( &rect );
			//GL_Renderer::draw_mesh( &obj );
			mvp = last_mvp;
			model = last_model;

			system.update();

			GL_Renderer::swap_buffers();
			GL_Renderer::end_frame();
			GL_Renderer::check_error( "Error at end of rendering loop" );

		}
        Window::close();
		Debug::report( "<h3>Successfully Exited Program</h3>" );
        return 0;
}
