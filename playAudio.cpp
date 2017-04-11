#include <stdio.h>
#include <iostream>
#include <string>
#include "irrKlang64/irrKlang.h"
using namespace std;
using namespace irrklang;

#define FILE_PATH "./res/audio/SupperMoment.mp3"
#pragma comment( lib, "winmm" )
#pragma comment(lib, "irrKlang.lib")



int main(int argc, char** argv) {
	/*--------------------------------------------------------------------------------
	*codes reserved for calling file from console
	---------------------------------------------------------------------------------*/
	//wchar_t wtext[20];
	//mbstowcs(wtext, argv[1], strlen(argv[1]) + 1);
	//LPWSTR filename = wtext;

	/*--------------------------------------------------------------------------------
	*Initiate IrrKlang engine
	---------------------------------------------------------------------------------*/
	char q = 0;
	ISoundEngine* engine = createIrrKlangDevice();

	if (!engine) {
		cout << "Cannot open engine";
		return 0;
	}
	/*--------------------------------------------------------------------------------
	*play music, support:
	RIFF WAVE (*.wav)
	Ogg Vorbis (*.ogg)
	MPEG-1 Audio Layer 3 (*.mp3)[2]
	Free Lossless Audio Codec (*.flac)
	Amiga Modules (*.mod)
	Impulse Tracker (*.it)
	Scream Tracker 3 (*.s3d)
	Fast Tracker 2 (*.xm)
	---------------------------------------------------------------------------------*/
	//false for no loop
	engine->play2D(FILE_PATH, false);
	while (q != 'q')
	{
		cout << "press 'q' to quit.\n";
		cin >> q; 
	}

	/*--------------------------------------------------------------------------------
	*Close IrrKlang engine
	---------------------------------------------------------------------------------*/
	engine->drop();


	return 0;
}
