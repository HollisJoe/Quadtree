#include "geometry.h"
#include "scene.h"
#include "polygon.h"

// The scene state is global
extern Scene scene;

/**
 * Construct a Geometry and initialize its OpenGL State: VAO and VBOs.
 */
Geometry::Geometry(int id, const vector<vec2>& vertices,
                   const vector<int>& edges) :
  _id(id)
{
  // Dynamically make a copy of vertices, edges, and bb
  _vertices = new vector<vec2>(vertices);
  _edges = new vector<int>(edges);
  _bb = new BB(vertices); // TODO: Initialize the BB correctly

  // Create VAO to manage Vertex and Color VBOs
  // Find unused VAO ID
  glGenVertexArrays(1, &_vao);
  // Make the VAO object current
  glBindVertexArray(_vao);

  // Find unused VBO ID for Vertex Position Buffer
	glGenBuffers(1, &_vbo);
  // Create buffer object of vertex attribute data
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  // Allocate memory on the GPU and transfer the app data to it
  glBufferData(
    GL_ARRAY_BUFFER,
    _vertices->size() * sizeof(vec2),
    _vertices->data(),
    GL_STATIC_DRAW
  );
  // Look up where on the GPU we can access our vertex position attribute buffer
	_vert_pos_loc = glGetAttribLocation(scene._prog_ID, "vertex_pos");
	glEnableVertexAttribArray(_vert_pos_loc); // TODO: Find out if you need to enable and disable for each call to scene.drawGeometry(g)

  // Bind our vertex VBO to current VAO
	glBindBuffer(GL_ARRAY_BUFFER, _vbo);
  glVertexAttribPointer(
    _vert_pos_loc,  // The attribute we want to configure
    2,              // Number of elems per vertex for this attribute
    GL_FLOAT,       // type
    GL_FALSE,       // normalized?
    0,              // stride
    (void*)0        // array buffer offset
  );
}

/**
 * Destroy this Geometry object and clean up its OpenGL state.
 */
Geometry::~Geometry()
{
  // Delete dynamic data from heap
  delete _vertices;
  delete _edges;
  delete _bb;
  _vertices = NULL;
  _edges = NULL;
  _bb = NULL;

  // TODO: Find out if we need to delete the VAO on the GPU
	glDisableVertexAttribArray(_vert_pos_loc);
	glDeleteBuffers(1, &_vbo);
  printf("Geometry DESTROYED!\n");
}

/**
 * Return the area of this geometry
 */
float Geometry::area() const
{
  // TODO: Consider just making the vertices member of a Geometry object a Polygon
  Polygon geom_poly(*_vertices);
  return geom_poly.area();
}
