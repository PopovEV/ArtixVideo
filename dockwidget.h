#ifndef DOCKWIDGET_H
#define DOCKWIDGET_H

#include <QDockWidget>

class DockWidget : public QDockWidget
{
    Q_OBJECT
public:
    explicit DockWidget(QWidget * parent = 0, const QString & title = QString(), Qt::WFlags flags = 0);
    ~DockWidget();

    QSize sizeHint() const;
    void resizeEvent(QResizeEvent *) const;


    
signals:
    
public slots:
    
};

#endif // DOCKWIDGET_H
