#ifndef __JMSHADOWFRAMEBASE_H__
#define __JMSHADOWFRAMEBASE_H__

#include "jmmovewidget.h"
#include <QColor>
#include <QRect>

namespace UiLite 
{

	class JMUILITE_EXPORT JmShadowFramebase : public JmMoveWidget
	{
		Q_OBJECT
			using _BaseClass = JmMoveWidget;

	public:
		explicit JmShadowFramebase(QWidget* parent = nullptr);
		~JmShadowFramebase() = default;

	public:
		void setShadowWidth(int width);
		int getShadowWidth() const;

		void setShadowColor(const QColor& color);
		QColor getShadowColor() const;

		void setRoundness(int roundness);
		int getRoundness() const;

		QRect leftShadowRect() const;
		QRect rightShadowRect() const;
		QRect topShadowRect() const;
		QRect bottomShadowRect() const;

		bool ptInShadow(QPoint pt) const;

	private:
		void initUI();

	protected:
		int m_shadowWidth = 8;
		QColor m_shadowColor = QColor(45, 45, 45, 50);
		int m_roundness = 8;

	protected:
		void paintEvent(QPaintEvent* event) override;
	};

}

#endif // __JMSHADOWFRAMEBASE_H__
