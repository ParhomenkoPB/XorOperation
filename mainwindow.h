#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QtWidgets>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QComboBox>
#include "FileModifier.h"




class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();


private:

    QPushButton *m_ExecButton;
    QPushButton *m_ExitButton;
    QLabel *m_label1;
    QLabel *m_label2;
    QLabel *m_label3;
    QLabel *m_label4;
    QLabel *m_label5;
    QGridLayout *m_LayoutInPath;
    QGridLayout *m_LayoutMaskFile;
    QGridLayout *m_LayoutTimer;
    QGridLayout *m_LayoutBinaryValue;
    QGridLayout *m_gridOutputPath;
    QHBoxLayout *m_LayoutDeleteInputFiles;
    QHBoxLayout *m_LayoutOverwriteOutput;
    QHBoxLayout *m_H_ExecLayout;
    QVBoxLayout *m_ExecLayout;
    QLineEdit *m_LineInPath;
    QLineEdit *m_LineMaskFile;
    QLineEdit *m_LineTimer;
    QLineEdit *m_LineBinaryValue;
    QLineEdit *m_LineOutputPath;
    QCheckBox *m_DeleteInputFiles;
    QCheckBox *m_OverwriteOutput;
    QComboBox *m_comboBox;

    std:: unique_ptr <FileModifier> m_filemodifier{};

private slots:

    void _on_ExecButton_clicked();

};


#endif // MAINWINDOW_H
