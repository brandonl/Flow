#include "Shapes.h"

namespace flow
{
	namespace shape
	{
		void build_cube( float r, Mesh &mesh, const Color& col )
		{
			// Clear mesh information if reusing this object since it will cause 
			// problems with buffer object drawing.
			if( !mesh.vertexCount() )
				mesh.reset();

				/////////////////////////////////////////////////////////
				// Top of cube
			Plane polygon = Plane();
			polygon.add( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col );
			polygon.add( r,		r,		-r,		r,		0,		0.0f,	r,		0.0f, col );
			polygon.add( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col  );
			polygon.add( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col  );
			polygon.add( -r,		r,		r,		0,		r,		0.0f,	r,		0.0f, col  );
			mesh.add( polygon );

				//////////////////////////////////////////////////////
				// Bottom of cube
			polygon = Plane();
			polygon.add( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
			polygon.add( r,		-r,		-r,		r,		0,		0.0f,	-r,		0.0f, col  );
			polygon.add( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( -r,		-r,		r,		0,		r,		0.0f,	-r,		0.0f, col  );
			polygon.add( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
			polygon.add( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
			mesh.add( polygon );

			//////////////////////////////////////////////////////
				// Left side of cube
			polygon = Plane();
			polygon.add( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
			polygon.add( -r,	r,		-r,		r,		0,		-r,		0.0f,	0.0f, col  );
			polygon.add( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
			polygon.add( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
			polygon.add( -r,	-r,		r,		0,		r,		-r,		0.0f,	0.0f, col  );
			mesh.add( polygon );

			/////////////////////////////////////////////////////
				// Right side of cube
			polygon = Plane();
			polygon.add( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
			polygon.add( r,		r,		-r,		r,		0,		r,		0.0f,	0.0f, col  );
			polygon.add( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
			polygon.add( r,		-r,		r,		0,		r,		r,		0.0f,	0.0f, col  );
			polygon.add( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
			mesh.add( polygon );

			//////////////////////////////////////////////////////
				// Front side of cube
			polygon = Plane();
			polygon.add( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
			polygon.add( r,		r,		r,		r,		r,		0.0f,	0.0f,	r, col  );
			polygon.add( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
			polygon.add( -r,		-r,		r,		0,		0,		0.0f,	0.0f,	r, col  );
			polygon.add( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
			mesh.add( polygon );

			////////////////////////////////////////////////////
				// Back side of cube
			polygon = Plane();
			polygon.add( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
			polygon.add( -r,		-r,		-r,		0,		0,		0.0f,	0.0f,	-r, col  );
			polygon.add( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
			polygon.add( r,		r,		-r,		r,		r,		0.0f,	0.0f,	-r, col  );
			polygon.add( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
			mesh.add( polygon );
		}	

		void build_sphere( float r, int lats, int longs, Mesh &mesh, const Color& col )
		{
			if( !mesh.vertexCount() )
				mesh.reset();

			float drho = (float)(3.141592653589) / (float) longs;
			float dtheta = 2.0f * (float)(3.141592653589) / (float) lats;
			float ds = 1.0f / (float) lats;
			float dt = 1.0f / (float) longs;
			float t = 1.0f;	
			float s = 0.0f;
	
			Plane polygon;
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
			
					polygon = Plane();
					polygon.add( v0 );
					polygon.add( v1 );
					polygon.add( v2 );
					mesh.add( polygon );

					/////////////////////////////////////////////////////////
					// Rearrange and and as next poly...
					polygon = Plane();
					polygon.add( v1 );
					polygon.add( v3 );
					polygon.add( v2 );
					mesh.add( polygon );
				}
				t -= dt;
			}
		}

		void build_torus( float outer_radius, float inner_radius, int num_major, int num_minor, Mesh &mesh, const Color& col )
		{
			if( !mesh.vertexCount() )
				mesh.reset();

			double major_step = 2.0f * 3.141592653589 / num_major;
			double minor_step = 2.0f * 3.141592653589 / num_minor;
			Plane polygon;
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

					polygon = Plane();
					polygon.add( v0 );
					polygon.add( v1 );
					polygon.add( v2 );
					mesh.add( polygon );

					/////////////////////////////////////////////////////////
					// Rearrange and and as next poly...
					polygon = Plane();
					polygon.add( v1 );
					polygon.add( v3 );
					polygon.add( v2 );
					mesh.add( polygon );			
				}
			}
		}

			void build_bbox( const glm::vec3& min, const glm::vec3& max, Mesh &mesh, const Color& col )
		{
			if( !mesh.vertexCount() )
				mesh.reset();

			Plane polygon = Plane();
			polygon.add( min.x, min.y, min.z, col );
			polygon.add( max.x, min.y, min.z, col  );
			polygon.add( max.x, min.y, max.z, col  ); 
			polygon.add( min.x, min.y, max.z, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( min.x, min.y, min.z, col  );
			polygon.add( min.x, max.y, min.z, col  );
			polygon.add( min.x, max.y, max.z, col  );
			polygon.add( max.x, max.y, max.z, col  ); 
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( max.x, max.y, min.z, col  );
			polygon.add( min.x, max.y, min.z, col  );
			polygon.add( min.x, max.y, max.z, col  );
			polygon.add( min.x, min.y, max.z, col  );
			mesh.add( polygon );

			polygon = Plane();
			polygon.add( max.x, min.y, max.z, col  );
			polygon.add( max.x, max.y, max.z, col  );
			polygon.add( max.x, max.y, min.z, col  );
			polygon.add( max.x, min.y, min.z, col  );
			mesh.add( polygon );
		}
	};
};