#pragma once

class Sprite;

class Drawable final
{
public:
	// default {ctor} and {dtor}
	//
	Drawable();
	~Drawable();

	// init element
	//
	void Init();

	void PreDraw()const;
	void Draw( const Sprite& part ) const;
	void PostDraw()const ;

	// clean ogl data
	//
	void Clean();

protected:
	// dirty code but the task is to make particle system
	// 
	GLuint _uiVBO;

	// shader related
	//
	GLuint _uiProgram;
	GLuint _uiVertexShader;
	GLuint _uiPixelShader;
	GLint _uiPosLAttribute;
	GLint _uiUVAttribute;

	// work uniforms
	//
	GLint _uiColorUni;
	GLint _uiTextureSampler;
	GLint _uiTM;


	Matrix projOrtho;
};