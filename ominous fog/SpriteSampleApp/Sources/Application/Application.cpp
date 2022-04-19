#include "stdafx.h"
#include "Input/Gamepad.h"
#include "Application.h"


namespace
{
	// static pointer for class application to get rid of complexity
	static Application* kpApp = nullptr;
}
//fwd
LRESULT WINAPI ESWindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam );

Application::Application()
	: eglContext( nullptr )
	, eglDisplay( nullptr )
	, eglSurface( nullptr )
{
	kpApp = this;
}

Application::~Application()
{
}
float bez(float x, float y, float t) {





	return 0;

}
void Application::Init()
{
	// initing window and open gl
	this->_MakeWindow( "Simple Sample", Globals::screenWidth, Globals::screenHeight );
	this->_InitOGL();


	this->_drawable.Init();
	
	
	
	this->_background.setTexture( Globals::Texures[ "grass.tga" ] );
	this->_background.setDepth( 0.0f );
	this->_background.setScale( { 60.0f, 60.0f } );
	this->_background.setPosition({ 0.0f, 0.0f });
	this->_background.MakeObjectTM();

	this->_star.setTexture(Globals::Texures[ "star.tga" ]);
	this->_star.setDepth( 1.0f );
	this->_star.setScale( { 5.0f, 5.0f } );
	this->_star.setPosition( { 100.0f, 100.0f } );
	this->_star.MakeObjectTM();

	this->_hero.setTexture( Globals::Texures[ "hero.tga" ] );
	this->_hero.setDepth( 3.0f );
	this->_hero.setScale( { 5.0f, 5.0f } );
	this->_hero.setPosition( { 0.0f, 0.0f } );
	this->_hero.setRotation( 180 );
	this->_hero.MakeObjectTM();

	this->_smoke.setTexture(Globals::Texures[ "smoke.tga" ]);
	this->_smoke.setDepth(3.0f);
	this->_smoke.setScale({ 5.0f, 5.0f });
	this->_smoke.setPosition({ 250.0f, 250.0f });
	this->_smoke.setRotation(180);
	this->_smoke.MakeObjectTM();

	this->gp.Init( 0 );
	this->gp.setEnabled(true);

}

void Application::Mouse( float x, float y )
{
}

void Application::Key( unsigned char key, bool bIsPressed )
{
}

void Application::Update(float deltaTime)
{

	this->gp.Update();



	if (this->gp.getRStick().Lenght())
	{

		float circle = this->gp.getRStick().Angle();
		this->_hero.setRotation(circle + 90);
		this->_hero.MakeObjectTM();
		Vector2 new_pos = { 10.0f, 10.0f };

		new_pos.x = new_pos.x * (circle / 360);
		new_pos.y = new_pos.y * (circle / 360);;
		this->_star.setRotation(circle + 90);
		this->_star.MakeObjectTM();

	}

	if (this->gp.getLStick().Lenght())
	{
		float fspeed = 4.0f;
		const Vector2& pos = this->_hero.getPosition();
		const Vector2& stickDiff = this->gp.getLStick().Position();
		Vector2 new_pos = pos;

		new_pos.x += stickDiff.x * fspeed;
		new_pos.y += -stickDiff.y * fspeed;

		this->_hero.setPosition(new_pos);
		this->_hero.MakeObjectTM();
	}


	if (this->gp.isReleased(Input::EGamepadButton::B))
	{
		const Vector2& pos = this->_hero.getPosition();
		Vector2 new_pos = pos;

		static float fTime = 0.0f;
		fTime += deltaTime;
		while (fTime > 1.0f)
		{
			fTime--;

		}

		this->_sprite.setTexture(Globals::Texures["fire.tga"]);
		this->_sprite.setDepth(2.0f);
		this->_sprite.setScale({ 5.0f, 5.0f });
		this->_sprite.setPosition(new_pos);
		this->_sprite.setRotation(360* fTime);
		this->_sprite.MakeObjectTM();

	}
	if (this->gp.isReleased(Input::EGamepadButton::A))
	{
		exit(0);

	}
	//////////////////////////////////////////////////////////
	if (this->gp.getRStick().Lenght())
	{
		float fTime2 = 10000.0f;
		float fTime = 0.0f;
		while (fTime < 1.0f)
		{
			fTime += 0.01f;
			Vector2 p1 = this->_hero.getPosition();
			Vector2 p2 = this->_smoke.getPosition();

			Vector2 new_pos = p2;

			new_pos.x += ((p1.x - p2.x) / fTime2) * fTime;
			new_pos.y += ((p1.y - p2.y) / fTime2) * fTime;

			this->_smoke.setPosition(new_pos);
			this->_smoke.MakeObjectTM();


		}

	}
	

	/* {
		static float fTime = 0.0f;
		fTime += deltaTime;
		while (fTime > 1.0f)
		{
			fTime--;

		}

		
		// just a sample, do not try to use it anywhere
		/* simplest easing anim in range  [1..5] -> [5..1] by one 
		
		//float fScale = 1.0f + sinf( fTime * 3.14f ) * 16.0f;
		float fRotation = fTime * 360;
		//this->_sprite.setScale( { fScale, fScale } ); 
		this->_sprite.setRotation( fRotation );
		this->_sprite.MakeObjectTM(); 
	}*/
}

