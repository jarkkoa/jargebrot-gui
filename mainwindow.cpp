#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "utilities.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , previewIterations_(100), previewSize_(200), fileName_("jargebrot.ppm")
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setDisabled(true);

    iterations_ = ui->iterSpinBox->value();
    imageSize_ = ui->sizeSpinBox->value();
    zoomFactor_ = ui->zoomSpinBox->value();
    xCoordinate_ = ui->xCoorSB->value();
    yCoordinate_ = ui->yCoorSB->value();

    std::vector<uint8_t> imageBuffer;
    unsigned int x, y;

    //#pragma omp parallel
    {
        std::vector<uint8_t> partialImageBuffer;

        #pragma omp for nowait
        for (y = 0; y < imageSize_; ++y) {
            for (x = 0; x < imageSize_; ++x) {
                uint8_t pixelValue =
                        calculateMandelbrot(iterations_, zoomFactor_,
                                            x, y, xCoordinate_, yCoordinate_,
                                            imageSize_, iterations_);
                partialImageBuffer.push_back(pixelValue);
            }
        }
        //#pragma omp critical
        imageBuffer.insert(imageBuffer.end(), partialImageBuffer.begin(),
                           partialImageBuffer.end());
    }

    drawPPM(imageBuffer, fileName_, imageSize_);

    ui->pushButton->setDisabled(false);

}
