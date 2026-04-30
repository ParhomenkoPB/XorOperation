#include <QStyle>
#include <QDesktopWidget>
#include "mainwindow.h"
//#include "FileModifier.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Widget::setWindowTitle("Xor.exe");
    //Widget::setFixedSize(400,130);
    Widget::setFixedSize(600,330);
    QDesktopWidget desktop;
    QRect rect = desktop.availableGeometry(this);
    QPoint center = rect.center();
    int x = center.x() - (width()/2);
    int y = center.y() - (height()/2);
    center.setX(x);
    center.setY(y);
    move(center);

    m_LineInPath = new QLineEdit("C:/Users/user/Desktop/XorOperation");
    m_LineMaskFile = new QLineEdit();
    m_LineTimer = new QLineEdit();
    m_LineBinaryValue = new QLineEdit();
    m_LineOutputPath = new QLineEdit("C:/Users/user/Desktop/XorOperation/output");
    m_comboBox = new QComboBox();
    m_comboBox->addItem("Разовый запуск");
    m_comboBox->addItem("Работа по таймеру");
    m_label1 = new QLabel("Введите путь к входным файлам");
    m_label2 = new QLabel("Введите маску(Например: *txt)");
    m_label3 = new QLabel("Введите периодичность(Таймер)");
    m_label4 = new QLabel("Введите переменную");
    m_label5 = new QLabel("Путь для сохранения результирующих файлов");
    m_DeleteInputFiles = new QCheckBox("Удалять входные файлы");
    m_DeleteInputFiles->isChecked();

    m_OverwriteOutput = new QCheckBox("Перезаписывать выходные файлы");
    m_OverwriteOutput->isChecked();

    m_LineInPath->setFixedWidth(150);
    m_LineMaskFile->setFixedWidth(150);
    m_LineTimer->setFixedWidth(150);
    m_LineBinaryValue->setFixedWidth(150);
    m_LineOutputPath->setFixedWidth(150);

    m_ExecButton = new QPushButton("Выполнить");
    m_ExitButton = new QPushButton("Выход");
    m_LayoutInPath = new QGridLayout;
    m_LayoutInPath->addWidget(m_LineInPath, 0, 0, Qt::Alignment());
    m_LayoutInPath->addWidget(m_label1, 0, 1, Qt::Alignment());

    m_LayoutMaskFile = new QGridLayout;
    m_LayoutMaskFile->addWidget(m_LineMaskFile, 0, 0, Qt::Alignment());
    m_LayoutMaskFile->addWidget(m_label2, 0, 1, Qt::Alignment());

    m_LayoutTimer = new QGridLayout;
    m_LayoutTimer->addWidget(m_LineTimer, 0, 0, Qt::Alignment());
    m_LayoutTimer->addWidget(m_label3, 0, 1, Qt::Alignment());

    m_LayoutBinaryValue = new QGridLayout;
    m_LayoutBinaryValue->addWidget(m_LineBinaryValue, 0, 0, Qt::Alignment());
    m_LayoutBinaryValue->addWidget(m_label4, 0, 1, Qt::Alignment());

    m_gridOutputPath = new QGridLayout;
    m_gridOutputPath->addWidget(m_LineOutputPath, 0, 0, Qt::Alignment());
    m_gridOutputPath->addWidget(m_label5, 0, 1, Qt::Alignment());

    m_LayoutDeleteInputFiles = new QHBoxLayout;//QGridLayout;
    m_LayoutDeleteInputFiles->addWidget(m_DeleteInputFiles);

    m_LayoutOverwriteOutput = new QHBoxLayout;//QGridLayout;
    m_LayoutOverwriteOutput->addWidget(m_OverwriteOutput);

    m_ExecLayout = new QVBoxLayout;
    m_ExecButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    m_ExitButton->setSizePolicy(QSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed, QSizePolicy::ToolButton));
    m_ExecLayout->addStretch();
    m_ExecLayout->addLayout(m_LayoutInPath);
    m_ExecLayout->addLayout(m_LayoutMaskFile);
    m_ExecLayout->addLayout(m_LayoutDeleteInputFiles);
    m_ExecLayout->addLayout(m_gridOutputPath);
    m_ExecLayout->addLayout(m_LayoutOverwriteOutput);
    m_ExecLayout->addWidget(m_comboBox);
    m_ExecLayout->addLayout(m_LayoutTimer);
    m_ExecLayout->addLayout(m_LayoutBinaryValue);
    m_ExecLayout->addWidget(m_ExecButton);
    m_ExecLayout->addWidget(m_ExitButton);
    m_ExecLayout->addStretch();

    m_H_ExecLayout = new QHBoxLayout;
    m_H_ExecLayout->addStretch();
    m_H_ExecLayout->addLayout(m_ExecLayout);
    m_H_ExecLayout->addStretch();

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(m_H_ExecLayout);

    connect(m_ExecButton, &QPushButton::clicked, this, &Widget::_on_ExecButton_clicked);
    connect(m_ExitButton, &QPushButton::clicked, this, &QApplication::quit);
}

Widget::~Widget()
{
}



void Widget::_on_ExecButton_clicked()
{
    m_filemodifier = ::std::make_unique<FileModifier>();
    m_filemodifier->setInputPath(m_LineInPath->text());
    int period = m_LineTimer->text().toInt();
    m_filemodifier->setInputMask(m_LineMaskFile->text());
    m_filemodifier->setOutputPath(m_LineOutputPath->text());
    m_filemodifier->setDeleteInputFiles(m_DeleteInputFiles->isChecked());
    m_filemodifier->setOverwriteOutput(m_OverwriteOutput->isChecked());
    int x = QString::compare("Разовый запуск", m_comboBox->currentText(), Qt::CaseInsensitive);
    if(x==0){
        m_filemodifier->setRunOnce(true);
    }
    else{
        m_filemodifier->setRunOnce(false);
    }
    m_filemodifier->setPeriodicity(period);
    m_filemodifier->setBinaryValue(m_LineBinaryValue->text());
    m_filemodifier->start();

}


