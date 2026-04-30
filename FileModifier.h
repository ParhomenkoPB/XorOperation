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
#include <memory>


class FileModifier : public QObject {
    Q_OBJECT

public:
    explicit FileModifier(QObject* parent = nullptr);


         void setInputMask(const QString& mask);
         void setDeleteInputFiles(bool deleteInput);
         void setInputPath(const QString& inPath);
         void setOutputPath(const QString& path);
         void setOverwriteOutput(bool overwrite);
         void setPeriodicity(int ms);
         void setBinaryValue(const QString& value);
         void setRunOnce(bool runOnce);
         void start();
         void processFiles();

private:
    bool _isFileLocked(const QString& filePath);

    QString m_inputMask;
    QString m_inputPath;
    bool m_deleteInputFiles;
    QString m_outputPath;
    bool m_overwriteOutput;
    int m_periodicity;
    QByteArray m_binaryValue;
    QTimer* m_timer;
    bool m_runOnce;
};
