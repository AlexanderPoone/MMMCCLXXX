#ifndef WAVPLAYER_H
#define WAVPLAYER_H

#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#include <QThread>
#include <QObject>
#include <QtDebug>

//#include <stdio.h>
//#include <iostream>
#include <windows.h>
#include <mmsystem.h>
//#include <atlbase.h>
//#include <fstream>

#define FILE_PATH "heartache.wav"
#pragma comment(lib, "winmm.lib")

class WavPlayer : public QThread
{
    Q_OBJECT
public:
    WavPlayer();
    void stop();

    //function prototype
    void GetWaveError(MMRESULT err);
    void setPath(LPTSTR path);
    void setVolume(int volume);
    static void CALLBACK WavPlayer::waveOutProc(
        HWAVEOUT hWaveOut,
        UINT uMsg,
        DWORD dwInstance,
        DWORD dwParam1,
        DWORD dwParam2
    ) {


        //if (uMsg == WOM_DONE) {
        //	LPWAVEHDR pWaveHeader = (LPWAVEHDR)dwParam1;
        //	waveOutUnprepareHeader(hAudioOut, pWaveHeader, sizeof(WAVEHDR));
        //	waveOutPrepareHeader(hAudioOut, pWaveHeader, sizeof(WAVEHDR));
        //	waveOutWrite(hAudioOut, pWaveHeader, sizeof(WAVEHDR));
        //	cout << "hi" << pWaveHeader;
        //}
        //return;
        ///*
        //* pointer to free block counter
        //*/
        //int* freeBlockCounter = (int*)dwInstance;
        ///*
        //* ignore calls that occur due to openining and closing the
        //* device.
        //*/
        //if (uMsg != WOM_DONE)
        //	return;
        //EnterCriticalSection(&waveCriticalSection);
        //(*freeBlockCounter)++;
        //LeaveCriticalSection(&waveCriticalSection);
    }
    void run() Q_DECL_OVERRIDE;
    void play();
private:
    LPTSTR path;
    HMMIO hmmioIn;
    HWAVEOUT  hAudioOut;

signals:
    void duration(int secs);
public slots:
};

#endif // WAVPLAYER_H
