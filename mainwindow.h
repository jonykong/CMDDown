#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QProcess>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_start_clicked();
    void onStart();

private:
    Ui::MainWindow  *ui;
    QProcess*        m_Process;
    int              m_nCurrent;     // ��ǰִ�е�
    int              m_nTotal;       // �ܼ�
    int              m_nNumber;      // ���ٸ�
    QString          m_strUrl;
};

#endif // MAINWINDOW_H
