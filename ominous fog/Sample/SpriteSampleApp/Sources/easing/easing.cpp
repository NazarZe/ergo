#include "stdafx.h"

#include "easing.h"


Vector4 easing::lerp( const Vector4 & v1, const Vector4 & v2, float alpha )
{
	Vector4 result;

	result.x = Base::Lerp( v1.x, v2.x, ( GLfloat )alpha );
	result.y = Base::Lerp( v1.y, v2.y, ( GLfloat )alpha );
	result.z = Base::Lerp( v1.z, v2.z, ( GLfloat )alpha );
	result.w = Base::Lerp( v1.w, v2.w, ( GLfloat )alpha );

	return result;
}

Vector3 easing::lerp( const Vector3 & v1, const Vector3 & v2, float alpha )
{
	Vector3 result;

	result.x = Base::Lerp( v1.x, v2.x, (GLfloat)alpha );
	result.y = Base::Lerp( v1.y, v2.y, (GLfloat)alpha );
	result.z = Base::Lerp( v1.z, v2.z, (GLfloat)alpha );

	return result;
}

Vector2 easing::lerp( const Vector2 & v1, const Vector2 & v2, float alpha )
{
	Vector2 result;

	result.x = Base::Lerp( v1.x, v2.x, (GLfloat)alpha );
	result.y = Base::Lerp( v1.y, v2.y, (GLfloat)alpha );

	return result;
}
