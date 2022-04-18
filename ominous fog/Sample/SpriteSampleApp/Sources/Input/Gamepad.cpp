#include "stdafx.h"

#include "Gamepad.h"

#include <Windows.h>
// xinput to listen to xbox controller
#include <Xinput.h>
#pragma comment( lib, "Xinput.lib" )

using namespace Input;

namespace
{
	// actual state for gamepad
	//
	XINPUT_STATE _State[ 4 ] = { {},{},{},{} };

	// number Pi
	const float Pi = 3.1415926535897f;
	const float Pi_Inv = 1.0f / Pi;

	// constant to convert
	// angle to radian
	// radian to angle
	//
	const float kAngToRad = Pi / 180.0f;
	const float kRadToAng = Pi_Inv * 180.0f;


	// convert from radian to angle
	//
	inline float RadianToAngle( float aValue )
	{
		return aValue * kRadToAng;
	}

	// int to bool
	//
	inline bool ToBool( int value )
	{
		return ( value != 0 ) ? true : false;
	}
}

float GamepadStick::Lenght() const
{
	Vector2 fVec = this->Position();
	return fVec.Length();
}

Vector2 GamepadStick::Position() const
{
	return Vector2( static_cast< float >( this->X ) / float( 0x7FFF ), static_cast< float >( this->Y ) / float( 0x7FFF ) );
}

float GamepadStick::Angle() const
{
	Vector2 fVec = this->Position();
	return  RadianToAngle( atan2( fVec.y, fVec.x ) );
}

unsigned char GamepadData::getButton( EGamepadButton button ) const
{
	switch( button )
	{
	case EGamepadButton::A:
		return this->A;
	case EGamepadButton::B:
		return this->B;
	case EGamepadButton::X:
		return this->X;
	case EGamepadButton::Y:
		return this->Y;
	case EGamepadButton::Left:
		return this->Left;
	case EGamepadButton::Right:
		return this->Right;
	case EGamepadButton::Up:
		return this->Up;
	case EGamepadButton::Down:
		return this->Down;
	case EGamepadButton::MenuLeft:
		return this->MenuLeft;
	case EGamepadButton::MenuRight:
		return this->MenuRight;
	case EGamepadButton::L1:
		return this->L1;
	case EGamepadButton::L2:
		return this->L2;
	case EGamepadButton::L3:
		return this->L3;
	case EGamepadButton::R1:
		return this->R1;
	case EGamepadButton::R2:
		return this->R2;
	case EGamepadButton::R3:
		return this->R3;
	}
	return 0;
}

Gamepad::Gamepad()
	: _pDelegate( nullptr )
	, _bActive( false )
	, _fStickDeadZone( 0.24f )
	, _PreviousStates{}
	, _CurrentStates{}
	, _fTriggerDeadZone( 0.12f )
	, _nIndexController( -1 )
{
}

Gamepad::~Gamepad()
{
}

void Gamepad::Init( int index, float fDeadStick, float fDeadTrigger )
{
	this->_nIndexController = index;
	this->setStickDeadZone( fDeadStick );
	this->setTriggerDeadZone( fDeadTrigger );
}

void Gamepad::setStickDeadZone( float fPercent )
{
	this->_fStickDeadZone = Base::Clamp( fPercent, 0.0f, 1.0f );
}

float Gamepad::getStickDeadZone() const
{
	return this->_fStickDeadZone;
}

void Gamepad::setTriggerDeadZone( float fPercent )
{
	this->_fTriggerDeadZone = Base::Clamp( fPercent, 0.0f, 1.0f );
}

float Gamepad::getTriggerDeadZone() const
{
	return this->_fTriggerDeadZone;
}

void Gamepad::setEnabled( bool bValue )
{
	if( bValue )
	{
		// App is now active, so re-enable XInput
		XInputEnable( bValue );

	}
	else
	{
		// App is now inactive, so disable XInput to prevent
		// user input from effecting application and to 
		// disable rumble. 
		XInputEnable( bValue );
	}
}

