#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include <QMainWindow>
#include <QDebug>
#include <QMouseEvent>
#include <QCloseEvent>
#include <QFileDialog>
#include <QMessageBox>
#include <QFile>
#include <windows.h>


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(int argc, char* argv[], QWidget *parent = nullptr);
    ~MainWindow();
//    void mousePressEvent(QMouseEvent* event) override;
//    void mouseMoveEvent(QMouseEvent* event) override;
    void closeEvent(QCloseEvent *event) override;

    void setFrame(QWidget *f);
    void setupFunctions();
    void changeTitle(const QString& content);
//    bool event(QEvent *event) override;

private slots:
    void on_actionOpen_triggered();

    void on_actionSave_triggered();

    void on_actionSaveAs_triggered();

    void on_textEdit_textChanged();

    void on_actionAbout_triggered();

private:
    bool has_saved;
    Ui::MainWindow *ui;
    QWidget *frame;
    QString file_path;
};
#endif // MAINWINDOW_H
