#include "geniusmanager.h"

static const char *base="https://api.genius.com"; //All interaction with the API must be done over HTTPS.
static const char *id="NL14RZ5i4tDImb8fPWBMXz1iAG8_86HJeyrllKdfaVkGaSWkYBdZjGpTpbTnVKPd";
static const char *secret="1OqgKFHflhdd9kOZpxE-nzt-HKnq6GuoZCXjeUwYyNWNz8tMVMHOBND96pPbm4ajDR7_lO_Hc9rdgSlUJLYvHA";

QLabel* holder;
QNetworkReply* res;
QNetworkReply* resLyrics;
QString lyrics;

GeniusManager::GeniusManager(QLabel *label, QString artist, QString songTitle)
{
    QNetworkAccessManager::QNetworkAccessManager();
    holder=label;
    holder->setTextFormat(Qt::RichText);
    holder->setText("Loading lyrics...");
    //    QNetworkConfigurationManager mgr;
    //    QNetworkConfiguration ap = mgr.defaultConfiguration();
    //    QNetworkSession *session = new QNetworkSession(ap);
    //    session->open();
    //    qDebug() << session->error();
    QUrl url("https://api.genius.com/search");
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("q"), QStringLiteral("%1 %2").arg(artist).arg(songTitle));
    url.setQuery(query);
    QNetworkRequest req(url);
    req.setRawHeader(QByteArray("client_id"), QByteArray("NL14RZ5i4tDImb8fPWBMXz1iAG8_86HJeyrllKdfaVkGaSWkYBdZjGpTpbTnVKPd"));
    req.setRawHeader(QByteArray("client_secret"), QByteArray("1OqgKFHflhdd9kOZpxE-nzt-HKnq6GuoZCXjeUwYyNWNz8tMVMHOBND96pPbm4ajDR7_lO_Hc9rdgSlUJLYvHA"));
    req.setRawHeader(QByteArray("Authorization"), QStringLiteral("Bearer %1").arg("oyb9YtIexk-TqF-1rITrR3XdTVjKE60XythFwfDoqr52eRXcjR1SdrnkqDDRhQb7").toLatin1());
    res = get(req);
    connect(res, SIGNAL(finished()), this, SLOT(result()));
}

void GeniusManager::result() {
    //    qDebug() << "Fuck!";
    //    qDebug() << res->isOpen();
    if (res->error() == QNetworkReply::NoError) {
        qDebug() << "No errors!";
    } else {
        qDebug() << "Error!";
    }
    int statusCode = res->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << QVariant(statusCode).toString();
    QJsonDocument json = QJsonDocument::fromJson(res->readAll());
    QJsonArray hits = json.object().value("response").toObject().value("hits").toArray();
    QJsonObject result = hits.at(0).toObject().value("result").toObject();
    qDebug() << result.value("primary_artist").toObject().value("name").toString();
    qDebug() << result.value("title").toString();
    qDebug() << result.value("url").toString();
    QNetworkRequest reqLyrics(QUrl(result.value("url").toString()));
    resLyrics = get(reqLyrics);
    connect(resLyrics, SIGNAL(finished()), this, SLOT(httpFinished()));
    //    connect(resLyrics, &resLyrics::finished, this, &GeniusManager::resultLyrics);
}

void GeniusManager::httpFinished() {
    QString text = resLyrics->readAll();
    qDebug() << "Text: " << text.left(120);
    if (resLyrics->error() == QNetworkReply::NoError) {
        qDebug() << "No errors!";
    } else {
        qCritical() << "Error!";
    }
    QRegExp lyricsRe("<lyrics.*>(.*)</lyrics>");
    lyricsRe.indexIn(text);
    lyrics = lyricsRe.cap(1);
    qDebug() << lyrics.left(120);
    QRegExp stripAHref("(<a href.*>|</a>)");
    stripAHref.setMinimal(true);
    lyrics.replace(stripAHref,"");
    holder->setText(lyrics);
}

//    int statusCode = resLyrics->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
//    qDebug() << QVariant(statusCode).toString();
//    page.settings()->setAttribute(QWebEngineSettings::AutoLoadImages, false);
//    //    page.settings()->setAttribute(QWebEngineSettings::JavascriptEnabled, false);
//    QWebEnginePage page;
//    page.setHtml(resLyrics->readAll());
//    page.runJavaScript("return ''", [](const QVariant &v) {
//        qDebug() << v;
//    });

//    page.settings()->setAttribute(QWebSettings::AutoLoadImages, false);
//    page.settings()->setAttribute(QWebSettings::JavascriptEnabled, false);
//    page.mainFrame()->setHtml(resL->readAll());
//    QWebElement lyricbox = page.mainFrame()->findFirstElement("lyrics[class=lyrics]")
