#include "videodialog.h"
#include "videogiantwidget.h"
#include <QHBoxLayout>

VideoDialog::VideoDialog()
{
    setWindowIcon(QIcon(":/jukebox.png"));
    resize(width()+100, 1000);
    setWindowTitle(QStringLiteral("Video Player"));
    setStyleSheet("background-image: url(:/ice_cubes.png);");
    //    QHBoxLayout *hbox;
    VideoGiantWidget *w=new VideoGiantWidget(this);
    w->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    setCentralWidget(w);
    //    hbox->addWidget(w);
    //    setLayout(hbox);
}

bool VideoDialog::event(QEvent *event) {
    QMainWindow::event(event);
    switch (event->type()) {
    case QEvent::WindowActivate: //QEvent::Enter
        this->setWindowOpacity(1);
        break;
    case QEvent::WindowDeactivate: //QEvent::Leave
        this->setWindowOpacity(0.9);
        break;
    }
    return true;
}
