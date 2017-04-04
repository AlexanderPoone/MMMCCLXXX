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
    QThread thread;
public:
    WavPlayer();
    void stop();
    void pause();
    void resume();

    //function prototype
    void GetWaveError(MMRESULT err);
    void setPath(QString path);
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
    HMMIO hmmioIn;
    HWAVEOUT  hAudioOut;
    std::vector<WAVEHDR> databuffer;
    MMRESULT err;
private:
    int full=0;
    void play();
    QString a;
    LPTSTR path;

    int bufferSize;
    void subThread(int bufferLoop);
    void subThread2(int bufferLoop);
    int counter;

signals:
    void duration(int secs);
public slots:
};

class SubThread : public QThread
{
    Q_OBJECT
public:
    void run() Q_DECL_OVERRIDE;
};

#endif // WAVPLAYER_H
