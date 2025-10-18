#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <thread>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_sizeSpinBox_valueChanged(int arg1);



private:

    void calculate();
    void threadCalculate(unsigned threadIndex);

    Ui::MainWindow *ui;

    unsigned int iterations_;
    unsigned int imageSize_;
    double xCoordinate_;
    double yCoordinate_;
    double zoomFactor_;

    const unsigned int previewIterations_;
    const unsigned int previewSize_;
    std::string fileName_;

    uint8_t* pixelArray_;
    unsigned int threadCount;
    std::vector<uint8_t> imageBuffer;
    std::vector<std::thread> threadPool;
};
#endif // MAINWINDOW_H
