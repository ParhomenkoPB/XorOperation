#include <QCoreApplication>
#include "FileModifier.h"

FileModifier::FileModifier(QObject* parent) : QObject(parent) {
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &FileModifier::processFiles);
}

void FileModifier::setInputMask(const QString& mask) {
    qDebug() << "Установка маски файла" << mask;
    inputMask = mask;
}

void FileModifier::setDeleteInputFiles(bool deleteInput) {
    qDebug() << "Удаление исходных файлов:" << deleteInput;
    deleteInputFiles = deleteInput;
}

void FileModifier::setOutputPath(const QString& path) {
    qDebug() << "Установка выходного каталога:" << path;
    outputPath = path;
}

void FileModifier::setOverwriteOutput(bool overwrite) {
    qDebug() << "Настройка перезаписи выходного файла:" << overwrite;
    overwriteOutput = overwrite;
}

void FileModifier::setPeriodicity(int ms) {
    qDebug() << "Настройка периодичности:" << ms;
    periodicity = ms;
}

void FileModifier::setBinaryValue(const QString& value) {
    qDebug() << "Перевод из шестнадцатеричной в двоичную:" << value;
    binaryValue = QByteArray::fromHex(value.toUtf8());
}

void FileModifier::setRunOnce(bool runOnce) {
    qDebug() << "Запуск один раз:" << runOnce;
    this->runOnce = runOnce;
}

void FileModifier::start() {
    qDebug() << "Старт";
    if (!QDir(outputPath).exists()) {
        qDebug() << "Выходной каталог не существует, создаем новый:" << outputPath;
        QDir().mkpath(outputPath);
    }
    if (runOnce) {
        processFiles();
    }
    else {
        timer->start(periodicity);
    }
}

void FileModifier::processFiles() {
    qDebug() << "Обработка файлов по маске:" << inputMask;
    QDir dir("C:/Users/user/Desktop/XorOperation");
    dir.setNameFilters(QStringList() << inputMask);
    dir.setFilter(QDir::Files);

    if (dir.entryList().isEmpty())
    {
        qDebug() << " Файла не существует, создайте файл ";
    }

    foreach(QFileInfo fileInfo, dir.entryInfoList()) {
        if (isFileLocked(fileInfo.filePath())) {
            qDebug() << "Файл" << fileInfo.filePath() << "заблокирован. Игнорируем.";
            continue;
        }

        QFile file(fileInfo.filePath());
        if (!file.open(QIODevice::ReadOnly)) {
            qDebug() << "Не удалось открыть файл" << fileInfo.filePath();
            continue;
        }

        QByteArray data = file.readAll();
        file.close();

        for (int i = 0; i < data.size(); ++i) {
            data[i] = data[i] ^ binaryValue[i % binaryValue.size()];
        }

        QString outputFilePath = outputPath + "/" + fileInfo.fileName();
        if (!overwriteOutput) {
            int counter = 1;
            while (QFile::exists(outputFilePath)) {
                outputFilePath = outputPath + "/" + QString("%1_%2").arg(fileInfo.baseName()).arg(counter++) + "." + fileInfo.completeSuffix();
            }
        }

        QFile outputFile(outputFilePath);
        if (!outputFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Не удалось открыть выходной файл" << outputFilePath;
            continue;
        }

        outputFile.write(data);
        outputFile.close();

        if (deleteInputFiles) {
            file.remove();
        }
    }

}

bool FileModifier::isFileLocked(const QString& filePath) {
    QFile file(filePath);
    return !file.open(QIODevice::ReadWrite);
}
int main(int argc, char *argv[]){
    QCoreApplication a(argc, argv);
    QString mask = "*.txt";
    bool deleteInputFiles = false;
    bool overwrite = true;
    int period = 10000;
    FileModifier _xor;
    _xor.setInputMask("*.txt");
    _xor.setDeleteInputFiles(deleteInputFiles);
    _xor.setOutputPath("C:/Users/user/Desktop/XorOperation/output");
    _xor.setOverwriteOutput(overwrite);
    _xor.setPeriodicity(period);
    _xor.setRunOnce(false);
    _xor.setBinaryValue("12345678");
    _xor.start();
    return a.exec();

}
