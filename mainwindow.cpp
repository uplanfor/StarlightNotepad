#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(int argc, char* argv[], QWidget *parent)
    : QMainWindow(parent),
    has_saved(true),
     ui(new Ui::MainWindow),
     file_path()
{
    ui->setupUi(this);
    this->setMinimumSize(420, 400);
//    ui->menubar->installEventFilter(this);

    if (argc > 1)
    {
        QFile file(argv[1]);
        file.open(QIODevice::ReadOnly);
        QByteArray arr = file.readAll();

        ui->textEdit->setText(arr);
        changeTitle(file.fileName().section("/",-1,-1));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}




//void MainWindow::mouseMoveEvent(QMouseEvent *event)
//{

//}


//void MainWindow::mousePressEvent(QMouseEvent *event)
//{
//    qDebug() << "press ";
//}


void MainWindow::setFrame(QWidget* f)
{
    frame = f;
}


void MainWindow::setupFunctions()
{
// todo
}


void MainWindow::closeEvent(QCloseEvent *event)
{
    if (!has_saved)
    {
        const QString& content = QString("The file \"%1\" has not been saved.\nWould you like to save it before you quit?").arg(file_path.section("/",-1,-1));
        QMessageBox::StandardButton  result = QMessageBox::warning(this, "Warning!", content, QMessageBox::No | QMessageBox::Yes);
        if (result == QMessageBox::Yes)
        {
            on_actionSave_triggered();
        }
    }
    qApp->quit();
    return;
}

void MainWindow::on_actionOpen_triggered()
{
    file_path = QFileDialog::getOpenFileName(this, "Opem a file");
    if (!file_path.isEmpty())
    {
        QFile file(file_path);
        file.open(QIODevice::ReadOnly);
        QByteArray arr = file.readAll();

        ui->textEdit->setText(arr);
        changeTitle(file_path.section("/",-1,-1));
    }
}

void MainWindow::on_actionSave_triggered()
{
    if (file_path.isEmpty())
    {
        on_actionSaveAs_triggered();
        return;
    }
    if (has_saved)
    {
        return;
    }
    QFile file(file_path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(ui->textEdit->toPlainText().toLatin1());
    has_saved = true;
}

void MainWindow::on_actionSaveAs_triggered()
{
    QString path = QFileDialog::getSaveFileName(this, "Save this file as...");
    if (path.isEmpty())
    {
        return;
    }
    QFile file(path);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    file.write(ui->textEdit->toPlainText().toLatin1());
    if (file_path.isEmpty())
    {
        file_path = path;
        has_saved = true;
        changeTitle(file_path.section("/",-1,-1));
    }
}


void MainWindow::changeTitle(const QString& content)
{
    const QString title(QString("%1 - Starlight Notepad").arg(content));
    static_cast<QWidget*>(this->parent())->setWindowTitle(title);
    ui->menubar->setTitlebarContent(title);
}

void MainWindow::on_textEdit_textChanged()
{
    if (!file_path.isEmpty())
    {
        has_saved = false;
    }
}

void MainWindow::on_actionAbout_triggered()
{

    ShellExecute(NULL, TEXT("open"), TEXT("https://www.ixigua.com/home/1874031348815676/?list_entrance=userdetail&source=follow"), NULL, NULL, SW_SHOW);
}
