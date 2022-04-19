#pragma once

// current code doesn't support more than one gamepad

namespace Input
{

	class IGamepadDelegate
	{
	public:
		virtual ~IGamepadDelegate()
		{
		}
		virtual void onConnectChanged( bool bActualStatus ) = 0;
	};


	struct GamepadStick
	{
		short X;
		short Y;

		bool isDeadZone;



		float Lenght()const;
		Vector2 Position()const;
		float Angle()const;
	};

	enum class EGamepadButton : int
	{
		A = 0,
		B,
		X,
		Y,

		PS4_Cross = A,
		PS4_Circlt = B,
		PS4_Square = Y,
		PS4_Triangle = X,

		Left = 4,
		Right,
		Up,
		Down,

		MenuLeft,
		MenuRight,

		PS4_Share = MenuLeft,
		PS4_Option = MenuRight,

		L1 = 10,
		L2,
		L3,
		R1,
		R2,
		R3,
	};

	struct GamepadData
	{
		bool A;// PS - X
		bool B;// PS - circle
		bool X;// PS - square
		bool Y;// PS - triangle

		bool Left;
		bool Right;
		bool Up;
		bool Down;

		// 
		bool MenuLeft;	// PS - Share, Xbox - back
		bool MenuRight;	// PS - Option, Xbox - start

		bool L1;
		bool R1;

		bool L3;
		bool R3;

		// trigger value
		//
		unsigned char L2;
		unsigned char R2;

		// thumbs
		GamepadStick LStick;
		GamepadStick RStick;

		// getter value for button
		//
		unsigned char getButton( EGamepadButton button )const;
	};





	class Gamepad
	{
	public:
		// default {ctor} and {ctor}
		//
		
		Gamepad();
		virtual ~Gamepad();

		// setter / getter index controller
		//
		void Init( int index, float fDeadStick = 0.24f, float fDeadTrigger = 0.12f );

		// setter / getter dead zone for sticks
		//
		void setStickDeadZone( float fPercent );
		float getStickDeadZone()const;

		// setter / getter dead zone for trigger
		//
		void setTriggerDeadZone( float fPercent );
		float getTriggerDeadZone()const;

		// setter active status 
		//
		void setEnabled( bool bValue );

		// update connecion
		//
		void Update();

		// is active
		//
		bool isActive()const;

		// is pressed button
		//
		bool isPressed( EGamepadButton button )const;

		// is downed button
		//
		bool isDowned( EGamepadButton button )const;

		// is released button
		//
		bool isReleased( EGamepadButton button )const;

		// getter trigger values
		//
		unsigned char getL2()const;
		unsigned char getR2()const;

		// getter sticks 
		//
		const GamepadStick& getLStick()const;
		const GamepadStick& getRStick()const;

		// getter full info 
		//
		const GamepadData& getCurrentState()const;
		const GamepadData& getPreviousState()const;

		// setting vibro
		//
		void setRumble( float fLeftMotor, float fRightMotor );
	protected:
		// gather state from controller
		//
		void _Gather();
	protected:
		// actual index
		//
		int _nIndexController;

		// is active gamepad
		//
		bool _bActive;

		// actions from gamepad
		//
		IGamepadDelegate* _pDelegate;

		// dead zone percent for thumbs
		// Default to 24 % of the + / -32767 range.This is a reasonable default value but can be altered if needed.
		//
		float _fStickDeadZone;

		// setter dead zone for triggers
		// 12% is default value
		//
		float _fTriggerDeadZone;

		// previous and current button states
		//
		GamepadData _PreviousStates;
		GamepadData _CurrentStates;
	};
}