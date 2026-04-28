#pragma once

#include <iostream>
#include <QObject>
#include <QTimer>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QDebug>
#include <QByteArray>
#include <QString>

class FileModifier : public QObject {
    Q_OBJECT

public:
    explicit FileModifier(QObject* parent = nullptr);


    void setInputMask(const QString& mask);
    void setDeleteInputFiles(bool deleteInput);
    void setOutputPath(const QString& path);
    void setOverwriteOutput(bool overwrite);
    void setPeriodicity(int ms);
    void setBinaryValue(const QString& value);
    void setRunOnce(bool runOnce);
    void start();
    void processFiles();

private:
    bool isFileLocked(const QString& filePath);

    QString inputMask;
    bool deleteInputFiles = false;
    QString outputPath;
    bool overwriteOutput = true;
    int periodicity = 1000;
    QByteArray binaryValue;
    QTimer* timer;
    bool runOnce = true;
};
