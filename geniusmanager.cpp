#include "geniusmanager.h"

static const char *base="https://api.genius.com"; //All interaction with the API must be done over HTTPS.
static const char *id="NL14RZ5i4tDImb8fPWBMXz1iAG8_86HJeyrllKdfaVkGaSWkYBdZjGpTpbTnVKPd";
static const char *secret="1OqgKFHflhdd9kOZpxE-nzt-HKnq6GuoZCXjeUwYyNWNz8tMVMHOBND96pPbm4ajDR7_lO_Hc9rdgSlUJLYvHA";

QNetworkReply* res;

GeniusManager::GeniusManager()
{
    QNetworkAccessManager::QNetworkAccessManager();

    //    QNetworkConfigurationManager mgr;
    //    QNetworkConfiguration ap = mgr.defaultConfiguration();
    //    QNetworkSession *session = new QNetworkSession(ap);
    //    session->open();
    //    qDebug() << session->error();
    QUrl url("https://api.genius.com/search");
    QUrlQuery query;
    query.addQueryItem(QStringLiteral("q"), QStringLiteral("Sia Chandelier"));
    url.setQuery(query);
    QNetworkRequest req(url);
    req.setRawHeader(QByteArray("client_id"), QByteArray("NL14RZ5i4tDImb8fPWBMXz1iAG8_86HJeyrllKdfaVkGaSWkYBdZjGpTpbTnVKPd"));
    req.setRawHeader(QByteArray("client_secret"), QByteArray("1OqgKFHflhdd9kOZpxE-nzt-HKnq6GuoZCXjeUwYyNWNz8tMVMHOBND96pPbm4ajDR7_lO_Hc9rdgSlUJLYvHA"));
    req.setRawHeader(QByteArray("Authorization"), QStringLiteral("Bearer %1").arg("oyb9YtIexk-TqF-1rITrR3XdTVjKE60XythFwfDoqr52eRXcjR1SdrnkqDDRhQb7").toLatin1());
    res = get(req);
    connect(res, &QNetworkReply::finished, this, &GeniusManager::result);
}

void GeniusManager::result() {
//    qDebug() << "Fuck!";
//    qDebug() << res->isOpen();
    if (res->error() == QNetworkReply::NoError) {
        qDebug() << "No errors!";
    } else {
        qCritical() << "Error!";
    }
    int statusCode = res->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << QVariant(statusCode).toString();
    QJsonDocument json = QJsonDocument::fromJson(res->readAll());
    qDebug() << json.isNull();
    qDebug() << json.object();
}
