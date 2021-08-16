#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QProcess>
#include <QTextEdit>

#ifdef _MSC_VER
#		if _MSC_VER >= 1600
#			pragma execution_character_set("utf-8")
#		endif
#endif

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_Process(new QProcess)
{
    ui->setupUi(this);

    ui->textEdit->setLineWrapMode(QTextEdit::NoWrap);

    m_Process->setProcessChannelMode(QProcess::MergedChannels);

    connect(m_Process, &QProcess::readyReadStandardOutput, this, [this]
    {
        QByteArray qbt = m_Process->readAllStandardOutput();
        QString msg = QString::fromUtf8(qbt);
        ui->textEdit->append(msg);
        ui->textEdit->update();
    });

    connect(m_Process, static_cast<void(QProcess::*)(int)>(&QProcess::finished), this, [this]
    {
        onStart();
    });

    connect(m_Process, static_cast<void(QProcess::*)(QProcess::ProcessError)>(&QProcess::error), this, [this]
    {
        onStart();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_start_clicked()
{
    ui->textEdit->clear();

    m_strUrl = ui->lineEdit_url->text();
    if (m_strUrl.isEmpty())
    {
        m_strUrl = QString("https://www.bilibili.com/video/BV12E411B7A5?p=");
    }
    m_nCurrent = ui->spinBox_begin->value();
    m_nTotal = ui->spinBox_end->value();

    m_nNumber = m_nTotal - m_nCurrent + 1;
    if (m_nNumber < 0)
    {
        ui->textEdit->append(QString("数量不合法"));
        return;
    }

    onStart();
}

void MainWindow::onStart()
{
    if (m_nTotal >= m_nCurrent)
    {
        QString strRealUrl = QString("you-get -o D:/cmdDown %1%2").arg(m_strUrl).arg(QString::number(m_nCurrent));
        m_Process->start(strRealUrl);

        ui->progressBar->setValue(m_nCurrent * 100 / m_nNumber);
        m_nCurrent++;
    }
}
