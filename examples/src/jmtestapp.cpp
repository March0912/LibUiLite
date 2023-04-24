#include "jmtestapp.h"
#include <QKeyEvent>

JmTestApp::JmTestApp(QWidget *parent)
    : JmWidgetBase(parent)
{
   // ui.setupUi(this);

    setFixedSize(1000, 800);
}

void JmTestApp::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape)
    {
        close();
    }
}
