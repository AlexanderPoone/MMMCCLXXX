#include "lrchandler.h"

LRCHandler::LRCHandler(QString path, QLabel *label)
{
label->setTextFormat(Qt::RichText);
QFile file(path);
if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;
QString str=file.readAll();
QRegExp y("(\\[.*\\])");
y.setMinimal(true);
str.remove(y);
str.prepend("<div style='color:gainsboro'><p>");
str.replace(QRegExp("\\n"),"</p><p>");
str.append("</p></div>");
qDebug() << str;
label->setText(str);
}
