#include "OBJLoader.h"
#include <fstream>
#include <sstream>
#include "Core/Debug.h"

namespace obj
{
	void import( const std::string& filename, Mesh &mesh )
	{
		// Clear mesh information if reusing this object since it will cause 
		// problems with buffer object drawing.
		if( !mesh.vertexCount() )
			mesh.reset();

		std::ifstream in( filename.c_str() );

		if( !in.is_open() )
		{
			debug() << "load_obj: Failed to open obj model file with name " << filename << std::endl;
			return;
		}

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
				Polygon polygon;

				while( ss >> face_tok ) 
				{
					Vertex vertex;

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
					polygon.add( vertex );

				} // End while face token
				mesh.add( polygon );

			} // End face line 
		} // End while getline

		in.close();
	}
};