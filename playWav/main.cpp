/*--------------------------------------------------------------------------------
*Unfinished
*Need to work on: 1.Prepare buffer, 2. Read Buffer, 3. Play buffer data
*Other codes should be no error.
---------------------------------------------------------------------------------*/



#include <stdio.h>
#include <iostream>
#include <windows.h>
#include <mmsystem.h>
#include <atlbase.h>
#include <fstream>
using namespace std;

#define FILE_PATH "./res/audio/heartache.wav"
#pragma comment( lib, "winmm" )

void GetWaveError(MMRESULT err) {
	char errorMsg[256];
	if (err) {
		waveOutGetErrorText(err, (LPWSTR)errorMsg, sizeof(errorMsg));
		cerr << "Error in WaveOutOpen:" << errorMsg << endl;
		return;
	}
}

int main(int argc, char** argv) {
	USES_CONVERSION;

	//MMIOINFO AudioData;
	HMMIO hmmioIn;
	MMCKINFO parentChunk;
	MMCKINFO formatChunk;
	MMCKINFO dataChunk;
	HWAVEOUT hAudioOut;
	WAVEHDR databuffer[1000];
	int BUFFER_SIZE = 500;
	int size = 123;

	int waveformatSize = 36-12;

	//path of Wav file for testing
	LPSTR path = FILE_PATH;
	LPWSTR filename = A2W(path);


	/*--------------------------------------------------------------------------------
	*codes reserved for calling file from console
	---------------------------------------------------------------------------------*/
	//wchar_t wtext[20];
	//mbstowcs(wtext, argv[1], strlen(argv[1]) + 1);
	//LPWSTR filename = wtext;
	

	/*--------------------------------------------------------------------------------
	*HMMIO mmioOpen(LPSTR filename, LPMMIOINFO info, DWORD flags);
	*Open the a wav file.
	---------------------------------------------------------------------------------*/
	if ((hmmioIn = mmioOpen(filename, NULL, MMIO_READ)) == NULL) {
		cerr<<"Error: mmioOPen error";
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
	*Go into RIFF chunk;
	*The file is wave format
	---------------------------------------------------------------------------------*/
	parentChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
	if (mmioDescend(hmmioIn, &parentChunk, NULL, MMIO_FINDRIFF)) {
		cerr <<"Error: could not find WAVE chunk or";
		cerr << "the file is not in RIFF\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
	*Go into fmt chunk;
	---------------------------------------------------------------------------------*/
	formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
	if (mmioDescend(hmmioIn, &formatChunk, &parentChunk, MMIO_FINDCHUNK)){
		cerr <<"Could not find FMT chunk.\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*LONG mmioRead(HMMIO h, HPSTR pch, LONG cch);
	*reads a specified number of bytes from a file;
	---------------------------------------------------------------------------------*/
	char * fmtData = new char[formatChunk.cksize];
	if (!mmioRead(hmmioIn, fmtData, formatChunk.cksize)) {
		cerr<< "Error in reading the waveformat\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}
	/*--------------------------------------------------------------------------------
	*mmioAscend(HMMIO h, LPMMCKINFO lpck, UINT flags);
	*ascend chunk
	---------------------------------------------------------------------------------*/
	if (mmioAscend(hmmioIn, &formatChunk, 0)) {
		cerr<<"Error in mmioAscend\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
	*Go into data chunk;
	---------------------------------------------------------------------------------*/
	dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
	if (mmioDescend(hmmioIn, &dataChunk, &parentChunk, MMIO_FINDCHUNK)) {
		cerr << "Could not find data chunk.\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID, LPWAVEFORMATEX pwfx,
	DWORD dwCallback, DWORD Instance, DWORD fdwOpen);
	*Create a wave device.
	*handle
	---------------------------------------------------------------------------------*/
	MMRESULT err = waveOutOpen(&hAudioOut, WAVE_MAPPER, (WAVEFORMATEX *)&fmtData,
		(DWORD)hmmioIn, 0, CALLBACK_FUNCTION);
	GetWaveError(err);

	/*--------------------------------------------------------------------------------
	*waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
	*Prepare buffer...
	***To be done
	---------------------------------------------------------------------------------*/
	for (int i = 0; i < size; i++) {
		databuffer[i].lpData = new char[BUFFER_SIZE];;
		databuffer[i].dwBufferLength = BUFFER_SIZE;
		//databuffer[i].dwflags = 0;
		memset(databuffer[i].lpData, 0, BUFFER_SIZE);
		err = waveOutPrepareHeader(hAudioOut, &databuffer[i], sizeof(WAVEHDR));
	}

	/*--------------------------------------------------------------------------------
	*Read dataChunk into buffer...
	***To be done
	---------------------------------------------------------------------------------*/
	DWORD dataChunksize = dataChunk.cksize;
	char * dataData = new char[dataChunksize];
	if (!mmioRead(hmmioIn, dataData, dataChunksize)) {
		cerr << "Error in reading the waveformat\n";
		mmioClose(hmmioIn, 0);
		exit(-1);
	}

	/*--------------------------------------------------------------------------------
	*waveOutWrite (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh );
	*Play back buffer data
	***To be done...
	---------------------------------------------------------------------------------*/
	waveOutWrite(hAudioOut, &databuffer[0], sizeof(WAVEHDR));

	/*--------------------------------------------------------------------------------
	*mmioClose(HMMIO h, UINT wflags);
	*Close Wav file
	---------------------------------------------------------------------------------*/
	mmioClose(hmmioIn, 0);

	/*--------------------------------------------------------------------------------
	*waveOutClose(HWAVEOUT hwo);
	*Close audio device
	---------------------------------------------------------------------------------*/
	waveOutClose(hAudioOut);

	cout << "cat";

	return 0;
}






/*
//useless, please ignore
char w, h;
FILE *fin = fopen(FILE_PATH, "r");
fscanf(fin, "%c %c", &w, &h);
cout << w << h;
fclose(fin);
*/