//#include "FileModifier.h"
#include "mainwindow.h"

FileModifier::FileModifier(QObject* parent) : QObject(parent) {
    m_timer = new QTimer(this);
    connect(m_timer, &QTimer::timeout, this, &FileModifier::processFiles);
}

void FileModifier::setInputMask(const QString& mask) {
    qDebug() << "Установка маски файла" << mask;
    m_inputMask = mask;
}

void FileModifier::setDeleteInputFiles(bool deleteInput) {
    qDebug() << "Удаление исходных файлов:" << deleteInput;
    m_deleteInputFiles = deleteInput;
}

void FileModifier::setInputPath(const QString& inPath) {
    qDebug() << "Установка входного каталога:" << inPath;
    m_inputPath = inPath;
}

void FileModifier::setOutputPath(const QString& outPath) {
    qDebug() << "Установка выходного каталога:" << outPath;
    m_outputPath = outPath;
}

void FileModifier::setOverwriteOutput(bool overwrite) {
    qDebug() << "Настройка перезаписи выходного файла:" << overwrite;
    m_overwriteOutput = overwrite;
}

void FileModifier::setPeriodicity(int ms) {
    qDebug() << "Настройка периодичности:" << ms;
    m_periodicity = ms;
}

void FileModifier::setBinaryValue(const QString& value) {
    qDebug() << "Перевод из шестнадцатеричной в двоичную:" << value;
    m_binaryValue = QByteArray::fromHex(value.toUtf8());
}

void FileModifier::setRunOnce(bool runOnce) {
    qDebug() << "Запуск один раз:" << runOnce;
    this->m_runOnce = runOnce;
}

void FileModifier::start() {
    qDebug() << "Старт";
    if (!QDir(m_outputPath).exists()) {
        qDebug() << "Выходной каталог не существует, создаем новый:" << m_outputPath;
        QDir().mkpath(m_outputPath);
    }
    if (m_runOnce) {
        processFiles();
    }
    else {
        m_timer->start(m_periodicity);
    }
}

void FileModifier::processFiles() {
    qDebug() << "Обработка файлов по маске:" << m_inputMask;
    QDir dir(m_inputPath);
    dir.setNameFilters(QStringList() << m_inputMask);
    dir.setFilter(QDir::Files);

    if (dir.entryList().isEmpty())
    {
        qDebug() << " Файла не существует, создайте файл ";
    }

    foreach(QFileInfo fileInfo, dir.entryInfoList()) {
        if (_isFileLocked(fileInfo.filePath())) {
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
            data[i] = data[i] ^ m_binaryValue[i % m_binaryValue.size()];
        }

        QString outputFilePath = m_outputPath + "/" + fileInfo.fileName();
        if (!m_overwriteOutput) {
            int counter = 1;
            while (QFile::exists(outputFilePath)) {
                outputFilePath = m_outputPath + "/" + QString("%1_%2").arg(fileInfo.baseName()).arg(counter++) + "." + fileInfo.completeSuffix();
            }
        }

        QFile outputFile(outputFilePath);
        if (!outputFile.open(QIODevice::WriteOnly)) {
            qDebug() << "Не удалось открыть выходной файл" << outputFilePath;
            continue;
        }

        outputFile.write(data);
        outputFile.close();

        if (m_deleteInputFiles) {
            file.remove();
        }
    }

}

bool FileModifier::_isFileLocked(const QString& filePath) {
    QFile file(filePath);
    return !file.open(QIODevice::ReadWrite);
}
