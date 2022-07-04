#include "mymenubar.h"

MyMenuBar::MyMenuBar(QWidget *parent):m_parent(parent)
{
    title_content = new QWidget(this);

    QHBoxLayout *layout = new QHBoxLayout(title_content);
    layout->setSpacing(0);
    layout->setContentsMargins(0, 0, 0, 0);
    title = new QLabel("untitled - Starlight Notepad", title_content);
    min_size_btn = new QPushButton("-", title_content);
    max_size_btn = new QPushButton("口", title_content);
    close_btn = new QPushButton("X", title_content);
    min_size_btn->setFixedSize(20, 20);
    max_size_btn->setFixedSize(20, 20);
    close_btn->setFixedSize(20, 20);
    layout->addWidget(title);
    layout->addWidget(min_size_btn);
    layout->addWidget(max_size_btn);
    layout->addWidget(close_btn);

    resetTitleContent();

    connect(close_btn, &QPushButton::pressed, m_parent, &QWidget::close);
    connect(min_size_btn, &QPushButton::pressed, [=]
    {
        static_cast<QWidget*>(m_parent->parent())->showMinimized();
    });
    connect(max_size_btn, &QPushButton::pressed, [=]
    {
        if (isMaxSize)
        {
            static_cast<QWidget*>(m_parent->parent())->showNormal();
        }
        else
        {
            static_cast<QWidget*>(m_parent->parent())->showMaximized();
        }
        isMaxSize = !isMaxSize;
    });
}


void MyMenuBar::mouseMoveEvent(QMouseEvent *event)
{
    for (auto it : this->children())
    {
        if(it->metaObject()->className() == QStringLiteral("QMenu"))
        {
            if (static_cast<QMenu*>(it)->rect().contains(event->pos()))
            {
                QMenuBar::mouseMoveEvent(event);
                return;
            }
        }
    }
    if (event->buttons() & Qt::LeftButton)
    {
        static_cast<QWidget*>(m_parent->parent())->move(event->globalPos() + m_parent->pos() - pressPos);
    }
}


void MyMenuBar::mousePressEvent(QMouseEvent *event)
{
    for (auto it : this->children())
    {
        if(it->metaObject()->className() == QStringLiteral("QMenu"))
        {
            if (static_cast<QMenu*>(it)->rect().contains(event->pos()))
            {
                QMenuBar::mousePressEvent(event);
                return;
            }
        }
    }

    if (event->button() == Qt::LeftButton)
    {
        if (isMaxSize)
        {
            isMaxSize = !isMaxSize;
            static_cast<QWidget*>(m_parent->parent())->showNormal();
            return;
        }
        pressPos = event->pos();
    }
}


void MyMenuBar::resetTitleContent()
{
    int menu_width = 0;
    int my_width = this->width();
    for (auto it : this->children())
    {
        if(it->metaObject()->className() == QStringLiteral("QMenu"))
        {
            menu_width += static_cast<QWidget*>(it)->width();
        }
    }
    menu_width -= 270;
    title_content->resize(my_width - menu_width, this->height());
    title_content->move(menu_width, 0);
}


void MyMenuBar::resizeEvent(QResizeEvent *)
{
    resetTitleContent();
}


void MyMenuBar::closeEvent(QCloseEvent *event)
{
    event->ignore();
}


//void MyMenuBar::mouseDoubleClickEvent(QMouseEvent *event)
//{
//    for (auto it : this->children())
//    {
//        if(it->metaObject()->className() == QStringLiteral("QMenu"))
//        {
//            if (static_cast<QMenu*>(it)->rect().contains(event->pos()))
//            {
//                QMenuBar::mouseDoubleClickEvent(event);
//                return;
//            }
//        }
//    }
//    if (isMaxSize)
//    {
//        static_cast<QWidget*>(m_parent->parent())->showNormal();
//    }
//    else
//    {
//        static_cast<QWidget*>(m_parent->parent())->showMaximized();
//    }
//    isMaxSize = !isMaxSize;
//}


void MyMenuBar::setTitlebarContent(const QString &content)
{
    title->setText(content);
}
