#pragma once

class Globals
{
public:
	static const int screenWidth = 1920;
	static const int screenHeight = 1080;
	static const int maxLightsCount = 8;

	// const value of size of one particle
	//
	static const float ParticleSize;


	static std::unordered_map< std::string, GLuint > Texures;
};


enum EActionCamera
{
	EActionCamera_None = 0,
	EActionCamera_WalkForward = 1 << 1,
	EActionCamera_Walkbackward = 1 << 2,
	EActionCamera_WalkLeft = 1 << 3,
	EActionCamera_WalkRight = 1 << 4,
	EActionCamera_FlyUp = 1 << 5,
	EActionCamera_FlyDown = 1 << 6,
	EActionCamera_PitchUp = 1 << 7,
	EActionCamera_PitchDown = 1 << 8,
	EActionCamera_YawLeft = 1 << 9,
	EActionCamera_YawRight = 1 << 10,
	EActionCamera_RollRight = 1 << 11,
	EActionCamera_RollLeft = 1 << 12
};
// overloaded operators for using action camera more friendly
static EActionCamera & operator|=( EActionCamera &x, const EActionCamera y )
{
	x = ( EActionCamera )( ( int )x | ( int )y ); return x;
}
static EActionCamera operator|( const EActionCamera x, const EActionCamera y )
{
	return ( EActionCamera )( ( int )x | ( int )y );
}
static EActionCamera & operator&=( EActionCamera &x, const EActionCamera y )
{
	x = ( EActionCamera )( ( int )x & ( int )y ); return x;
}
static EActionCamera operator&( const EActionCamera x, const EActionCamera y )
{
	return ( EActionCamera )( ( int )x & ( int )y );
}
static EActionCamera& operator^=( EActionCamera &x, const EActionCamera y )
{
	x = ( EActionCamera )( ( int )x ^ ( int )y ); return x;
}
static EActionCamera operator^( const EActionCamera x, const EActionCamera y )
{
	return ( EActionCamera )( ( int )x ^ ( int )y );
}
