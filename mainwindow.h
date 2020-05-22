#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
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
    bool isAllocated_;
};
#endif // MAINWINDOW_H
