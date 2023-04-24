#pragma once

#include <QtWidgets/QWidget>
#include "jmwidgetbase.h"

class QKeyEvent;

class JmTestApp : public JmWidgetBase
{
    Q_OBJECT
	using _BaseClass = JmWidgetBase;

public:
    JmTestApp(QWidget *parent = Q_NULLPTR);

protected:
    void keyPressEvent(QKeyEvent* event) override;
};
