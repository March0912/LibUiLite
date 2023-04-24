#include "jmdrawhelper.h"
#include "jmskinloader.h"

namespace JmSkin
{
	QColor getThemeColor(const QString& themeName, const QString& className, const QString& propName, const QColor& def/* = QColor()*/)
	{
		return JmThemeLoader::getInstance()->getThemeColor(themeName, className, propName, def);
	}

	int getThemeHint(const QString& themeName, const QString& className, const QString& propName, int def/* = 0*/)
	{
		return JmThemeLoader::getInstance()->getThemeHint(themeName, className, propName, def);
	}

	int getThemeFontSize(const QString& themeName, const QString& className, const QString& propName, int def/* = 0*/)
	{
		return JmThemeLoader::getInstance()->getThemeFontSize(themeName, className, propName, def);
	}

	QString getThemeFontFamily(const QString& themeName, const QString& className, const QString& propName, const QString& def/* = QString()*/)
	{
		return JmThemeLoader::getInstance()->getThemeFontFamily(themeName, className, propName, def);
	}
}