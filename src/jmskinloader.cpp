#include "jmskinloader.h"

#include <QFile>
#include <QtXml>
#include <QDomDocument>
#include <QApplication>

void JmSkinTheme::addColor(const QString& className, const QString& propName, const QColor& color)
{
	if (className.isEmpty() || propName.isEmpty())
		return;

	if (m_styleList.contains(className))
	{
		Styles& styles = m_styleList[className];
		styles.m_propValues[Styles::color][propName] = color;
	}
	else
	{
		Styles styles;
		styles.m_propValues[Styles::color][propName] = color;
		m_styleList[className] = styles;
	}
}

QColor JmSkinTheme::getColor(const QString& className, const QString& propName, const QColor& def /*= QColor()*/)
{
	if (!_check(Styles::color, className, propName))
		return def;

	auto styles = m_styleList[className];
	auto propValues = styles.m_propValues[Styles::color];
	QString colorStr = propValues[propName].toString();
	if (!QColor::isValidColor(colorStr))
		return def;
	return QColor(colorStr);
}

void JmSkinTheme::addHint(const QString& className, const QString& propName, int hint)
{
	if (className.isEmpty() || propName.isEmpty())
		return;

	if (m_styleList.contains(className))
	{
		Styles& styles = m_styleList[className];
		styles.m_propValues[Styles::hint][propName] = hint;
	}
	else
	{
		Styles styles;
		styles.m_propValues[Styles::hint][propName] = hint;
		m_styleList[className] = styles;
	}
}

int JmSkinTheme::getHint(const QString& className, const QString& propName, int def /*= 0*/)
{
	if (!_check(Styles::hint, className, propName))
		return def;

	auto styles = m_styleList[className];
	auto propValues = styles.m_propValues[Styles::hint];

	return propValues[propName].toInt();
}

void JmSkinTheme::addFontSize(const QString& className, const QString& propName, int size)
{
	if (className.isEmpty() || propName.isEmpty())
		return;

	if (m_styleList.contains(className))
	{
		Styles& styles = m_styleList[className];
		styles.m_propValues[Styles::fontSize][propName] = size;
	}
	else
	{
		Styles styles;
		styles.m_propValues[Styles::fontSize][propName] = size;
		m_styleList[className] = styles;
	}
}

QString JmSkinTheme::getFontFamily(const QString& className, const QString& propName, const QString& def /*= QString()*/)
{
	if (!_check(Styles::fontFamily, className, propName))
		return def;

	auto styles = m_styleList[className];
	auto propValues = styles.m_propValues[Styles::fontFamily];
	return propValues[propName].toString();
}

int JmSkinTheme::getFontSize(const QString& className, const QString& propName, int def/* = 0*/)
{
	if (!_check(Styles::fontSize, className, propName))
		return def;

	auto styles = m_styleList[className];
	auto propValues = styles.m_propValues[Styles::fontSize];
	return propValues[propName].toInt();
}

void JmSkinTheme::addFontFamily(const QString& className, const QString& propName, const QString& family)
{
	if (className.isEmpty() || propName.isEmpty())
		return;

	if (m_styleList.contains(className))
	{
		Styles& styles = m_styleList[className];
		styles.m_propValues[Styles::fontFamily][propName] = family;
	}
	else
	{
		Styles styles;
		styles.m_propValues[Styles::fontFamily][propName] = family;
		m_styleList[className] = styles;
	}
}

bool JmSkinTheme::_check(Styles::Type type, const QString& className, const QString& propName)
{
	if (!m_styleList.contains(className))
		return false;

	auto styles = m_styleList[className];
	if (!styles.m_propValues.contains(type))
		return false;

	if (!styles.m_propValues.contains(type))
		return false;

	return true;
}

////////////////////////////////////////////////////////////

JmThemeLoader* JmThemeLoader::m_pInstance = nullptr;

JmThemeLoader::~JmThemeLoader()
{
	for (auto itr = m_skins.begin();
		itr != m_skins.end();
		itr++)
	{
		delete itr.value();
	}
	m_skins.reserve(0);
}

