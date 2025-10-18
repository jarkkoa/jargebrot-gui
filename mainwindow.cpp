#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , previewIterations_(100), previewSize_(200), fileName_("jargebrot.png")
    , threadCount(std::thread::hardware_concurrency())
{
    ui->setupUi(this);
    ui->memUsageLabel->setText("160 KB");
}


MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);
    ui->drawingStatus->setText("Calculating...");

    iterations_ = ui->iterSpinBox->value();
    imageSize_ = ui->sizeSpinBox->value();
    zoomFactor_ = ui->zoomSpinBox->value();
    xCoordinate_ = ui->xCoorSB->value();
    yCoordinate_ = ui->yCoorSB->value();

    imageBuffer.resize(imageSize_*imageSize_);

    std::thread calcThread(&MainWindow::calculate, this);
    calcThread.detach();

}

void MainWindow::on_sizeSpinBox_valueChanged(int arg1)
{
    double memUsage = (arg1*arg1)/1000;
    ui->memUsageLabel->setText(QString::number(memUsage) + " KB");
}

void MainWindow::calculate()
{
    threadPool.clear();

    for (unsigned i = 0; i < threadCount; i++)
    {
        threadPool.push_back(std::thread(&MainWindow::threadCalculate, this, i));
    }

    for (auto &thread : threadPool)
    {
        thread.join();
    }


    QMetaObject::invokeMethod(this, [this]() {
        ui->pushButton->setDisabled(false);
        ui->drawingStatus->setText("Done!");
    });

    Jarge::drawPNG(imageBuffer, fileName_, imageSize_);
}

void MainWindow::threadCalculate(unsigned threadIndex)
{
    unsigned x, y;
    uint8_t pixelValue;

    for (y = threadIndex; y < imageSize_; y += threadCount) {
        for (x = 0; x < imageSize_; x++) {

            pixelValue = Jarge::calculateMandelbrot(iterations_, zoomFactor_, x, y,
                                                    xCoordinate_, yCoordinate_,
                                                    imageSize_);

            imageBuffer[y*imageSize_+x] = pixelValue;
        }
    }
}
