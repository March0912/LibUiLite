#include "jmwidgetbase.h"
#include <QPainter>
#include <QPainterPath>
#include <QColor>
#include <QRect>
#include <QStyleOption>
#include <qmath.h>
#include "jmdrawhelper.h"

namespace UiLite
{

	JmWidgetBase::JmWidgetBase(QWidget* parent /*= nullptr*/) : _BaseClass(parent)
	{
		this->setMinimumSize(800, 500);
		initUI();
	}

	JmWidgetBase::~JmWidgetBase()
	{

	}

	QWidget* JmWidgetBase::centerWidget() const
	{
		return m_pCenterWidget;
	}

	QVBoxLayout* JmWidgetBase::getMainLayout() const
	{
		return m_pMainLayout;
	}

	void JmWidgetBase::initUI()
	{
		m_pCenterWidget = createCenterWidget();
		layout()->addWidget(m_pCenterWidget);

		m_pMainLayout = new QVBoxLayout(m_pCenterWidget);
		m_pMainLayout->setContentsMargins(16, 16, 16, 16);
		m_pCenterWidget->setLayout(m_pMainLayout);
	}

	QWidget* JmWidgetBase::createCenterWidget()
	{
		QWidget* centerWidget = new DefaultCenterWidget(this);
		// 	centerWidget->setStyleSheet(QString("background: rgb(%1,%2,%3); border: 1px; border-radius:%4")
		// 			.arg(m_shadowColor.red()).arg(m_shadowColor.green()).arg(m_shadowColor.blue())
		// 			.arg(m_shadowWidth));
		return centerWidget;
	}

	void JmWidgetBase::paintEvent(QPaintEvent* event)
	{
		_BaseClass::paintEvent(event);
	}


	DefaultCenterWidget::DefaultCenterWidget(JmWidgetBase* parent/* = nullptr*/) : QWidget(parent)
	{
		m_pParent = parent;
	}

	void DefaultCenterWidget::paintEvent(QPaintEvent* event)
	{
		QPainter painter(this);
		painter.setRenderHint(QPainter::Antialiasing, true);

		QString theme = "dark";// JmSetting->isDarkTheme() ? "dark" : "light";

		QColor color = JmSkin::getThemeColor(theme, metaObject()->className(), "background", m_pParent ? m_pParent->getShadowColor() : QColor(51, 51, 51, 255));
		color.setAlpha(255);

		QBrush brush(color);
		painter.setBrush(brush);
		painter.setPen(Qt::NoPen);

		QPainterPath path;
		path.setFillRule(Qt::WindingFill);
		path.addRoundRect(rect(), m_pParent->getRoundness());
		painter.drawPath(path);

		painter.setRenderHint(QPainter::Antialiasing, false);
	}

}