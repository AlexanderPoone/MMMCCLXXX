#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#ifndef WIN32_LEAN_AND_MEAN         //Required, or else Winsock will override Windows.h and cause error.
#define WIN32_LEAN_AND_MEAN
#endif

#define TAGLIB_STATIC

#define DEFAULT_PORT "6894"
#include "taglib/include/taglib/fileref.h"
#include "taglib/include/taglib/wavfile.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QSystemTrayIcon>
#include <QtWidgets>
#include <windows.h>                //WAV
#include <winsock2.h>               //Winsock (P2P)
#include <ws2tcpip.h>               //Winsock (P2P)
//#include <iphlpapi.h>
#include <stdio.h>                  //Winsock (P2P)
//#include <mmsystem.h>               //WAV
//We use QThread for multithreading.
//#pragma comment(lib, "winmm.lib")   //WAV
#pragma comment(lib, "Ws2_32.lib")  //Winsock (P2P)
#include "winsockserverthread.h"
#include "winsockclientthread.h"
#include "wavplayer.h"
#include <tchar.h>
#include "playpausebutton.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
//    void on_scrollSpeedDial_valueChanged(int value);
    void changePage(QModelIndex index);
    void serverDialogSlot();
    void clientDialogSlot();
    void createServerOrClients();
    void on_volumeSlider_valueChanged(int value);
    void on_sendButton_clicked();
    void on_lrcButton_clicked();
    void openFile();
    void quitSlot();
    void pauseSlot();
    void startSecTimer();
    void stopSecTimer();
    void moveSeekBar();
    void stopSlot();
    void setScrollSpeed();
    void setBars(int secs);
    void trayIconActivated(QSystemTrayIcon::ActivationReason reason);
    void createClients(); //const QString &ip, const QString &port
    void onItemClicked(QListWidgetItem *item);
    void onItemDoubleClicked(QListWidgetItem *item);
    void onRemoteItemDoubleClicked(QListWidgetItem *item);
    void onReceiveMusicCatalogue(QString rawJSON);
private:
    WinSockClientThread *client_1, *client_2, *client_3;
    PlayPauseButton *playPauseItem;
    QDir tmpDir;
    QLabel *addL,*one_addL, *one_addL_0, *one_addL_1, *one_addL_2,
    *two_addL, *one_portL, *two_portL, *two_addL_0, *two_addL_1, *two_addL_2;
    QSpinBox *addS_3, *portS,
     *one_addS_3, *one_portS,
     *two_addS_3, *two_portS;
    QRadioButton *selectServer, *selectClient;
    QString playingPath;
    int secs, now;
    void updateElapsed();
    void createServer();
    void scrollScroller();
    bool event(QEvent *event) override;
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void bindToView(QGraphicsView *view, QGraphicsScene *scene, QGraphicsItem *item);
    void createSysTray();
    void useGeniusAPI();
    void setArtist(QString artist);
    void setSongTitle(QString songTitle);
    void initWavFile(QString fileLocation);

    WinSockServerThread *server;

    Ui::MainWindow *ui;
    WavPlayer *wavPlay;
    QSystemTrayIcon *sysTray;
    QGraphicsScene *previousScene;
    QGraphicsScene *playPauseScene;
    QGraphicsScene *nextScene;
    QGraphicsScene *stopScene;
    QGraphicsScene *ratingBarScene;
    QGraphicsScene *bulletScrScene;
    QTimer *secTimer;
    QTimer *lyricsTimer;
    int speed=10;

    QString artist;
    QString songTitle;
    enum genre; //yet to be implemented
    //
    //
//    HMMIO *hmmioIn; // HMMIO mmioOpen (LPSTR filename, LPMMIOINFO info, DWORD flags);
//    LPMMCKINFO *pckInRIFF; // mmioDescend (HMMIO h, LPMMCKINO lpck, LPMMCKINFO lpckParent, UNIT flags);
//    HPSTR *pcmWaveFormat; // LONG mmioRead (HMMIO h, HPSTR pch, LONG cch);
//    LONG waveFormatSize; // Ditto.
//    LPMMCKINFO *ckIn; // mmioAscend(HMMIO h, LPMMCKINFO lpck, UINT flags);
//    LPHWAVEOUT *hAudioOut; // waveOutOpen(LPHWAVEOUT phwo, UINT uDeviceID, LPWAVEFORMATEX pwfx, DWORD dwCallback, DWORD Instance, DWORD fdwOpen );
//    LPWAVEFORMATEX *pcmWaveFormat1; // Ditto.
//    DWORD playSamples; // Ditto. DWORD dwCallback.
//    LPSTR *errorMsg; // waveOutGetErrorText(MMRESULT mmrError, LPSTR pszText, UINT cchText);
//    LPWAVEHDR *dataBufferElement; // waveOutPrepareHeader(HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
    //Also waveOutWrite (HWAVEOUT hwo, LPWAVEHDR pwh, UINT cbwh);
    //mmioClose (HMMIO h, UINT wflags); too.
    //Don't forget waveOutClose (HWAVEOUT hwo);
    //Volume: between 0xFFFF (255 255) and 0x0000, int qRound(2.55*volumeSlider.value()) << 8;
    //Left two bits: left-channel, right two bits: right-channel
    //
    //
    int iResult;
    WSADATA wsaData;
    struct addrinfo *result = NULL, *ptr = NULL, hints;
    SOCKET ConnectSocket;
    SOCKET ListenSocket;
};

#endif // MAINWINDOW_H
