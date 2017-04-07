#ifndef WAVASSEMBLER_H
#define WAVASSEMBLER_H

#include "wavplayer.h"

class WavAssembler : public WavPlayer
{
    Q_OBJECT
public:
    WavAssembler();
    void run() Q_DECL_OVERRIDE;
    void assemble();
public slots:
    void receiveBuffer(char *buffer, int bufLen);
private:
    WAVEFORMATEX fmtData;
    long int currentPosition;
};

#endif // WAVASSEMBLER_H
