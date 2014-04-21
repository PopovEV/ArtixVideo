#include "dockwidget.h"

DockWidget::DockWidget(QWidget *parent, const QString &title, Qt::WFlags flags) :
    QDockWidget(parent)
{
    setWindowTitle(title);
}

DockWidget::~DockWidget()
{
}

QSize DockWidget::sizeHint() const
{
//    QSize sh = QDockWidget::sizeHint();
//    sh.setWidth(500);
//    sh.setHeight(500);

//    return sh;
}

void DockWidget::resizeEvent(QResizeEvent *) const
{

}
