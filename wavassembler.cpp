#include "wavassembler.h"

WavAssembler::WavAssembler() {

}

void WavAssembler::run() {
    assemble();
}

void WavAssembler::receiveBuffer(char *buffer) {
    // :'(
    currentPosition+=176400;
}

void WavAssembler::assemble() {
    //    USES_CONVERSION;
    CONST int BUFFER_QUANTITY = 5;
    WAVEFORMATEX fmtData;
    databuffer.reserve(BUFFER_QUANTITY);
    for (int i=0;i<BUFFER_QUANTITY; i++) {
        WAVEHDR tmp;
        databuffer.push_back(tmp);
    }
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
    bufferSize = 176400;
    /*--------------------------------------------------------------------------------
        *waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
        *Prepare buffer
        ---------------------------------------------------------------------------------*/
    for (int i = 0; i < BUFFER_QUANTITY; i++) {
        databuffer[i].lpData = (char *) malloc(bufferSize);
        databuffer[i].dwBufferLength = bufferSize;
        databuffer[i].dwFlags = 0;
        databuffer[i].dwLoops = 0;
        memset(databuffer[i].lpData, 0, bufferSize);
//        err = waveOutPrepareHeader(hAudioOut, &databuffer[i], sizeof(WAVEHDR));
    }
    /*--------------------------------------------------------------------------------
        *waveOutWrite (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh );
        *Playback buffer data
        *loop
        ---------------------------------------------------------------------------------*/
    bufferLoop = 0;
//    while (1) {
//        mut.lock();
//        waveOutWrite(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//        Sleep(1000); //Please let the second finish first.
//        mut.unlock();
//        waveOutUnprepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(databuffer[bufferLoop]));
//        memset(databuffer[bufferLoop].lpData, 0, bufferSize);
//        err = waveOutPrepareHeader(hAudioOut, &databuffer[bufferLoop], sizeof(WAVEHDR));
//        bufferLoop++;
//        if (bufferLoop == BUFFER_QUANTITY) {
//            bufferLoop = 0;
//        }
//    }
    /*--------------------------------------------------------------------------------
        *mmioClose(HMMIO h, UINT wflags);
        *Close Wav file
        ---------------------------------------------------------------------------------*/



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
