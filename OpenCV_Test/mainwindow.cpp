#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>

using namespace cv;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    Mat image = imread("C:\\Users\\Administrator\\Pictures\\641.jpg", 1);
    if (image.empty()) {
        qDebug() << "Error: Could not load the image!";
        return;
    }

    Mat grayImage;
    cvtColor(image, grayImage, COLOR_BGR2GRAY);

    Mat thresholdImage;
    threshold(grayImage, thresholdImage, 127, 255, THRESH_BINARY);

    Mat blurImage;
    GaussianBlur(image, blurImage, Size(7, 7), 0);

    Mat cascadeImage;
    Canny(blurImage, cascadeImage, 125, 175);

    Mat dilatingImage;
    Mat kernel = getStructuringElement(MORPH_RECT, Size(2, 2));
    dilate(cascadeImage, dilatingImage, kernel);

    imshow("Image", dilatingImage);
}

MainWindow::~MainWindow()
{
    delete ui;
}