void Gamepad::Update()
{
	if( this->_nIndexController == -1 )
	{
		return;
	}

	memset( &_State[ this->_nIndexController ], 0, sizeof( XINPUT_STATE ) );
	DWORD dwStatus = XInputGetState( this->_nIndexController, &_State[ this->_nIndexController ] );
	bool bPreviousStatus = this->_bActive;
	if( dwStatus == ERROR_SUCCESS )
	{
		this->_bActive = true;
	}
	else
	{
		this->_bActive = false;
	}

	// notify abount current status
	if( bPreviousStatus != this->_bActive && this->_pDelegate )
	{
		this->_pDelegate->onConnectChanged( this->_bActive );

		memset( &this->_CurrentStates, 0, sizeof( GamepadData ) );
		memset( &this->_PreviousStates, 0, sizeof( GamepadData ) );
	}

	if( !this->_bActive )
	{
		return;
	}

	// copy current status to prev.
	memcpy( &this->_PreviousStates, &this->_CurrentStates, sizeof( GamepadData ) );
	memset( &this->_CurrentStates, 0, sizeof( GamepadData ) );
	// gather new one
	this->_Gather();
}

bool Gamepad::isActive() const
{
	return this->_bActive;
}

bool Gamepad::isPressed( EGamepadButton button ) const
{
	return ToBool( this->_CurrentStates.getButton( button ) );;
}

bool Gamepad::isDowned( EGamepadButton button ) const
{
	return !this->_PreviousStates.getButton( button ) && this->_CurrentStates.getButton( button );
}

bool Gamepad::isReleased( EGamepadButton button ) const
{
	return this->_PreviousStates.getButton( button ) && !this->_CurrentStates.getButton( button );
}

unsigned char Gamepad::getL2() const
{
	return this->_CurrentStates.L2;
}

unsigned char Gamepad::getR2() const
{
	return this->_CurrentStates.R2;
}

const GamepadStick& Gamepad::getLStick() const
{
	return this->_CurrentStates.LStick;
}

const GamepadStick& Gamepad::getRStick() const
{
	return this->_CurrentStates.RStick;
}

const GamepadData& Gamepad::getCurrentState() const
{
	return this->_CurrentStates;
}

const GamepadData& Gamepad::getPreviousState() const
{
	return this->_PreviousStates;
}

void Input::Gamepad::setRumble( float fLeftMotor, float fRightMotor )
{
	// XInput vibration state
	XINPUT_VIBRATION rumble;

	// Zero memory on vibration state
	ZeroMemory( &rumble, sizeof( XINPUT_VIBRATION ) );

	fLeftMotor = Base::Clamp( fLeftMotor, 0.0f, 1.0f );
	fRightMotor = Base::Clamp( fRightMotor, 0.0f, 1.0f );

	// Calculate vibration intensity
	int left_motor = int( fLeftMotor * 65535.0f );
	int right_motor = int( fRightMotor * 65535.0f );

	rumble.wLeftMotorSpeed = left_motor;
	rumble.wRightMotorSpeed = right_motor;

	// Apply vibration
	XInputSetState( this->_nIndexController, &rumble );
}

