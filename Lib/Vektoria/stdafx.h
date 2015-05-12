#define NULL 0
#define WIN32_LEAN_AND_MEAN

// windows only
//#define _CRT_SECURE_NO_WARNINGS
#include <winsock2.h>
#include <windows.h>

// directinput
#define DIRECTINPUT_VERSION 0x0800
#include "dinput.h"

//winsock2 library
#pragma comment(lib, "ws2_32.lib")

#include <string.h>
#include <iostream>
#include <math.h>
#include <time.h>


//using namespace std;

// memory leak check
// #define _CRTDBG_MAP_ALLOC
// #include <stdlib.h>
// #include <crtdbg.h>
