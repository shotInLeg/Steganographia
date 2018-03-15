#include "steganographia.h"
#include "ui_steganographia.h"

Steganographia::Steganographia(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Steganographia)
{
    ui->setupUi(this);
    ui->pbProgress->setValue(0);
}

Steganographia::~Steganographia()
{
    delete ui;
}

void Steganographia::on_bSelectFile_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(
        this, "Выберите файл для шифрования", ".", "*.*"
    );
    ui->eFileInput->setText(filePath);
}

void Steganographia::on_bSelectInputImage_clicked()
{
    QString imgPath = QFileDialog::getOpenFileName(
        this, "Выберите целевое изображение", ".", "*.png"
    );
    ui->eImageInput->setText(imgPath);

    this->showImage(imgPath, ui->imgInput);
}

void Steganographia::on_bEncode_clicked()
{
    QString msgText = ui->pteInput->toPlainText();
    QString filePath = ui->eFileInput->text();
    QString imgPath = ui->eImageInput->text();

    if(imgPath == "") {
        QMessageBox::information(this, "Ошибка", "Необходимо выбрать изображение");
        return;
    }
    else if(msgText == "" && filePath == "") {
        QMessageBox::information(this, "Ошибка", "Необходимо ввести текст или выбрать файл");
        return;
    }

    QImage img(imgPath);
    ui->imgInput->setPixmap(QPixmap(imgPath));
    ui->pbProgress->setMaximum(img.width() * img.height());
    ui->pbProgress->setValue(0);

    QImage mimg;
    if(msgText != "") {
        mimg = this->encode(imgPath, msgText);
    }
    else if(filePath != "") {
        QByteArray fileData = this->readDataFromFile(filePath);
        if(fileData.size() == 0) {
            return;
        }

        mimg = this->encode(imgPath, fileData);
    }

    QString outputImg = QFileDialog::getSaveFileName(
        this, "Выберите куда сохранить результат", ".", "*.*"
    );
    mimg.save(outputImg);

    this->showImage(outputImg, ui->imgOutput);
}

void Steganographia::on_bDecode_clicked()
{
    QString imgPath = ui->eImageInput->text();

    if(imgPath == "") {
        QMessageBox::information(this, "Ошибка", "Необходимо выбрать изображение");
        return;
    }

    QImage img(imgPath);
    ui->imgInput->setPixmap(QPixmap(imgPath));
    ui->pbProgress->setMaximum(img.width() * img.height());
    ui->pbProgress->setValue(0);


    if(ui->cbFile->isChecked()) {
        QByteArray fileData = this->decode(imgPath, true);

        QString outputFile = QFileDialog::getSaveFileName(
            this, "Выберите куда сохранить результат", ".", "*.*"
        );

        if(!this->writeDataToFile(outputFile, fileData)) {
            return;
        }

        ui->teOutput->setPlainText("File save to " + outputFile);
    }
    else {
        QString msg = this->decode(imgPath);
        qDebug() << msg;
        ui->teOutput->setPlainText(msg);
    }
}
