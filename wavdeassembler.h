#ifndef WAVDEASSEMBLER_H
#define WAVDEASSEMBLER_H

#include "wavplayer.h"

class WavDeassembler : public WavPlayer
{
    Q_OBJECT
public:
    WavDeassembler();
    void run() Q_DECL_OVERRIDE;
private:
    void deassemble();
signals:
    void partitionMade(char *partition);
};

#endif // WAVDEASSEMBLER_H