JmThemeLoader* JmThemeLoader::getInstance()
{
	if (!m_pInstance)
	{
		QString skFilePath = QString("%1/Config/theme/jmtheme.sk").arg(qApp->applicationDirPath());
		m_pInstance = new JmThemeLoader();
		m_pInstance->setupSkinFile(skFilePath);
	}
	return m_pInstance;
}

QColor JmThemeLoader::getThemeColor(const QString& themeName, const QString& className, const QString& prop, const QColor& def /*= QColor()*/)
{
	if (m_skins.contains(themeName))
	{
		return m_skins[themeName]->getColor(className, prop, def);
	}
	else
		return def;
}

int JmThemeLoader::getThemeHint(const QString& themeName, const QString& className, const QString& propName, int def /*= 0*/)
{
	if (m_skins.contains(themeName))
	{
		return m_skins[themeName]->getHint(className, propName, def);
	}
	else
		return def;
}

int JmThemeLoader::getThemeFontSize(const QString& themeName, const QString& className, const QString& propName, int def /*= 0*/)
{
	if (m_skins.contains(themeName))
	{
		return m_skins[themeName]->getFontSize(className, propName, def);
	}
	else
		return def;
}

QString JmThemeLoader::getThemeFontFamily(const QString& themeName, const QString& className, const QString& propName, const QString& def /*= QString()*/)
{
	if (m_skins.contains(themeName))
	{
		return m_skins[themeName]->getFontFamily(className, propName, def);
	}
	else
		return def;
}

void JmThemeLoader::setupSkinFile(const QString& xml)
{
	QFile xmlfile(xml);
	if (!(xmlfile.open(QFile::ReadOnly)))
	{
		printf("read skin file failed.\n");
		return;
	}

	QDomDocument doc;
	QString msg;
	if (!doc.setContent(&xmlfile, &msg))
	{
		xmlfile.close();
		return;
	}

	QDomElement root = doc.documentElement();
	if (root.isNull()) {
		qDebug() << "parse *.sk file failed.\n";
		xmlfile.close();
		return;
	}

	QDomElement resNode = root.firstChildElement("resource");
	if (!resNode.isNull())
	{
		m_resourcePath = resNode.attribute("relativePath");
	}

	QDomElement themeNode = root.firstChildElement("theme");
	while (!themeNode.isNull())
	{
		QString themeName = "defaultTheme";
		if (themeNode.hasAttribute("name"))
		{
			themeName = themeNode.attribute("name");
		}

		JmSkinTheme* pTheme = new JmSkinTheme(themeName);
		auto styleNode = themeNode.firstChildElement("style");
		while (!styleNode.isNull())
		{
			QString className = styleNode.attribute("class");

			auto propNode = styleNode.firstChildElement("");
			while (!propNode.isNull())
			{
				if (propNode.nodeName() == "color")
				{
					QString propName = propNode.attribute("name");
					QColor colorValue = QColor(propNode.attribute("value"));
					pTheme->addColor(className, propName, colorValue);
				}
				else if (propNode.nodeName() == "hint")
				{
					QString propName = propNode.attribute("name");
					int hintValue = propNode.attribute("value").toInt();
					pTheme->addHint(className, propName, hintValue);
				}
				else if (propNode.nodeName() == "fontSize")
				{
					QString propName = propNode.attribute("name");
					int fontSizeValue = propNode.attribute("value").toInt();
					pTheme->addFontSize(className, propName, fontSizeValue);
				}
				else if (propNode.nodeName() == "fontFamily")
				{
					QString propName = propNode.attribute("name");
					QString fontFamilyValue = propNode.attribute("value");
					pTheme->addFontFamily(className, propName, fontFamilyValue);
				}
				propNode = propNode.nextSiblingElement();
			}
			styleNode = styleNode.nextSiblingElement();
		}

		if (!m_skins.contains(themeName))
		{
			m_skins[themeName] = pTheme;
		}
		themeNode = themeNode.nextSiblingElement();
	}
	xmlfile.close();
}
