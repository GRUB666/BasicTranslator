#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtNetwork/QNetworkAccessManager>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->inverse_lang->setIcon(QIcon("://Arrow.png"));
    setWindowIcon(QIcon("://Icon.ico"));
    last_symbol = new QTimer(this);
    last_symbol->setInterval(1200);

    connect(last_symbol, SIGNAL(timeout()), this, SLOT(timeoutSlot()));


    fillComboBoxes();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::TranslateTheText()
{
    QString result = "";
    if(ui->first_lang_text->toPlainText().length() > 0)
    {
        QProcess process(this);
        QString str = ui->first_lang_text->toPlainText();
        cutSpecialCharacters(str);
        std::string to_translate = (str + "\n").toLocal8Bit().data();
        std::string lang_param = (first_lang + "-" + second_lang + "\n").toLocal8Bit().data();
        const char* str_char = to_translate.c_str();
        const char* lang_char = lang_param.c_str();


        process.start("Translator.exe");

        process.write(str_char);
        process.waitForBytesWritten();

        process.write(lang_char);
        process.waitForBytesWritten();

        process.waitForReadyRead();

        result = QString::fromLocal8Bit(process.readAll());
        process.waitForFinished();
    }

    ui->second_lang_text->setText(result);
}

QString MainWindow::getLanguageSybm(LangCode code)
{
    switch (code)
    {
    case English:
        return "en";
        break;
    case Russian:
        return "ru";
        break;
    case Spanish:
        return  "es";
        break;
    }
}

void MainWindow::cutSpecialCharacters(QString &str)
{
    for(int i = 0; i < str.length(); i++)
    {
        if(str[i] == '\n')
        {
            str[i] = ' ';
        }
    }
}

void MainWindow::fillComboBoxes()
{
    QVector<QString> languages {"Английский", "Русский"};

    for(int i = 0; i < languages.length(); i++)
    {
        ui->first_lang_cmb->addItem(languages[i]);
        ui->second_lang_cmb->addItem(languages[i]);
    }

    ui->first_lang_cmb->setCurrentIndex(0);
    ui->second_lang_cmb->setCurrentIndex(1);
}



void MainWindow::on_first_lang_cmb_currentIndexChanged(int index)
{
    first_lang = getLanguageSybm(LangCode(index));
    TranslateTheText();
}

void MainWindow::on_second_lang_cmb_currentIndexChanged(int index)
{
    second_lang = getLanguageSybm(LangCode(index));
    TranslateTheText();
}

void MainWindow::on_first_lang_text_textChanged()
{
    last_symbol->start();
}

void MainWindow::timeoutSlot()
{
    TranslateTheText();
    last_symbol->stop();
}

void MainWindow::on_inverse_lang_clicked()
{
    QString tmp = first_lang;
    first_lang = second_lang;
    second_lang = tmp;

    tmp = ui->first_lang_text->toPlainText();
    ui->first_lang_text->blockSignals(true);
    ui->first_lang_text->setText(ui->second_lang_text->toPlainText());
    ui->first_lang_text->blockSignals(false);
    ui->second_lang_text->blockSignals(true);
    ui->second_lang_text->setText(tmp);
    ui->second_lang_text->blockSignals(false);

    int tmp_index = ui->first_lang_cmb->currentIndex();
    ui->first_lang_cmb->blockSignals(true);
    ui->first_lang_cmb->setCurrentIndex(ui->second_lang_cmb->currentIndex());
    ui->second_lang_cmb->blockSignals(true);

    ui->second_lang_cmb->blockSignals(true);
    ui->second_lang_cmb->setCurrentIndex(tmp_index);
    ui->second_lang_cmb->blockSignals(false);

    TranslateTheText();
}
