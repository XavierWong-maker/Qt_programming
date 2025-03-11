#include <QCoreApplication>
#include <QFile>
#include <QByteArray>
#include <QDebug>
#include <QFileInfo>
#include <QDateTime>
#include <QTemporaryFile>

void write(QString f){
    QFile file(f);
    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        file.write("D.T.Software\n");
        file.write("Xiaver\n");
        file.close();
    }
}

void read(QString f){
    QFile file(f);
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray ba = file.readAll();
        QString s(ba);
        qDebug() << s;
        file.close();
    }
}

void info(QString f)
{
    QFile file(f);
    QFileInfo info(file);

    qDebug() << info.exists();
    qDebug() << info.isFile();
    qDebug() << info.isReadable();
    qDebug() << info.isWritable();
    qDebug() << info.birthTime();
    qDebug() << info.lastRead();
    qDebug() << info.lastModified();
    qDebug() << info.path();
    qDebug() << info.fileName();
    qDebug() << info.suffix();
    qDebug() << info.size();
}

void textStream(QString f){
    QFile file(f);

    if(file.open(QIODevice::WriteOnly | QIODevice::Text)){
        QTextStream ts_Out(&file);
        ts_Out << QString("D.T.Software") << Qt::endl;
        ts_Out << QString("Result: ") << Qt::endl;
        ts_Out << 5 << '*' << 6 << '=' << 5 * 6 << Qt::endl;
        file.close();
    }

    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream ts_In(&file);
        while(!ts_In.atEnd()){
            QString line = ts_In.readLine();
            qDebug() << line;
        }
        file.close();
    }
}

void dataStream(QString f){
    QFile file(f);

    if(file.open(QIODevice::WriteOnly)){
        QDataStream ds_Out(&file);
        ds_Out.setVersion(QDataStream::Qt_6_8);
        ds_Out << QString("D.T.Software");
        ds_Out << QString("Result: ");
        ds_Out << 3.14;
        file.close();
    }

    if(file.open(QIODevice::ReadOnly)){
        QDataStream ds_In(&file);
        ds_In.setVersion(QDataStream::Qt_6_8);
        QString dt = "";
        QString result = "";
        double value = 0;

        ds_In >> dt;
        ds_In >> result;
        ds_In >> value;

        file.close();
        qDebug() << dt;
        qDebug() << result;
        qDebug() << value;
    }
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    /* //TemporaryFile
    QTemporaryFile tempFile;
    if(tempFile.open()){
        tempFile.write("Xavier");
        tempFile.close();
    }*/

    // write("C:/Users/Administrator/Desktop/file_test.txt");
    // read("C:/Users/Administrator/Desktop/file_test.txt");
    // info("C:/Users/Administrator/Desktop/file_test.txt");

    // textStream("C:/Users/Administrator/Desktop/file_test.txt");
    dataStream("C:/Users/Administrator/Desktop/file_test.txt");
    return a.exec();
}
