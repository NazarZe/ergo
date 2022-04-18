// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#ifdef WIN32
#pragma warning( disable: 4996)
#endif
// system default
#include <conio.h>
#include <stdio.h>
#include <tchar.h>

// stl
#include <iostream>
#include <list>
#include <vector>
#include <string>
#include <functional>
#include <memory>
#include <unordered_map>
#include <map>

// ogl libs
#pragma comment( lib, "libEGL.lib")
#pragma comment( lib, "libGLESv2.lib" )


// external 
#include <Utilities/utilities.h>
#pragma comment( lib, "Utilities.lib" )

//#include "../Utilities/utilities.h" // if you use STL, please include this line AFTER all other include


// common 
#include "Common\Globals.h"
#include "Common\Vertex.h"
#include "Common\Base_Funcs.h"
#include "easing\easing.h"

