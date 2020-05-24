#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , previewIterations_(100), previewSize_(200), fileName_("jargebrot.png")
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
//    ui->pushButton->setDisabled(true);
//    ui->drawingStatus->setText("Calculating...");

    iterations_ = ui->iterSpinBox->value();
    imageSize_ = ui->sizeSpinBox->value();
    zoomFactor_ = ui->zoomSpinBox->value();
    xCoordinate_ = ui->xCoorSB->value();
    yCoordinate_ = ui->yCoorSB->value();

//    pixelArray_ = (uint8_t*)malloc(imageSize_*imageSize_);
    std::vector<uint8_t> imageBuffer(imageSize_*imageSize_);

    #pragma omp parallel
    {
        unsigned int x, y;
        uint8_t pixelValue;

        #pragma omp for nowait
        for (y = 0; y < imageSize_; ++y) {
            for (x = 0; x < imageSize_; ++x) {

                pixelValue = calculateMandelbrot(iterations_, zoomFactor_, x, y,
                                                 xCoordinate_, yCoordinate_,
                                                 imageSize_);

                imageBuffer[y*imageSize_+x] = pixelValue;
            }
        }
    }

    drawPNG(imageBuffer, fileName_, imageSize_);
//    ui->pushButton->setDisabled(false);
//    ui->drawingStatus->setText("Done!");
//    free(pixelArray_);

}

void MainWindow::on_sizeSpinBox_valueChanged(int arg1)
{
    double memUsage = (arg1*arg1)/1000;
    ui->memUsageLabel->setText(QString::number(memUsage) + " KB");
}
