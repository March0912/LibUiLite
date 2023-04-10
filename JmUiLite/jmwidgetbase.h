#ifndef __JMWIDGETBASE_H__
#define __JMWIDGETBASE_H__

#include "jmshadowframebase.h"

class JMUILITE_EXPORT JmWidgetBase : public JmShadowFramebase
{
	Q_OBJECT
	using _BaseClass = JmShadowFramebase;

public:
	explicit JmWidgetBase(QWidget* parent = nullptr);
	virtual ~JmWidgetBase();

public:
	QWidget* centerWidget() const;
	QVBoxLayout* getMainLayout() const;

private:
	void initUI();
	virtual QWidget* createCenterWidget();

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	QWidget* m_pCenterWidget = nullptr;
	QVBoxLayout* m_pMainLayout = nullptr;
};

class DefaultCenterWidget : public QWidget
{
	Q_OBJECT
public:
	explicit DefaultCenterWidget(JmWidgetBase* parent = nullptr);
	~DefaultCenterWidget() = default;

protected:
	void paintEvent(QPaintEvent* event) override;

private:
	JmWidgetBase* m_pParent = nullptr;
};



#endif
