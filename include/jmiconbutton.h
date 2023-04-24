#ifndef __JMICONBUTTON_H__
#define __JMICONBUTTON_H__

#include "jmuilite_global.h"
#include <QAbstractButton>

namespace UiLite
{
	class JmIconButtonPrivate;
	/// <summary>
	/// ´øÍ¼±êµÄbutton
	/// </summary>
	class JMUILITE_EXPORT JmIconButton : QAbstractButton
	{
		Q_OBJECT

	public:
		explicit JmIconButton(QWidget* parent = nullptr);
		~JmIconButton();

	public:
		enum IconPosition
		{
			OnTextLeft,
			OnTextRight,
			OnTextTop,
		};
		enum ArrowPosition
		{
			ArrowOnLeft,
			ArrowOnRight,
		};

	public:
		IconPosition iconPosition() const;
		void setIconPosition(IconPosition position);

		ArrowPosition arrowPosition() const;
		void setArrowPosition(ArrowPosition position);

		Qt::Alignment alignment() const;
		void setAlignment(Qt::Alignment align);

		int borderRadius() const;
		void setBorderRadius(int borderRadius);

	protected:
		IconPosition m_iconPosition = OnTextLeft;
		ArrowPosition m_arrowPosition = ArrowOnRight;
		Qt::Alignment m_alignment = Qt::AlignCenter;
		int m_borderRadius = 8;

	private:

	};
}

#endif
