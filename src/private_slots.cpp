#include "steganographia.h"
#include "ui_steganographia.h"


QImage Steganographia::encode(const QString &path, const QString &msg)
{
    if(path.endsWith(".png")) {
        QImage img(path);
        return this->encodePng(img, msg);
    }

    throw std::invalid_argument("Format is not supported");
}

QImage Steganographia::encode(const QString &path, const QByteArray &file)
{
    if(path.endsWith(".png")) {
        QImage img(path);
        return this->encodePng(img, file);
    }

    throw std::invalid_argument("Format is not supported");
}

QString Steganographia::decode(const QString &path)
{
    if(path.endsWith(".png")) {
        QImage img(path);
        return this->decodePng(img);
    }

    throw std::invalid_argument("Format is not supported");
}

QByteArray Steganographia::decode(const QString &path, bool)
{
    if(path.endsWith(".png")) {
        QImage img(path);
        return this->decodePng(img, true);
    }

    throw std::invalid_argument("Format is not supported");
}
