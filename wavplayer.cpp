#include "wavplayer.h"

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

void WavPlayer::setPath(LPTSTR path) {
    this->path=path;
}

void WavPlayer::run() {
    play();
}

void WavPlayer::play() {
//    USES_CONVERSION;
    CONST int BUFFER_QUANTITY = 5;


    //MMIOINFO AudioData;
    HMMIO hmmioIn;
    MMCKINFO parentChunk;
    MMCKINFO formatChunk;
    MMCKINFO dataChunk;
    WAVEFORMATEX fmtData;
    HWAVEOUT  hAudioOut;
    WAVEHDR databuffer[BUFFER_QUANTITY];


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
    if ((hmmioIn = mmioOpen(path, NULL, MMIO_READ)) == NULL) {
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
    MMRESULT err = waveOutOpen(&hAudioOut, WAVE_MAPPER, (WAVEFORMATEX *)&fmtData,
        (DWORD)NULL, 0, CALLBACK_FUNCTION);
    GetWaveError(err);

    /*--------------------------------------------------------------------------------
    *Determine the size of buffer
    ---------------------------------------------------------------------------------*/
    int blockSize = fmtData.nChannels*fmtData.wBitsPerSample;
    int bufferSize = blockSize * fmtData.nSamplesPerSec;
    int totalBlocks = dataChunkSize / blockSize;
    int remainder = totalBlocks % BUFFER_QUANTITY;

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
    int bufferLoop = 0;


    while (1) {

        if (!mmioRead(hmmioIn, databuffer[bufferLoop].lpData, bufferSize)) {
            qDebug() << "Error in reading the waveformat\n";
            mmioClose(hmmioIn, 0);
            return; //exit(-1);
        }
        if (databuffer[bufferLoop].lpData == 0) {
            break;
        }
        waveOutWrite(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
        Sleep(10000);
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
    mmioClose(hmmioIn, 0);

    /*--------------------------------------------------------------------------------
    *waveOutClose(HWAVEOUT hwo);
    *Close audio device
    ---------------------------------------------------------------------------------*/
    waveOutClose(hAudioOut);

    qDebug() << "cat";

    return;
}
