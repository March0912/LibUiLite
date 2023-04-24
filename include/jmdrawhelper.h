#ifndef __JMDRAWHELPER_H__
#define __JMDRAWHELPER_H__

#include "jmuilite_global.h"
#include <QColor>

namespace JmSkin
{
	JMUILITE_EXPORT extern QColor getThemeColor(const QString& themeName, const QString& className, const QString& propName, const QColor& def = QColor());
	JMUILITE_EXPORT extern int getThemeHint(const QString& themeName, const QString& className, const QString& propName, int def = 0);
	JMUILITE_EXPORT extern int getThemeFontSize(const QString& themeName, const QString& className, const QString& propName, int def = 0);
	JMUILITE_EXPORT extern QString getThemeFontFamily(const QString& themeName, const QString& className, const QString& propName, const QString& def = QString());
};

#endif
