#pragma once


class Sprite
{
public:
	// default {ctor} and {dtor}
	//
	Sprite();
	virtual ~Sprite() = default;

	// setter / getter parent transform
	//
	void setParentTM( const Matrix& matTM );
	const Matrix& getParentTM()const;

	// setter / getter rotation
	//
	void setRotation( float fAngle );
	float getRotation()const;

	// setter / getter position
	//
	void setPosition( const Vector2& pos );
	const Vector2& getPosition()const;

	// setter / getter scale
	//
	void setScale( const Vector2& scale );
	const Vector2& getScale()const;

	// setter / getter active texture
	//
	void setTexture( int texID );
	int getTexture()const;

	// setter/ getter tint color
	//
	void setTint( const Vector4& color );
	const Vector4& getTint()const;

	// setter/ getter depth
	//
	void setDepth( float value );
	float getDepth()const;

	// getter object TM
	//
	const Matrix& getObjectTM()const;

	// updating object transform
	//
	void MakeObjectTM( );

protected:
	// base TM of create time
	//
	Matrix _parentTM;

	// Postion
	//
	Vector2 _Position;

	// color value
	//
	Vector4 _ColorTint;

	// rotation value( due to 2D - only one axis )
	//
	float _fRotation;

	// scale value
	//
	Vector2 _Scale;

	// index texture in the system
	// should not be assigned manually
	//
	int _TextureIndex;

	// result matrix after all transformations
	//
	Matrix _TM;

	// 
	//
	float _fDepth;
};