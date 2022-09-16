#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "cserver.h"
#include "csignalgenerator.h"

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_startServerBtn_clicked();

    void on_transmitSignalBtn_clicked();

    void on_freqLineEdit_textEdited(const QString &arg1);

    void on_amplLineEdit_textEdited(const QString &arg1);

private:
    QString excludeLetters(QString str);

    Ui::MainWindow *ui;
    CServer* server;
    CSignalGenerator* signalGenerator;

};
#endif // MAINWINDOW_H