void Gamepad::_Gather()
{
	WORD wButtons = _State[ this->_nIndexController ].Gamepad.wButtons;

	this->_CurrentStates.A = ToBool( wButtons & XINPUT_GAMEPAD_A );
	this->_CurrentStates.B = ToBool( wButtons & XINPUT_GAMEPAD_B );
	this->_CurrentStates.X = ToBool( wButtons & XINPUT_GAMEPAD_X );
	this->_CurrentStates.Y = ToBool( wButtons & XINPUT_GAMEPAD_Y );


	this->_CurrentStates.Left = ToBool( wButtons & XINPUT_GAMEPAD_DPAD_LEFT );
	this->_CurrentStates.Right = ToBool( wButtons & XINPUT_GAMEPAD_DPAD_RIGHT );
	this->_CurrentStates.Up = ToBool( wButtons & XINPUT_GAMEPAD_DPAD_UP );
	this->_CurrentStates.Down = ToBool( wButtons & XINPUT_GAMEPAD_DPAD_DOWN );

	this->_CurrentStates.L1 = ToBool( wButtons & XINPUT_GAMEPAD_LEFT_SHOULDER );
	this->_CurrentStates.R1 = ToBool( wButtons & XINPUT_GAMEPAD_RIGHT_SHOULDER );

	this->_CurrentStates.L3 = ToBool( wButtons & XINPUT_GAMEPAD_LEFT_THUMB );
	this->_CurrentStates.R3 = ToBool( wButtons & XINPUT_GAMEPAD_RIGHT_THUMB );

	this->_CurrentStates.MenuLeft = ToBool( wButtons & XINPUT_GAMEPAD_BACK );
	this->_CurrentStates.MenuRight = ToBool( wButtons & XINPUT_GAMEPAD_START );


	// stick deadzone
	short StickDeadZone = static_cast< short >( this->_fStickDeadZone * float( 0x7FFF ) );

	// Zero value if thumbsticks are within the dead zone 
	if( ( _State[ this->_nIndexController ].Gamepad.sThumbLX < StickDeadZone && _State[ this->_nIndexController ].Gamepad.sThumbLX > -StickDeadZone ) &&
		( _State[ this->_nIndexController ].Gamepad.sThumbLY < StickDeadZone && _State[ this->_nIndexController ].Gamepad.sThumbLY > -StickDeadZone ) )
	{
		_State[ this->_nIndexController ].Gamepad.sThumbLX = 0;
		_State[ this->_nIndexController ].Gamepad.sThumbLY = 0;
		this->_CurrentStates.LStick.isDeadZone = true;
	}

	if( ( _State[ this->_nIndexController ].Gamepad.sThumbRX < StickDeadZone && _State[ this->_nIndexController ].Gamepad.sThumbRX > -StickDeadZone ) &&
		( _State[ this->_nIndexController ].Gamepad.sThumbRY < StickDeadZone && _State[ this->_nIndexController ].Gamepad.sThumbRY > -StickDeadZone ) )
	{
		_State[ this->_nIndexController ].Gamepad.sThumbRX = 0;
		_State[ this->_nIndexController ].Gamepad.sThumbRY = 0;
		this->_CurrentStates.RStick.isDeadZone = true;
	}

	this->_CurrentStates.LStick.X = _State[ this->_nIndexController ].Gamepad.sThumbLX;
	this->_CurrentStates.LStick.Y = _State[ this->_nIndexController ].Gamepad.sThumbLY;
	this->_CurrentStates.RStick.X = _State[ this->_nIndexController ].Gamepad.sThumbRX;
	this->_CurrentStates.RStick.Y = _State[ this->_nIndexController ].Gamepad.sThumbRY;


	// l2, r2

	unsigned char DeadZoneTrigger = static_cast< unsigned char >( this->_fTriggerDeadZone * float( 0xFF ) );
	if( _State[ this->_nIndexController ].Gamepad.bLeftTrigger < DeadZoneTrigger )
	{
		_State[ this->_nIndexController ].Gamepad.bLeftTrigger = 0;
	}
	if( _State[ this->_nIndexController ].Gamepad.bRightTrigger < DeadZoneTrigger )
	{
		_State[ this->_nIndexController ].Gamepad.bRightTrigger = 0;
	}

	this->_CurrentStates.L2 = _State[ this->_nIndexController ].Gamepad.bLeftTrigger;
	this->_CurrentStates.R2 = _State[ this->_nIndexController ].Gamepad.bRightTrigger;
}


