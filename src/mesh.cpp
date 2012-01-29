#include "mesh.h"
#include "debug.h"
#include <string>
#include <fstream>

std::string Mesh::working_directory = "../../content/models/";

Mesh::Mesh( Mesh_Type mtype )
	:	mesh_type(mtype),
		poly_mode(FILL),
		is_indexed(false),
		max_index(0),
		min_index(4294967295),
		data_is_dirty(false)
{
}

Mesh::~Mesh()
{
}

void Mesh::add_poly( const Polygon& poly )
{
	std::vector<Vertex> pverts = poly.get_vertices();

	if( is_indexed )
	{
		for( unsigned int i = 0; i < pverts.size(); ++i )
		{
			unsigned int match = 0;
			for( match = 0; match < vertices.size(); ++match )
			{
				// Overload == operator
				if( vertices[match] == pverts[i] )
				{
					min_index = ( match < min_index ) ? match : min_index;
					max_index = ( match > max_index ) ? match : max_index;
					indexes.push_back( match );
					break;
				}
			}

			if( match == vertices.size() )
			{
				vertices.push_back( pverts[i] );
				indexes.push_back( match );
			}
		}
	}

	else // Not indexed
	{
		const Vertex *tempv = &pverts[0];
		for( unsigned int i = 0; i < pverts.size(); ++i )
		{
			vertices.push_back( tempv[i] );
		}
	}

	polys.push_back( poly );
}
/////////////////////////////////////////////////////////////////////

void Mesh::import_obj( const std::string& filename )
{
	// Clear mesh information if reusing this object since it will cause 
	// problems with buffer object drawing.
	if( data_is_dirty )
		reset();

	mesh_type = TRI_MESH;
	poly_mode = FILL;
	is_indexed = true; 

	std::string filename_and_path = working_directory + filename;
	std::ifstream in( filename_and_path.c_str() );

	if( !in.is_open() )
	{
		debug() <<"Mesh::load_obj: Failed to open object file with name " << filename << std::endl;
		return;
	}

	/////////////////////////////////////////////////////////////////////
	Polygon polygon;
	Vertex vertex;

	std::string line, tok;
	std::vector<float> verts, norms, tex_coords;

	int		ival = 0;
	float	fval1 = 0.0f, fval2 = 0.0f, fval3 = 0.0f;
	char	cval = ' ';
	/////////////////////////////////////////////////////////////////////

	while( getline( in, line ) )
	{
		std::stringstream ss;
		ss << line;
		ss >> tok;
		//-----------------------------------------------------------
		// Extract all the vertex data
		/////////////////////////////////////////////////////////////
		if( tok == "v" )
		{
			ss >> fval1 >> fval2 >> fval3;
			verts.push_back( fval1 );
			verts.push_back( fval2 );
			verts.push_back( fval3 );
		}

		else if( tok == "vn" )
		{
			ss >> fval1 >> fval2 >> fval3;
			norms.push_back( fval1 );
			norms.push_back( fval2 );
			norms.push_back( fval3 );
		}

		else if( tok == "vt" )
		{
			ss >> fval1 >> fval2;
			tex_coords.push_back( fval1 );
			tex_coords.push_back( fval2 );
		}

		//-----------------------------------------------------------
		// Extract the face data (indexes)
		/////////////////////////////////////////////////////////////
		else if( tok == "f" ) // vind/tind/nind
		{
			std::string face_tok;
			polygon = Polygon();

			while( ss >> face_tok ) 
			{
				vertex = Vertex();

				//Convert line to stringstream for str to int conversion.
        std::stringstream ss2;
        ss2 << face_tok;

				// Grab vertex index.
        ss2 >> ival;
				vertex.position[0] = verts[ (( ival - 1 )*3) ];
				vertex.position[1] = verts[ (( ival - 1 )*3) + 1 ];
				vertex.position[2] = verts[ (( ival - 1 )*3) + 2 ];

        if( ss2 && ss2.peek() == '/' ) 
        {
					ss2 >> cval;

					// Grab texture indexes
					if( ss2.peek() != '/' ) 
					{
							ss2 >> ival;
						vertex.tex0[0] = tex_coords[ (( ival - 1 )*2) ];
						vertex.tex0[1] = tex_coords[ (( ival - 1 )*2) + 1 ];
					}
		
					// Grab vertex normals indexes (may not be unit)
					else
					{
						ss2 >> cval;
						ss2 >> ival;
						vertex.normal[0] = norms[ (( ival - 1 )*3) ];
						vertex.normal[1] = norms[ (( ival - 1 )*3) + 1 ];
						vertex.normal[2] = norms[ (( ival - 1 )*3) + 2 ];
					}
				}
				polygon.add_vertex( vertex );
			} // End while
			add_poly( polygon );
		} // End face line 
	}

  in.close();
	data_is_dirty = true;
}

