#ifndef __JMMOVEWIDGET_H__
#define __JMMOVEWIDGET_H__

#include "jmuilite_global.h"
#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QPaintEvent>
#include <QVBoxLayout>

class JMUILITE_EXPORT JmMoveWidget : public QWidget
{
	Q_OBJECT
public:
	explicit JmMoveWidget(QWidget* parent = nullptr);
	virtual ~JmMoveWidget() {}

public:
	QVBoxLayout* getMainLayout() const;

signals:
	void restoreWindow();
	void switchMaxOrNormal();

protected:
	void mousePressEvent(QMouseEvent* event) override;
	void mouseMoveEvent(QMouseEvent* event) override;
	void mouseReleaseEvent(QMouseEvent* event) override;
	void mouseDoubleClickEvent(QMouseEvent* event) override;
	void paintEvent(QPaintEvent* event) override;

protected:
	virtual bool inMoveableArea(const QPoint& pos);

private:
	QPoint m_point;
	QVBoxLayout* m_mainLayout{ nullptr };
	bool m_enableMove{ false };
	QWidget* m_parent = nullptr;
};

#endif