void Application::Draw()
{
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	// allow alpha blending
	
	glEnable( GL_BLEND );
	glBlendFunc( GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA );

	glEnable( GL_DEPTH_TEST );

	// setup assembly
	this->_drawable.PreDraw();

	// open GL does NOT allow to draw in threads, so all this task should be in main thread
	// poor OpenGL.....

	this->_drawable.Draw( this->_background );
	this->_drawable.Draw( this->_sprite );
	this->_drawable.Draw( this->_hero );
	this->_drawable.Draw( this->_star);
	this->_drawable.Draw(this->_smoke);
	
	

	// clean up binding
	this->_drawable.PostDraw();
}

void Application::clean()
{
}

void Application::_MakeWindow( const std::string& sTitle, unsigned int uiWidth, unsigned int uiHeight )
{
	WNDCLASS wndclass = { 0 };
	DWORD    wStyle = 0;
	RECT     windowRect;
	HINSTANCE hInstance = GetModuleHandle( NULL );


	wndclass.style = CS_CLASSDC;
	wndclass.lpfnWndProc = ( WNDPROC )ESWindowProc;
	wndclass.hInstance = hInstance;
	wndclass.hbrBackground = ( HBRUSH )GetStockObject( BLACK_BRUSH );
	wndclass.lpszClassName = "ogl";

	if( !RegisterClass( &wndclass ) )
	{
		//   return FALSE;
	}

	wStyle = WS_OVERLAPPEDWINDOW;// WS_VISIBLE | WS_POPUP | WS_BORDER | WS_SYSMENU | WS_CAPTION;

								 // Adjust the window rectangle so that the client area has
								 // the correct number of pixels
	windowRect.left = 0;
	windowRect.top = 0;
	windowRect.right = uiWidth;
	windowRect.bottom = uiHeight;

	AdjustWindowRect( &windowRect, wStyle, FALSE );

	this->_hwnd = CreateWindowA(
		"ogl",
		sTitle.c_str(),
		wStyle,
		0,
		0,
		windowRect.right - windowRect.left,
		windowRect.bottom - windowRect.top,
		NULL,
		NULL,
		hInstance,
		nullptr );


	ShowWindow( this->_hwnd, TRUE );
	UpdateWindow( this->_hwnd );
}

LRESULT Application::WindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	switch( uMsg )
	{
	case WM_PAINT:
	{
		if( this->eglContext )
		{
			eglMakeCurrent( this->eglDisplay, this->eglSurface, this->eglSurface, this->eglContext );

			this->Draw();

			// present backbuffer
			SwapBuffers( GetDC( this->_hwnd ) );
		}
	}
	break;

	case WM_DESTROY:
		PostQuitMessage( 0 );
		break;

	case WM_MOUSEMOVE:
	{
		float x = ( float )( LOWORD( lParam ) );
		float y = ( float )( HIWORD( lParam ) );

		this->Mouse( x, y );

	}
	break;

	case WM_KEYDOWN:
	case WM_KEYUP:
	{
		this->Key( ( unsigned char )wParam, uMsg == WM_KEYDOWN );
	}
	break;

	}

	return -1;
}