//-------------------------------------------------------------------
// Primitives code based off of source code from OpenGL SuperBible 5ed.
/////////////////////////////////////////////////////////////////////
void Mesh::build_cube( float r, const Color& col )
{
	// Clear mesh information if reusing this object since it will cause 
	// problems with buffer object drawing.
	if( data_is_dirty )
		reset();

	mesh_type = TRI_MESH;
	poly_mode = FILL;
	is_indexed = true;

    /////////////////////////////////////////////////////////
    // Top of cube
	Polygon polygon = Polygon();
	polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col );
	polygon.add_vertex( r,		r,		-r,		r,		0,		0.0f,	r,		0.0f, col );
	polygon.add_vertex( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	r,		0.0f, col  );
	polygon.add_vertex( -r,		r,		-r,		0,		0,		0.0f,	r,		0.0f, col  );
	polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	r,		0.0f, col  );
	add_poly( polygon );

    //////////////////////////////////////////////////////
    // Bottom of cube
	polygon = Polygon();
	polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
	polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	-r,		0.0f, col  );
	polygon.add_vertex( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( -r,		-r,		r,		0,		r,		0.0f,	-r,		0.0f, col  );
	polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	-r,		0.0f, col  );
	polygon.add_vertex( r,		-r,		r,		r,		r,		0.0f,	-r,		0.0f, col  );
	add_poly( polygon );

	//////////////////////////////////////////////////////
    // Left side of cube
	polygon = Polygon();
	polygon.add_vertex( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
	polygon.add_vertex( -r,	r,		-r,		r,		0,		-r,		0.0f,	0.0f, col  );
	polygon.add_vertex( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( -r,	r,		r,		r,		r,		-r,		0.0f,	0.0f, col  );
	polygon.add_vertex( -r,	-r,		-r,		0,		0,		-r,		0.0f,	0.0f, col  );
	polygon.add_vertex( -r,	-r,		r,		0,		r,		-r,		0.0f,	0.0f, col  );
	add_poly( polygon );

	/////////////////////////////////////////////////////
    // Right side of cube
	polygon = Polygon();
	polygon.add_vertex( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
	polygon.add_vertex( r,		r,		-r,		r,		0,		r,		0.0f,	0.0f, col  );
	polygon.add_vertex( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( r,		r,		r,		r,		r,		r,		0.0f,	0.0f, col  );
	polygon.add_vertex( r,		-r,		r,		0,		r,		r,		0.0f,	0.0f, col  );
	polygon.add_vertex( r,		-r,		-r,		0,		0,		r,		0.0f,	0.0f, col  );
	add_poly( polygon );

	//////////////////////////////////////////////////////
    // Front side of cube
	polygon = Polygon();
	polygon.add_vertex( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
	polygon.add_vertex( r,		r,		r,		r,		r,		0.0f,	0.0f,	r, col  );
	polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( -r,		r,		r,		0,		r,		0.0f,	0.0f,	r, col  );
	polygon.add_vertex( -r,		-r,		r,		0,		0,		0.0f,	0.0f,	r, col  );
	polygon.add_vertex( r,		-r,		r,		r,		0,		0.0f,	0.0f,	r, col  );
	add_poly( polygon );

	////////////////////////////////////////////////////
    // Back side of cube
	polygon = Polygon();
	polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
	polygon.add_vertex( -r,		-r,		-r,		0,		0,		0.0f,	0.0f,	-r, col  );
	polygon.add_vertex( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( -r,		r,		-r,		0,		r,		0.0f,	0.0f,	-r, col  );
	polygon.add_vertex( r,		r,		-r,		r,		r,		0.0f,	0.0f,	-r, col  );
	polygon.add_vertex( r,		-r,		-r,		r,		0,		0.0f,	0.0f,	-r, col  );
	add_poly( polygon );
	
	data_is_dirty = true;
}	

void Mesh::build_sphere( float r, int lats, int longs, const Color& col )
{
	// Clear mesh information if reusing this object since it will cause 
	// problems with buffer object drawing.
	if( data_is_dirty )
		reset();

	mesh_type = TRI_MESH;
	poly_mode = FILL;
	is_indexed = true;

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
			add_poly( polygon );

			/////////////////////////////////////////////////////////
			// Rearrange and and as next poly...
			polygon = Polygon();
			polygon.add_vertex( v1 );
			polygon.add_vertex( v3 );
			polygon.add_vertex( v2 );
			add_poly( polygon );
		}
		t -= dt;
	}
	
	data_is_dirty = true;
}

void Mesh::build_torus( float outer_radius, float inner_radius, int num_major, int num_minor, const Color& col )
{
	// Clear mesh information if reusing this object since it will cause 
	// problems with buffer object drawing.
	if( data_is_dirty )
		reset();

	mesh_type = TRI_MESH;
	poly_mode = FILL;
	is_indexed = true;

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
			add_poly( polygon );

			/////////////////////////////////////////////////////////
			// Rearrange and and as next poly...
			polygon = Polygon();
			polygon.add_vertex( v1 );
			polygon.add_vertex( v3 );
			polygon.add_vertex( v2 );
			add_poly( polygon );			
		}
	}

	data_is_dirty = true;
}

void Mesh::build_bbox( const glm::vec3& min, const glm::vec3& max, const Color& col )
{
	// Clear mesh information if reusing this object since it will cause 
	// problems with buffer object drawing.
	if( data_is_dirty )
		reset();

	mesh_type = LINE_STRIP_MESH;
	poly_mode = LINES;
	is_indexed = false;

	Polygon polygon = Polygon();
	polygon.add_vertex( min.x, min.y, min.z, col );
	polygon.add_vertex( max.x, min.y, min.z, col  );
	polygon.add_vertex( max.x, min.y, max.z, col  ); 
	polygon.add_vertex( min.x, min.y, max.z, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( min.x, min.y, min.z, col  );
	polygon.add_vertex( min.x, max.y, min.z, col  );
	polygon.add_vertex( min.x, max.y, max.z, col  );
	polygon.add_vertex( max.x, max.y, max.z, col  ); 
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( max.x, max.y, min.z, col  );
	polygon.add_vertex( min.x, max.y, min.z, col  );
	polygon.add_vertex( min.x, max.y, max.z, col  );
	polygon.add_vertex( min.x, min.y, max.z, col  );
	add_poly( polygon );

	polygon = Polygon();
	polygon.add_vertex( max.x, min.y, max.z, col  );
	polygon.add_vertex( max.x, max.y, max.z, col  );
	polygon.add_vertex( max.x, max.y, min.z, col  );
	polygon.add_vertex( max.x, min.y, min.z, col  );
	add_poly( polygon );

	data_is_dirty = true;
}


/////////////////////////////////////////////////////////////////////
const std::vector<Vertex>& Mesh::get_vertices() const
{
	return vertices;
}

const unsigned int Mesh::get_vertex_count() const
{
	return vertices.size();
}

const std::vector<unsigned short>& Mesh::get_indexes() const
{
	return indexes;
}

const unsigned int Mesh::get_index_count() const
{
	return indexes.size();
}

const unsigned int Mesh::get_poly_count() const
{
	return polys.size();
}

const unsigned int Mesh::get_max_index() const
{
	return max_index;
}

const unsigned int Mesh::get_min_index() const
{
	return min_index;
}

/////////////////////////////////////////////////////////////////////

void Mesh::set_working_dir( const std::string& directory )
{
	working_directory = directory;
}

void Mesh::reset()
{
	vertices.clear();
	polys.clear();
	indexes.clear();
}