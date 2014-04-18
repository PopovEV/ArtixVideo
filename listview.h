#ifndef LISTVIEW_H
#define LISTVIEW_H

#include <QListView>
#include <QEvent>

class ListView : public QListView
{
    Q_OBJECT
public:
    explicit ListView(QWidget *parent = 0);


protected:
    void mousePressEvent(QMouseEvent *e);
    void mouseDoubleClickEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e);
    void mouseMoveEvent(QMouseEvent *e);

signals:

public slots:

};

#endif // LISTVIEW_H
