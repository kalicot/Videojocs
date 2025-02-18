#ifndef _TEXTURED_QUAD_INCLUDE
#define _TEXTURED_QUAD_INCLUDE


#include <glm/glm.hpp>
#include "Texture.h"
#include "ShaderProgram.h"


class TexturedQuad
{

public:
	// Textured quads can only be created inside an OpenGL context
	static TexturedQuad* createTexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram* program);

	TexturedQuad(glm::vec2 geom[2], glm::vec2 texCoords[2], ShaderProgram* program);

	void render(const Texture& tex) const;
	void free();
	void setPosition(const glm::vec2& pos);


private:
	GLuint vao;
	GLuint vbo;
	GLint posLocation, texCoordLocation;
	ShaderProgram* shaderProgram;
	glm::vec2 position;

};


#endif // _TEXTURED_QUAD_INCLUDE

