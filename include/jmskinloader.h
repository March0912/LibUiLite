#ifndef __JMSKINLOADER_H__
#define __JMSKINLOADER_H__

#include "jmuilite_global.h"
#include <QObject>
#include <QHash>
#include <QMultiHash>
#include <QColor>
#include <QFont>
#include <QVariant>

struct Styles
{
	enum Type { color, hint, fontSize, fontFamily };

	/// <summary>
	/// propty-value
	/// </summary>
	using PropList = QHash<QString, QVariant>;

	/// <summary>
	/// type-value
	/// </summary>
	using StyleList = QHash<Type, PropList>;
	StyleList m_propValues;
};

class JmSkinTheme
{
public:
	JmSkinTheme(const QString& themeName = QString()) : m_themeName(themeName) {}
	~JmSkinTheme() = default;

	QString getName() const
	{
		return m_themeName;
	}

	void addColor(const QString& className, const QString& propName, const QColor& color);
	QColor getColor(const QString& className, const QString& propName, const QColor& def = QColor());

	void addHint(const QString& className, const QString& propName, int hint);
	int getHint(const QString& className, const QString& propName, int def = 0);

	void addFontSize(const QString& className, const QString& propName, int size);
	int getFontSize(const QString& className, const QString& propName, int def = 0);

	void addFontFamily(const QString& className, const QString& propName, const QString& family);
	QString getFontFamily(const QString& className, const QString& propName, const QString& def = QString());

private:
	bool _check(Styles::Type type, const QString& className, const QString& propName);

private:
	QString m_themeName;

	/// <summary>
	/// className-Styles
	/// </summary>
	QHash<QString, Styles> m_styleList;
};

class JmThemeLoader : public QObject
{
	Q_OBJECT
public:
	static JmThemeLoader* getInstance();

public:
	QColor getThemeColor(const QString& themeName, const QString& className, const QString& prop, const QColor& def = QColor());
	int getThemeHint(const QString& themeName, const QString& className, const QString& prop, int def = 0);
	int getThemeFontSize(const QString& themeName, const QString& className, const QString& propName, int def = 0);
	QString getThemeFontFamily(const QString& themeName, const QString& className, const QString& propName, const QString& def = QString());

private:
	JmThemeLoader() = default;
	~JmThemeLoader();

	void setupSkinFile(const QString& xml);

private:
	static JmThemeLoader* m_pInstance;
	QString m_resourcePath;
	QHash<QString, JmSkinTheme*> m_skins;
};


#endif
