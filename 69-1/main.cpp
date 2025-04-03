#include <QCoreApplication>
#include <QImage>
#include <QPixmap>
#include <QDebug>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QImage img;
    if(!img.load("D:/Github/Qt_programming/69-1/PixPin.jpg")) {
        qDebug() << "Error loading image - check if file exists and path is correct";
        return 1;
    }
    img = img.scaled(QSize(img.width()/2, img.height()/2));

    for(int i = 0; i < img.width(); ++i) {
        for(int j = 0; j < img.height(); ++j) {
            QRgb rgb = img.pixel(i, j);
            int r = qRed(rgb);
            int g = qGreen(rgb);
            int b = qBlue(rgb);
            int gray = (r + g + b) / 3;
            img.setPixel(i, j, qRgb(gray, gray, gray));
        }
    }

    if(!img.save("new.jpg")) {
        qDebug() << "Error saving image";
        return 1;
    }
    qDebug() << "Image processed successfully";
    return a.exec();
}

