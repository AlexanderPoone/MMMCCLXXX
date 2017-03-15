#include "lrchandler.h"

LRCHandler::LRCHandler(QString path, QLabel *label)
{
label->setTextFormat(Qt::PlainText);
QFile file(path);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
QString str=file.readAll();
QRegExp x("\[[0-9|:|\.]{1,10}");
str.remove(x).remove("]");
qDebug() << str;
label->setText(str);
}
