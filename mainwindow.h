#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <string>
#include <QProcess>
#include <QDebug>
#include <QTimer>
#include <QTextCodec>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

enum LangCode
{
    English, Russian, Spanish
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

    QString first_lang, second_lang;
    QString final_lang;
    QTimer *last_symbol;
    QString to_translate;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    void TranslateTheText();
    QString getLanguageSybm(LangCode code);
    void cutSpecialCharacters(QString &str);
    void fillComboBoxes();


private slots:
    void on_first_lang_cmb_currentIndexChanged(int index);
    void on_second_lang_cmb_currentIndexChanged(int index);
    void on_first_lang_text_textChanged();
    void timeoutSlot();
    void on_inverse_lang_clicked();
};
#endif // MAINWINDOW_H
