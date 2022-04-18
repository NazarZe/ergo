#include "stdafx.h"


#include "Sprite.h"

Sprite::Sprite()
	: _Position( 0.0f, 0.0f )
	, _ColorTint( 1.0f, 1.0f, 1.0f, 1.0f )
	, _fRotation( 0.0f )
	, _Scale( 1.0f, 1.0f )
	, _TextureIndex( -1 )
	, _fDepth( 0.0f )
{
	this->_TM.SetIdentity();
	this->_parentTM.SetIdentity();
}

void Sprite::setParentTM( const Matrix& matTM )
{
	this->_parentTM = matTM;
}

const Matrix& Sprite::getParentTM() const
{
	return this->_parentTM;
}

void Sprite::setRotation( float fAngle )
{
	this->_fRotation = fAngle;
}

float Sprite::getRotation() const
{
	return this->_fRotation;
}

void Sprite::setPosition( const Vector2& pos )
{
	this->_Position = pos;
}

const Vector2& Sprite::getPosition() const
{
	return this->_Position;
}

void Sprite::setScale( const Vector2& scale )
{
	this->_Scale = scale;
}

const Vector2& Sprite::getScale() const
{
	return this->_Scale;
}

void Sprite::setTexture( int texID )
{
	this->_TextureIndex = texID;
}

int Sprite::getTexture() const
{
	return this->_TextureIndex;
}

void Sprite::setTint( const Vector4& color )
{
	this->_ColorTint = color;
}

const Vector4& Sprite::getTint() const
{
	return this->_ColorTint;
}

void Sprite::setDepth( float value )
{
	this->_fDepth = value;
}

float Sprite::getDepth() const
{
	return this->_fDepth;
}

const Matrix& Sprite::getObjectTM() const
{
	return this->_TM;
}

void Sprite::MakeObjectTM()
{
	// calculate result of TM
	Matrix scale;
	scale.SetScale( this->_Scale.x, this->_Scale.y, 1.0f );

	Matrix rot;
	rot.SetRotationZ( this->_fRotation * 3.14f / 180.0f );


	Matrix pos;
	pos.SetTranslation( this->_Position.x, -this->_Position.y, this->_fDepth );

	this->_TM = ( scale * rot * pos ) * this->_parentTM;
}

