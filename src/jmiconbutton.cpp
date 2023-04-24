#include "jmiconbutton.h"

namespace UiLite 
{

	JmIconButton::JmIconButton(QWidget* parent /*= nullptr*/) : QAbstractButton(parent)
	{

	}

	JmIconButton::~JmIconButton()
	{

	}

	JmIconButton::IconPosition JmIconButton::iconPosition() const
	{
		return m_iconPosition;
	}

	void JmIconButton::setIconPosition(IconPosition position)
	{
		m_iconPosition = position;
	}

	JmIconButton::ArrowPosition JmIconButton::arrowPosition() const
	{
		return m_arrowPosition;
	}
	void JmIconButton::setArrowPosition(ArrowPosition position)
	{
		m_arrowPosition = position;
	}

	Qt::Alignment JmIconButton::alignment() const
	{
		return m_alignment;
	}

	void JmIconButton::setAlignment(Qt::Alignment align)
	{
		m_alignment = align;
	}

	int JmIconButton::borderRadius() const
	{
		return m_borderRadius;
	}

	void JmIconButton::setBorderRadius(int borderRadius)
	{
		m_borderRadius = borderRadius;
	}
}