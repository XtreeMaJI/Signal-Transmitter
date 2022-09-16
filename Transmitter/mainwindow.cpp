#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    server = new CServer();
    signalGenerator = new CSignalGenerator();

    signalGenerator->setServer(server);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete server;
    delete signalGenerator;
}

void MainWindow::on_startServerBtn_clicked()
{
    if(!server->tryStartServer())
    {
        ui->serverStatusLabel->setText("Server failed to start");
        return;
    }

    ui->serverStatusLabel->setText("Server has been started");
}

void MainWindow::on_transmitSignalBtn_clicked()
{
    if(!server->isListening())
    {
        ui->signalStatusLabel->setText("Please, start server first");
        return;
    }

    if(signalGenerator->isGenerating)
        return;

    ui->signalStatusLabel->setText("Signal transmitting");

    signalGenerator->startGenerateSignal();
}

QString MainWindow::excludeLetters(QString str)
{
    QString text = "";
    for(auto ch : str)
    {
        if((ch >= '0' && ch <= '9') || (ch == '.' && !text.contains('.')))
        {
            text.append(ch);
        }
    }
    return text;
}

void MainWindow::on_freqLineEdit_textEdited(const QString &arg1)
{
    QString text = excludeLetters(arg1);
    ui->freqLineEdit->setText(text);
    signalGenerator->setFrequency(text.toDouble());
}

void MainWindow::on_amplLineEdit_textEdited(const QString &arg1)
{
    QString text = excludeLetters(arg1);
    ui->amplLineEdit->setText(text);
    signalGenerator->setAmplitude(text.toDouble());
}

