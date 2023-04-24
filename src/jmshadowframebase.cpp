#include "jmshadowframebase.h"
#include "jmdrawhelper.h"
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QRect>
#include <QStyleOption>
#include <qmath.h>

namespace UiLite
{
	JmShadowFramebase::JmShadowFramebase(QWidget* parent /*= nullptr*/) : _BaseClass(parent)
	{
		setWindowFlag(Qt::FramelessWindowHint);
		this->setAttribute(Qt::WA_TranslucentBackground);

		QString theme = "dark";// JmSetting->isDarkTheme() ? "dark" : "light";
		m_shadowColor = JmSkin::getThemeColor(theme, metaObject()->className(), "shadow", m_shadowColor);
		m_shadowWidth = JmSkin::getThemeHint(theme, metaObject()->className(), "shadowWidth", m_shadowWidth);
		m_roundness = JmSkin::getThemeHint(theme, metaObject()->className(), "roundness", m_roundness);

		initUI();
	}

	void JmShadowFramebase::setRoundness(int roundness)
	{
		m_roundness = roundness;
	}

	int JmShadowFramebase::getRoundness() const
	{
		return m_roundness;
	}

	QRect JmShadowFramebase::leftShadowRect() const
	{
		QRect rct = QRect(0, 0, m_shadowWidth, this->height());
		return rct;
	}

	QRect JmShadowFramebase::rightShadowRect() const
	{
		QRect rct = QRect(this->width() - m_shadowWidth, 0, this->width(), this->height());
		return rct;
	}

	QRect JmShadowFramebase::topShadowRect() const
	{
		QRect rct = QRect(0, 0, this->width(), m_shadowWidth);
		return rct;
	}

	QRect JmShadowFramebase::bottomShadowRect() const
	{
		QRect rct = QRect(0, this->height() - m_shadowWidth, this->width(), this->height());
		return rct;
	}

	bool JmShadowFramebase::ptInShadow(QPoint pt) const
	{
		return leftShadowRect().contains(pt) || rightShadowRect().contains(pt) || topShadowRect().contains(pt) || bottomShadowRect().contains(pt);
	}

	void JmShadowFramebase::initUI()
	{
		QVBoxLayout* mainLayout = new QVBoxLayout(this);
		mainLayout->setContentsMargins(m_shadowWidth, m_shadowWidth, m_shadowWidth, m_shadowWidth);
		mainLayout->setSpacing(0);

		setLayout(mainLayout);
	}

	void JmShadowFramebase::setShadowWidth(int width)
	{
		m_shadowWidth = width;
	}

	int JmShadowFramebase::getShadowWidth() const
	{
		return m_shadowWidth;
	}

	void JmShadowFramebase::setShadowColor(const QColor& color)
	{
		m_shadowColor = color;
	}

	QColor JmShadowFramebase::getShadowColor() const
	{
		return m_shadowColor;
	}

	void JmShadowFramebase::paintEvent(QPaintEvent* event)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);

		QColor color = m_shadowColor;

		for (int i = 0; i < m_shadowWidth; i++)
		{
			QRect rect(m_shadowWidth - i, m_shadowWidth - i, this->width() - (m_shadowWidth - i) * 2, this->height() - (m_shadowWidth - i) * 2);

			QPainterPath path;
			path.setFillRule(Qt::WindingFill);
			path.addRoundRect(rect, m_roundness);
			color.setAlpha(150 - qSqrt(i) * 50);
			painter.setPen(color);
			painter.drawPath(path);
		}
		painter.setRenderHint(QPainter::Antialiasing, false);
	}

}