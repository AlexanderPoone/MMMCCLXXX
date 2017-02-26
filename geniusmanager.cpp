#include "geniusmanager.h"

static const char *base="https://api.genius.com/"; //All interaction with the API must be done over HTTPS.
static const char *id="NL14RZ5i4tDImb8fPWBMXz1iAG8_86HJeyrllKdfaVkGaSWkYBdZjGpTpbTnVKPd";
static const char *secret="1OqgKFHflhdd9kOZpxE-nzt-HKnq6GuoZCXjeUwYyNWNz8tMVMHOBND96pPbm4ajDR7_lO_Hc9rdgSlUJLYvHA";

GeniusManager::GeniusManager()
{
    QNetworkRequest req;
    req.setUrl(QUrl(base));
//    req.setUrl(QUrl(QStringLiteral("%1/q?=Zaz").arg(base)));
//    req.setRawHeader("Authorization", secret);
//    QUrlQuery getData;
//    postData.addQueryItem("q", "Zaz");
//    sendCustomRequest(req, "")
    QNetworkReply* reply = get(req);
    qDebug() << qPrintable(reply->errorString());
}
