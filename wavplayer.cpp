#include "wavplayer.h"
#include <QFuture>
#include <QtConcurrent>
int bufferLoop;
QMutex mut;

WavPlayer::WavPlayer() {
}

void WavPlayer::GetWaveError(MMRESULT err) {
    char errorMsg[256];
    if (err == 0) {
        return;
    }else{
        waveOutGetErrorText(err, (LPTSTR)errorMsg, sizeof(errorMsg));
        qDebug() << "Error in WaveOutOpen:" << errorMsg << endl;
        return;
    }
}

void WavPlayer::setPath(QString path) {
    a=QString(path);
    this->path=(LPTSTR)a.utf16();
//    this->path=path;
}

void WavPlayer::setVolume(int volume) {
    //    waveOutSetVolume(HWAVEOUT hwo, DWORD dwVolume);
    int a=qRound(volume*2.55);
    DWORD vol= (a << 8) + a;
    waveOutSetVolume(hAudioOut, vol);
}

void WavPlayer::run() {
    play();
}

void WavPlayer::play() {
    full=1;
//    USES_CONVERSION;
    CONST int BUFFER_QUANTITY = 5;


    //MMIOINFO AudioData;
    MMCKINFO parentChunk;
    MMCKINFO formatChunk;
    MMCKINFO dataChunk;
    MMCKINFO infoChunk;
    WAVEFORMATEX fmtData;
databuffer.reserve(BUFFER_QUANTITY);
for (int i=0;i<BUFFER_QUANTITY; i++) {
 WAVEHDR tmp;
databuffer.push_back(tmp);
}
    //path of Wav file for testing
//    LPTSTR path;
//    locationPath.toWCharArray(path);
//    LPTSTR path=(LPTSTR) TEXT("C:\\Users\\Alexandre Poon\\Documents\\sans_titre\\numb.wav");

//    qDebug() << path;
//    LPTSTR path = (LPTSTR)FILE_PATH;
//    LPWSTR filename = (LPWSTR)A2W(path);


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
    if ((WavPlayer::hmmioIn = mmioOpen(path, NULL, MMIO_READ)) == NULL) {
        qDebug() << "Error: mmioOpen error";
        return; //exit(-1);
    }

    /*--------------------------------------------------------------------------------
    *mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
    *Go into RIFF chunk;
    *The file is wave format
    ---------------------------------------------------------------------------------*/
    parentChunk.fccType = mmioFOURCC('W', 'A', 'V', 'E');
    if (mmioDescend(hmmioIn, &parentChunk, NULL, MMIO_FINDRIFF)) {
        qDebug() << "Error: could not find WAVE chunk or";
        qDebug() << "the file is not in RIFF\n";
        mmioClose(hmmioIn, 0);
        return; //exit(-1);
    }

    /*--------------------------------------------------------------------------------
    *mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
    *Go into fmt chunk;
    ---------------------------------------------------------------------------------*/
    formatChunk.ckid = mmioFOURCC('f', 'm', 't', ' ');
    if (mmioDescend(hmmioIn, &formatChunk, &parentChunk, MMIO_FINDCHUNK)) {
        qDebug() << "Could not find FMT chunk.\n";
        mmioClose(hmmioIn, 0);
        return; //exit(-1);
    }

    /*--------------------------------------------------------------------------------
    *LONG mmioRead(HMMIO h, HPSTR pch, LONG cch);
    *reads a specified number of bytes from a file;
    ---------------------------------------------------------------------------------*/
    if (!mmioRead(hmmioIn, (char*)&fmtData, formatChunk.cksize)) {
        qDebug() << "Error in reading the waveformat\n";
        mmioClose(hmmioIn, 0);
        return; //exit(-1);
    }

    /*--------------------------------------------------------------------------------
    *mmioAscend(HMMIO h, LPMMCKINFO lpck, UINT flags);
    *ascend chunk
    ---------------------------------------------------------------------------------*/
    if (mmioAscend(hmmioIn, &formatChunk, 0)) {
        qDebug() << "Error in mmioAscend\n";
        mmioClose(hmmioIn, 0);
        return; //exit(-1);
    }

    /*--------------------------------------------------------------------------------
    *mmioDescend(HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
    *Go into data chunk;
    ---------------------------------------------------------------------------------*/
    dataChunk.ckid = mmioFOURCC('d', 'a', 't', 'a');
    if (mmioDescend(hmmioIn, &dataChunk, &parentChunk, MMIO_FINDCHUNK)) {
        qDebug() << "Could not find data chunk.\n";
        mmioClose(hmmioIn, 0);
        return; //exit(-1);
    }





    /*--------------------------------------------------------------------------------
    *Get the lOffset bytes from the current file position
    ---------------------------------------------------------------------------------*/
    DWORD dataOffset = mmioSeek(hmmioIn, 0, SEEK_CUR);
    DWORD dataChunkSize = dataChunk.cksize;

    /*--------------------------------------------------------------------------------
    *waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID, LPWAVEFORMATEX pwfx,
    DWORD dwCallback, DWORD Instance, DWORD fdwOpen);
    *Create a wave device.
    ---------------------------------------------------------------------------------*/
    err = waveOutOpen(&hAudioOut, WAVE_MAPPER, (WAVEFORMATEX *)&fmtData,
        (DWORD)NULL, 0, CALLBACK_FUNCTION);
    GetWaveError(err);

    /*--------------------------------------------------------------------------------
    *Determine the size of buffer
    ---------------------------------------------------------------------------------*/
    int blockSize = fmtData.nChannels*fmtData.wBitsPerSample;
    bufferSize = blockSize * fmtData.nSamplesPerSec / 8;
    int totalBlocks = dataChunkSize / blockSize;
    emit duration(dataChunk.cksize/fmtData.nAvgBytesPerSec);
//    int remainder = totalBlocks % BUFFER_QUANTITY;

    /*--------------------------------------------------------------------------------
    *waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
    *Prepare buffer
    ---------------------------------------------------------------------------------*/
    for (int i = 0; i < BUFFER_QUANTITY; i++) {
        databuffer[i].lpData = new char[bufferSize];
        databuffer[i].dwBufferLength = bufferSize;
        databuffer[i].dwFlags = 0;
        databuffer[i].dwLoops = 0;
        memset(databuffer[i].lpData, 0, bufferSize);
        err = waveOutPrepareHeader(hAudioOut, &databuffer[i], sizeof(WAVEHDR));
    }
    /*--------------------------------------------------------------------------------
    *waveOutWrite (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh );
    *Playback buffer data
    *loop
    ---------------------------------------------------------------------------------*/
    bufferLoop = 0;

    setVolume(50);
    while (1) {
        if (!mmioRead(hmmioIn, databuffer[bufferLoop].lpData, bufferSize)) {
            qDebug() << "Error in reading the waveformat\n";
            mmioClose(hmmioIn, 0);
            full=0;
            exit(-1); //exit(-1);
        }
        if (databuffer[bufferLoop].lpData == 0) {
            return;
        }
        mut.lock();
        waveOutWrite(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
        Sleep(1000); //Sleep(8000);
        mut.unlock();
        waveOutUnprepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(databuffer[bufferLoop]));
        memset(databuffer[bufferLoop].lpData, 0, bufferSize);
        err = waveOutPrepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
        bufferLoop++;
        if (bufferLoop == BUFFER_QUANTITY) {
            bufferLoop = 0;
        }
    }
    /*--------------------------------------------------------------------------------
    *mmioClose(HMMIO h, UINT wflags);
    *Close Wav file
    ---------------------------------------------------------------------------------*/



    /*--------------------------------------------------------------------------------
    *mmioClose(HMMIO h, UINT wflags);
    *Close Wav file
    ---------------------------------------------------------------------------------*/
    full=0;
    mmioClose(hmmioIn, 0);

    /*--------------------------------------------------------------------------------
    *waveOutClose(HWAVEOUT hwo);
    *Close audio device
    ---------------------------------------------------------------------------------*/
    waveOutClose(hAudioOut);

    qDebug() << "cat";

    return;
}

