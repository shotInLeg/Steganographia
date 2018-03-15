#include "steganographia.h"
#include "ui_steganographia.h"


QString Steganographia::decodePng(const QImage &img)
{
    bool reading = true;
    QString msg = "";
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);

            //int R = pixel.red();
            //int G = pixel.green();
            int B = pixel.blue();
            //int A = pixel.alpha();

            if(B == 0) {
                reading = false;
            }
            else if(reading) {
                qDebug() << x << " " << y << ") " << B << " " << char(B);
                msg += QChar(char(B));
            }

            ui->pbProgress->setValue(x * img.height() + y);
        }
    }
    ui->pbProgress->setValue(img.width() * img.height());

    qDebug() << msg;
    return msg;
}

QByteArray Steganographia::decodePng(const QImage &img, bool)
{
    bool reading = true;
    QByteArray file;
    for(int x = 0; x < img.width(); ++x)
    {
        for(int y = 0; y < img.height(); ++y)
        {
            QColor pixel = img.pixelColor(x, y);

            //int R = pixel.red();
            //int G = pixel.green();
            int B = pixel.blue();
            //int A = pixel.alpha();

            if(B == 0) {
                reading = false;
            }
            else if(reading) {
                file.append(char(B));
            }

            ui->pbProgress->setValue(x * img.height() + y);
        }
    }
    ui->pbProgress->setValue(img.width() * img.height());

    return file;
}
