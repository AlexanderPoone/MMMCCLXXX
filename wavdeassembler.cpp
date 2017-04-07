#include "wavdeassembler.h"

WavDeassembler::WavDeassembler() {

}

void WavDeassembler::run() {
    deassemble();
}

void WavDeassembler::deassemble() {
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
    /*--------------------------------------------------------------------------------
        *HMMIO mmioOpen(LPSTR filename, LPMMIOINFO info, DWORD flags);
        *Open the a wav file.
        ---------------------------------------------------------------------------------*/
    if ((WavDeassembler::hmmioIn = mmioOpen(path, NULL, MMIO_READ)) == NULL) {
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

    QList<QString> *fmtList=new QList<QString>;
    fmtList->append(QString::number(fmtData.cbSize));
    fmtList->append(QString::number(fmtData.nAvgBytesPerSec));
    fmtList->append(QString::number(fmtData.nBlockAlign));
    fmtList->append(QString::number(fmtData.nChannels));
    fmtList->append(QString::number(fmtData.nSamplesPerSec));
    fmtList->append(QString::number(fmtData.wBitsPerSample));
    fmtList->append(QString::number(fmtData.wFormatTag));
    emit fmtDataPrepared(fmtList);
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
//    err = waveOutOpen(&hAudioOut, WAVE_MAPPER, (WAVEFORMATEX *)&fmtData,
//                      (DWORD)NULL, 0, CALLBACK_FUNCTION);
//    GetWaveError(err);

    /*--------------------------------------------------------------------------------
        *Determine the size of buffer
        ---------------------------------------------------------------------------------*/
    int blockSize = fmtData.nChannels*fmtData.wBitsPerSample;
    bufferSize = blockSize * fmtData.nSamplesPerSec / 8;
    qDebug() << "Buffer size:::" << bufferSize;
//    int totalBlocks = dataChunkSize / blockSize;
//    emit duration(dataChunk.cksize/fmtData.nAvgBytesPerSec);

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

    //    setVolume(50);
    while (1) {
        if (!mmioRead(hmmioIn, databuffer[bufferLoop].lpData, bufferSize)) { //Copy received data to buffer
            qDebug() << "Error 2: in reading the waveformat\n";
            mmioClose(hmmioIn, 0);
            return; //exit(-1);
        }
        if (databuffer[bufferLoop].lpData == 0) {
            return;
        }
        emit partitionMade(databuffer[bufferLoop].lpData, bufferSize);
        Sleep(800);
        free(databuffer[bufferLoop].lpData);
        databuffer[bufferLoop].lpData = (char *) malloc(bufferSize);
        memset(databuffer[bufferLoop].lpData, 0, bufferSize);
        bufferLoop++;
        if (bufferLoop == BUFFER_QUANTITY) {
            bufferLoop = 0;
        }
        qDebug() << databuffer[bufferLoop].lpData;
    }
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
