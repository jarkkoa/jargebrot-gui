#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , previewIterations_(100), previewSize_(200), fileName_("jargebrot.ppm")
    , isAllocated_(false)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;

    if (isAllocated_)
        free(pixelArray_);
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);

    iterations_ = ui->iterSpinBox->value();
    imageSize_ = ui->sizeSpinBox->value();
    zoomFactor_ = ui->zoomSpinBox->value();
    xCoordinate_ = ui->xCoorSB->value();
    yCoordinate_ = ui->yCoorSB->value();

    pixelArray_ = (uint8_t*)malloc(imageSize_*imageSize_);
    isAllocated_ = true;

    #pragma omp parallel
    {
        unsigned int x, y;
        uint8_t pixelValue;

        #pragma omp for
        for (y = 0; y < imageSize_; ++y) {
            for (x = 0; x < imageSize_; ++x) {
                pixelValue = calculateMandelbrot(iterations_, zoomFactor_,
                                            x, y, xCoordinate_, yCoordinate_,
                                            imageSize_);
                pixelArray_[y*imageSize_+x] = pixelValue;
            }
        }
    }

    drawPPM(pixelArray_, fileName_, imageSize_);


    ui->pushButton->setDisabled(false);

}
