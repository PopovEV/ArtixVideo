#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(const QString & title, QWidget * parent = 0, Qt::WFlags flags = 0);
    ~DockWidget();

    QSize sizeHint() const;
    void resizeEvent(QResizeEvent *) const;


    
signals:
    
public slots:
    
};

#endif // DOCKWIDGET_H
