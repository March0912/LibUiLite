#include "jmmovewidget.h"
#include <QPainterPath>
#include <QPainter>
#include <QColor>
#include <QtMath>
#include <QPen>
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>

namespace UiLite
{
	JmMoveWidget::JmMoveWidget(QWidget* parent /*= nullptr*/) : QWidget(parent)
	{
		m_parent = parent;
		setWindowFlag(Qt::FramelessWindowHint, true);
	}

	QVBoxLayout* JmMoveWidget::getMainLayout() const
	{
		return m_mainLayout;
	}

	void JmMoveWidget::mousePressEvent(QMouseEvent* event)
	{
		if (QEvent::MouseButtonPress == event->type() && Qt::LeftButton == event->button()) {
			m_point = event->pos();
			m_enableMove = inMoveableArea(m_point);
		}
		QWidget::mousePressEvent(event);
	}


	void JmMoveWidget::mouseMoveEvent(QMouseEvent* event)
	{
		if (QEvent::MouseMove == event->type() && event->buttons() & Qt::LeftButton) {
			if (!m_enableMove) {
				return;
			}

			QRect availableRect = QApplication::desktop()->availableGeometry(this);
			if (availableRect.width() > this->width() || availableRect.height() > this->height())
			{
				QPoint pt = this->pos() + event->pos() - m_point;

				if (this->parentWidget() == nullptr) {
					QRect desktopRct = QApplication::desktop()->screenGeometry(this);
					int x = qBound(0 - this->width() / 2, pt.x(), desktopRct.width() - this->width() / 2);
					int y = qBound(0 - this->height() / 2, pt.y(), desktopRct.height() - this->height() / 2);
					pt = QPoint(x, y);
				}
				else {
					QRect rect = this->parentWidget()->geometry();
					int x = qBound(0 - this->width() / 2, pt.x(), rect.width() - this->width() / 2);
					int y = qBound(0, pt.y(), rect.height() - this->height());
					pt = QPoint(x, y);
				}
				this->move(pt);

				//可能有残影，父窗口update能避免
				if (m_parent != nullptr) {
					m_parent->update();
				}
			}
		}
		QWidget::mouseMoveEvent(event);
	}

	void JmMoveWidget::mouseReleaseEvent(QMouseEvent* event)
	{
		m_enableMove = false;
		QWidget::mouseReleaseEvent(event);
	}

	void JmMoveWidget::mouseDoubleClickEvent(QMouseEvent* event)
	{
		if (QEvent::MouseButtonDblClick == event->type() && Qt::LeftButton == event->button()) {
			emit switchMaxOrNormal();
			setCursor(Qt::ArrowCursor);
		}
		QWidget::mouseDoubleClickEvent(event);
	}

	void JmMoveWidget::paintEvent(QPaintEvent* event)
	{
		QWidget::paintEvent(event);
	}

	bool JmMoveWidget::inMoveableArea(const QPoint& pos)
	{
		Q_UNUSED(pos);
		return true;
	}

}