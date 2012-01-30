#ifndef PRIM_SHAPES_H__
#define PRIM_SHAPES_H__

#include "mesh.h"

namespace shape
{
	//-------------------------------------------------------------------
	// Primitives code based off of source code from OpenGL SuperBible 5ed.
	/////////////////////////////////////////////////////////////////////
	void build_cube( float r, Mesh &mesh, const Color& col = Color() )
	{
		// Clear mesh information if reusing this object since it will cause 
		// problems with buffer object drawing.
		if( !mesh.get_vertex_count() )
			mesh.reset();

		mesh.mesh_type = Mesh::TRI_MESH;
		mesh.poly_mode = Mesh::FILL;
		mesh.is_indexed = true; 

			/////////////////////////////////////////////////////////
			// Top of cube
		Polygon polygon = Polygon();
		polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col );
		polygon.add_vertex( r,		r,		-r,		r,		0,		0.0f,	r,		0.0f, col );
		polygon.add_vertex( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col  );
		polygon.add_vertex( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col  );
		polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	r,		0.0f, col  );
		mesh.add_poly( polygon );

			//////////////////////////////////////////////////////
			// Bottom of cube
		polygon = Polygon();
		polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
		polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	-r,		0.0f, col  );
		polygon.add_vertex( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( -r,		-r,		r,		0,		r,		0.0f,	-r,		0.0f, col  );
		polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
		polygon.add_vertex( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
		mesh.add_poly( polygon );

		//////////////////////////////////////////////////////
			// Left side of cube
		polygon = Polygon();
		polygon.add_vertex( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
		polygon.add_vertex( -r,	r,		-r,		r,		0,		-r,		0.0f,	0.0f, col  );
		polygon.add_vertex( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
		polygon.add_vertex( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
		polygon.add_vertex( -r,	-r,		r,		0,		r,		-r,		0.0f,	0.0f, col  );
		mesh.add_poly( polygon );

		/////////////////////////////////////////////////////
			// Right side of cube
		polygon = Polygon();
		polygon.add_vertex( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
		polygon.add_vertex( r,		r,		-r,		r,		0,		r,		0.0f,	0.0f, col  );
		polygon.add_vertex( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
		polygon.add_vertex( r,		-r,		r,		0,		r,		r,		0.0f,	0.0f, col  );
		polygon.add_vertex( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
		mesh.add_poly( polygon );

		//////////////////////////////////////////////////////
			// Front side of cube
		polygon = Polygon();
		polygon.add_vertex( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
		polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	0.0f,	r, col  );
		polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
		polygon.add_vertex( -r,		-r,		r,		0,		0,		0.0f,	0.0f,	r, col  );
		polygon.add_vertex( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
		mesh.add_poly( polygon );

		////////////////////////////////////////////////////
			// Back side of cube
		polygon = Polygon();
		polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
		polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	0.0f,	-r, col  );
		polygon.add_vertex( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
		polygon.add_vertex( r,		r,		-r,		r,		r,		0.0f,	0.0f,	-r, col  );
		polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
		mesh.add_poly( polygon );
	}	

	void build_sphere( float r, int lats, int longs, Mesh &mesh, const Color& col = Color() )
	{
		if( !mesh.get_vertex_count() )
			mesh.reset();

		mesh.mesh_type = Mesh::TRI_MESH;
		mesh.poly_mode = Mesh::FILL;
		mesh.is_indexed = true;

		float drho = (float)(3.141592653589) / (float) longs;
		float dtheta = 2.0f * (float)(3.141592653589) / (float) lats;
		float ds = 1.0f / (float) lats;
		float dt = 1.0f / (float) longs;
		float t = 1.0f;	
		float s = 0.0f;
	
		Polygon polygon;
		Vertex v0, v1, v2, v3;
		for( int i = 0; i < longs; ++i )
		{
			float rho = (float)i * drho;
			float srho = (float)( sin(rho) );
			float crho = (float)( cos(rho) );
			float srhodrho = (float)( sin( rho + drho ) );
			float crhodrho = (float)( cos( rho + drho ) );
			s = 0.0f;

			for( int j = 0; j < lats; ++j )
			{
				float theta = ( j == lats ) ? 0.0f : j * dtheta;
				float stheta = (float)( -sin(theta) );
				float ctheta = (float)( cos(theta) );		
				float x = stheta * srho;
				float y = ctheta * srho;
				float z = crho;
				v0 = Vertex( x*r,	y*r,	z*r,	s,		t,		x,	y,	z, col );
				/////////////////////////////////////////////////////////

							x = stheta * srhodrho;
				y = ctheta * srhodrho;
				z = crhodrho;
				v1 = Vertex( x*r,	y*r,	z*r,	s,		t-dt,	x,	y,	z, col );
				/////////////////////////////////////////////////////////

				theta = ( ( j + 1 ) == lats ) ? 0.0f : ( j + 1 ) * dtheta;
				stheta = (float)( -sin(theta) );
				ctheta = (float)( cos(theta) );	
				x = stheta * srho;
				y = ctheta * srho;
				z = crho;
				s += ds;
				v2 = Vertex( x*r,	y*r,	z*r,	s,		t,		x,	y,	z, col );
				/////////////////////////////////////////////////////////

						x = stheta * srhodrho;
				y = ctheta * srhodrho;
				z = crhodrho;
				v3 = Vertex( x*r,	y*r,	z*r,	s,		t-dt,	x,	y,	z, col );
				/////////////////////////////////////////////////////////
			
				polygon = Polygon();
				polygon.add_vertex( v0 );
				polygon.add_vertex( v1 );
				polygon.add_vertex( v2 );
				mesh.add_poly( polygon );

				/////////////////////////////////////////////////////////
				// Rearrange and and as next poly...
				polygon = Polygon();
				polygon.add_vertex( v1 );
				polygon.add_vertex( v3 );
				polygon.add_vertex( v2 );
				mesh.add_poly( polygon );
			}
			t -= dt;
		}
	}

	void build_torus( float outer_radius, float inner_radius, int num_major, int num_minor, Mesh &mesh, const Color& col = Color() )
	{
		if( !mesh.get_vertex_count() )
			mesh.reset();

		mesh.mesh_type = Mesh::TRI_MESH;
		mesh.poly_mode = Mesh::FILL;
		mesh.is_indexed = true;

		double major_step = 2.0f * 3.141592653589 / num_major;
		double minor_step = 2.0f * 3.141592653589 / num_minor;
		Polygon polygon;
		Vertex v0, v1, v2, v3;
		float s, t;

			for( int i = 0; i < num_major; ++i )
		{
			double a0 = i * major_step;
			double a1 = a0 + major_step;
			float x0 = (float) cos(a0);
			float y0 = (float) sin(a0);
			float x1 = (float) cos(a1);
			float y1 = (float) sin(a1);

			for( int j = 0; j < num_minor; ++j )
			{
				double b = j * minor_step;
				float c = (float)cos(b);
				float r = inner_radius * c + outer_radius;
				float z = inner_radius * (float)sin(b);

				///////////////////////////////////////////////////////////////////
				// First point
				s = (float)(i)/(float)(num_major);
				t = (float)(j)/(float)(num_minor);
				v0 = Vertex( x0*r,	y0*r,	z,	s,		t,		x0*c,	y0*c,	z/inner_radius, col );
			
				///////////////////////////////////////////////////////////////////
				// Second point
				s = (float)(i+1)/(float)(num_major);
				t = (float)(j)/(float)(num_minor);
				v1 = Vertex( x1*r,	y1*r,	z,	s,		t,		x1*c,	y1*c,	z/inner_radius, col );

				///////////////////////////////////////////////////////////////////			
				// Next one over
				b = (j+1) * minor_step;
				c = (float) cos(b);
				r = inner_radius * c + outer_radius;
				z = inner_radius * (float) sin(b);

				// Third (based on first)
				s = (float)(i)/(float)(num_major);
				t = (float)(j+1)/(float)(num_minor);
				v2 = Vertex( x0*r,	y0*r,	z,	s,		t,		x0*c,	y0*c,	z/inner_radius, col );
			
				///////////////////////////////////////////////////////////////////
				// Fourth (based on second)
				s = (float)(i+1)/(float)(num_major);
				t = (float)(j+1)/(float)(num_minor);
				v3 = Vertex( x1*r,	y1*r,	z,	s,		t,		x1*c,	y1*c,	z/inner_radius, col );

				polygon = Polygon();
				polygon.add_vertex( v0 );
				polygon.add_vertex( v1 );
				polygon.add_vertex( v2 );
				mesh.add_poly( polygon );

				/////////////////////////////////////////////////////////
				// Rearrange and and as next poly...
				polygon = Polygon();
				polygon.add_vertex( v1 );
				polygon.add_vertex( v3 );
				polygon.add_vertex( v2 );
				mesh.add_poly( polygon );			
			}
		}
	}

	void build_bbox( const glm::vec3& min, const glm::vec3& max, Mesh &mesh, const Color& col = Color() )
	{
		if( !mesh.get_vertex_count() )
			mesh.reset();

		mesh.mesh_type = Mesh::LINE_STRIP_MESH;
		mesh.poly_mode = Mesh::LINES;
		mesh.is_indexed = false; 

		Polygon polygon = Polygon();
		polygon.add_vertex( min.x, min.y, min.z, col );
		polygon.add_vertex( max.x, min.y, min.z, col  );
		polygon.add_vertex( max.x, min.y, max.z, col  ); 
		polygon.add_vertex( min.x, min.y, max.z, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( min.x, min.y, min.z, col  );
		polygon.add_vertex( min.x, max.y, min.z, col  );
		polygon.add_vertex( min.x, max.y, max.z, col  );
		polygon.add_vertex( max.x, max.y, max.z, col  ); 
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( max.x, max.y, min.z, col  );
		polygon.add_vertex( min.x, max.y, min.z, col  );
		polygon.add_vertex( min.x, max.y, max.z, col  );
		polygon.add_vertex( min.x, min.y, max.z, col  );
		mesh.add_poly( polygon );

		polygon = Polygon();
		polygon.add_vertex( max.x, min.y, max.z, col  );
		polygon.add_vertex( max.x, max.y, max.z, col  );
		polygon.add_vertex( max.x, max.y, min.z, col  );
		polygon.add_vertex( max.x, min.y, min.z, col  );
		mesh.add_poly( polygon );
	}
};

#endif