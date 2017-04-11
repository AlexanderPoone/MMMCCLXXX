#ifndef VIDEODIALOG_H
#define VIDEODIALOG_H
#include <QMainWindow>
#include <QEvent>

class VideoDialog : public QMainWindow
{
public:
    VideoDialog();
private:
    bool event(QEvent *event) override;
};

#endif // VIDEODIALOG_H
