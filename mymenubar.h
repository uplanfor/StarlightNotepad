#ifndef MYMENUBAR_H
#define MYMENUBAR_H

#include <QMenuBar>
#include <QDebug>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QCloseEvent>

class MainWindow;

class MyMenuBar : public QMenuBar
{
    friend MainWindow;
public:
    MyMenuBar(QWidget*);
    void setTitlebarContent(const QString& content);
protected:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
//    void mouseDoubleClickEvent(QMouseEvent *event) override;
    void closeEvent(QCloseEvent *event) override;
    void resizeEvent(QResizeEvent *) override;
    void resetTitleContent();

    bool isMaxSize;
    QLabel *title;
    QPushButton* min_size_btn;
    QPushButton* max_size_btn;
    QPushButton* close_btn;
private:
    QPoint pressPos;
    QWidget *m_parent;
    QWidget *title_content;
};

#endif // MYMENUBAR_H
