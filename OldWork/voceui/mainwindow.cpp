#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <voce.h>
#include <QtCore>
#include <QtGui>
#include <string>
#include <sstream>

#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif

std::string s;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton->setText("Speak");
    ui->textEdit->installEventFilter(this);

    voce::init("C:/Users/Ernest Curioso/Documents/Voce/voce-0.9.1/voce-0.9.1/lib", true, true,
               "", "");
    voce::setRecognizerEnabled(false);
    voce::synthesize("Press down and speak and I will repeat");
    voce::synthesize("or type your command in the input text field.");
}

MainWindow::~MainWindow()
{
    delete ui;
    voce::destroy();
}

void MainWindow::on_pushButton_pressed()
{
    voce::stopSynthesizing();
    voce::setRecognizerEnabled(true);
}

void MainWindow::on_pushButton_released()
{
    #ifdef WIN32
        ::Sleep(1500);
    #else
        usleep(1500);
    #endif

    s = voce::popRecognizedString();
    voce::setRecognizerEnabled(false);
    voce::stopSynthesizing();
    voce::synthesize(s);
    if (s.empty() == false)
    {
    ui->textBrowser->QTextBrowser::append("You said: " + QString::fromStdString(s));
    ui->textBrowser->QTextBrowser::append("Cayley: " + QString::fromStdString(s));
    }
}

bool MainWindow::eventFilter(QObject *object, QEvent *event)
{
    if (object == ui->textEdit && event->type() == QEvent::KeyPress)
    {
        voce::stopSynthesizing();

        QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);

        if (keyEvent->key() == Qt::Key_Return)
        {
            QString r = ui->textEdit->toPlainText();
            s = r.toStdString();

            if (s != "")
            {
                QStringList list = r.split("\n");
                int length = list.length();

                for (int i = 0; i < length; i++)
                {
                    if (list[i] != "")
                    {
                        QStringList list2 = list[i].split(" ");
                        int length2 = list2.length();

                        for (int j = 0; j < length; j++)
                        {
                            if (list2[j] != "")
                            {
                                ui->textBrowser->QTextBrowser::append("You typed: " + QString::fromStdString(s));
                                ui->textBrowser->QTextBrowser::append("Cayley: " + QString::fromStdString(s));
                                voce::synthesize(s);
                                ui->textEdit->QTextEdit::setText("");
                                return true;
                            }
                        }
                    }
                }
            }
            ui->textEdit->QTextEdit::setText("");
        }
        else
        {
            return QMainWindow::eventFilter(object, event);
        }
    }
    else
    {
        return QMainWindow::eventFilter(object, event);
    }
}