void Application::_InitOGL()
{
	GLuint flags = ES_WINDOW_RGB | ES_WINDOW_DEPTH;

	EGLint attribList[] =
	{
		EGL_RED_SIZE, 5,
		EGL_GREEN_SIZE, 6,
		EGL_BLUE_SIZE, 5,
		EGL_ALPHA_SIZE, ( flags & ES_WINDOW_ALPHA ) ? 8 : EGL_DONT_CARE,
		EGL_DEPTH_SIZE, ( flags & ES_WINDOW_DEPTH ) ? 24 : EGL_DONT_CARE,
		EGL_STENCIL_SIZE, ( flags & ES_WINDOW_STENCIL ) ? 8 : EGL_DONT_CARE,
		EGL_SAMPLE_BUFFERS, ( flags & ES_WINDOW_MULTISAMPLE ) ? 1 : 0,
		EGL_NONE
	};



	EGLint numConfigs;
	EGLint majorVersion;
	EGLint minorVersion;
	EGLConfig config;
	EGLint contextAttribs[] = { EGL_CONTEXT_CLIENT_VERSION, 2, EGL_NONE, EGL_NONE };

	// Get Display
	this->eglDisplay = eglGetDisplay( GetDC( this->_hwnd ) );


	if( this->eglDisplay == EGL_NO_DISPLAY )
	{
		return;
	}


	// Initialize EGL
	if( !eglInitialize( this->eglDisplay, &majorVersion, &minorVersion ) )
	{
		return;
	}

	// Get configs
	if( !eglGetConfigs( this->eglDisplay, NULL, 0, &numConfigs ) )
	{
		return;
	}

	// Choose config
	if( !eglChooseConfig( this->eglDisplay, attribList, &config, 1, &numConfigs ) )
	{
		return;
	}



	// Create a surface
	this->eglSurface = eglCreateWindowSurface( this->eglDisplay, config, this->_hwnd, NULL );
	if( this->eglSurface == EGL_NO_SURFACE )
	{
		return;
	}


	// try to share context
	EGLContext contextother = eglGetCurrentContext();

	// Create a GL context
	this->eglContext = eglCreateContext( this->eglDisplay, config, contextother, contextAttribs );
	if( this->eglContext == EGL_NO_CONTEXT )
	{
		return;
	}

	// Make the context current
	if( !eglMakeCurrent( this->eglDisplay, this->eglSurface, this->eglSurface, this->eglContext ) )
	{
		return;
	}
}

void Application::EntryPoint()
{
	MSG msg = { 0 };
	DWORD lastTime = GetTickCount();

	while( true )
	{
		int gotMsg = ( PeekMessage( &msg, NULL, 0, 0, PM_REMOVE ) != 0 );
		DWORD curTime = GetTickCount();
		float deltaTime = ( float )( curTime - lastTime ) / 1000.0f;
		lastTime = curTime;

		if( deltaTime > ( 1.0f / 30.0f ) )
		{
			// avoid debug values
			deltaTime = 1.0f / 30.0f;
		}

		if( gotMsg )
		{
			if( msg.message == WM_QUIT )
			{
				break;
			}
			else
			{
				TranslateMessage( &msg );
				DispatchMessage( &msg );
			}
		}
		else
		{
			SendMessage( this->_hwnd, WM_PAINT, 0, 0 );
		}

		// Call update function if registered
		this->Update( deltaTime );
	}
}

LRESULT WINAPI ESWindowProc( HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam )
{
	LRESULT lr = -1;
	if( kpApp )
	{
		lr = kpApp->WindowProc( hWnd, uMsg, wParam, lParam );
	}

	if( lr == -1 )
	{
		return DefWindowProc( hWnd, uMsg, wParam, lParam );
	}

	// return value from app
	return lr;
}