void WavPlayer::stop() {
//    waveOutBreakLoop()
    waveOutPause(hAudioOut);
//    waveOutRestart()
//    waveOutReset(hAudioOut);
//    waveInClose()
    mmioClose(hmmioIn, 0);
    waveOutClose(hAudioOut);
    terminate();
}

void WavPlayer::pause() {
    mut.lock();
    waveOutUnprepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(databuffer[bufferLoop]));
    memset(databuffer[bufferLoop].lpData, 0, bufferSize);
    err = waveOutPrepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
    waveOutPause(hAudioOut);
}

void WavPlayer::resume() {
    mut.unlock();
    waveOutRestart(hAudioOut);
}

void WavPlayer::subThread(int bufferLoop) {
//    if (!mmioRead(hmmioIn, databuffer[bufferLoop].lpData, bufferSize)) {
//        qDebug() << "Error in reading the waveformat\n";
//        mmioClose(hmmioIn, 0);
//        exit(-1); //exit(-1);
//    }
//    if (databuffer[bufferLoop].lpData == 0) {
//        return;
//    }
//    waveOutWrite(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//    Sleep(10000);
    waveOutUnprepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(databuffer[bufferLoop]));
    memset(databuffer[bufferLoop].lpData, 0, bufferSize);
    err = waveOutPrepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//    bufferLoop++;
//    if (bufferLoop == BUFFER_QUANTITY) {
//        bufferLoop = 0;
//    }
}

//void SubThread::run() {
//#include <wavplayer.h>
//    if (!mmioRead(*WavPlayer.hmmioIn, databuffer[bufferLoop].lpData, bufferSize)) {
//        qDebug() << "Error in reading the waveformat\n";
//        mmioClose(*WavPlayer.hmmioIn, 0);
//        return; //exit(-1);
//    }
//    if (databuffer[bufferLoop].lpData == 0) {
//        break;
//    }
//    waveOutWrite(*WavPlayer.hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//    Sleep(10000);
//    waveOutUnprepareHeader(*WavPlayer.hAudioOut, &databuffer[bufferLoop], sizeof(databuffer[bufferLoop]));
//    memset(databuffer[bufferLoop].lpData, 0, bufferSize);
//    err = waveOutPrepareHeader(*WavPlayer.hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//}
