#include "thememanager.h"
#include <QApplication>
#include <QSettings>
#include <QSet>
#include <QWidget>

namespace {
void setThemeOverride(QWidget *widget, const QString &rule)
{
    static const char originalStyleProperty[] = "themeOriginalStyle";
    if (!widget->property(originalStyleProperty).isValid())
        widget->setProperty(originalStyleProperty, widget->styleSheet());
    widget->setStyleSheet(widget->property(originalStyleProperty).toString() + rule);
}

void applyWidgetOverrides(const QString &themeName)
{
    const bool dark = themeName == QStringLiteral("dark");
    const QString mainSurface = dark ? QStringLiteral("#292a2d") : QStringLiteral("#f5f5f5");
    const QString sideSurface = dark ? QStringLiteral("#242528") : QStringLiteral("#f0f0f0");
    const QString inputSurface = dark ? QStringLiteral("#3a3b3f") : QStringLiteral("#e3e3e3");
    const QString text = dark ? QStringLiteral("#eeeeee") : QStringLiteral("#202124");

    const QSet<QString> sidePanels = QSet<QString>() << QStringLiteral("headLeft") << QStringLiteral("bodyLeft");
    const QSet<QString> mainPanels = QSet<QString>() << QStringLiteral("head")
        << QStringLiteral("headRight") << QStringLiteral("bodyRight")
        << QStringLiteral("musicPlayBox") << QStringLiteral("listLabelBox") << QStringLiteral("controlBox")
        << QStringLiteral("CommonPage") << QStringLiteral("recPage") << QStringLiteral("musicpage")
        << QStringLiteral("radioPage") << QStringLiteral("scrollAreaWidgetContents");

    const QWidgetList widgets = qApp ? qApp->allWidgets() : QWidgetList();
    for (QWidget *widget : widgets) {
        if (!widget) continue;
        const QString name = widget->objectName();
        if (name == QStringLiteral("background")) {
            setThemeOverride(widget, QStringLiteral(
                "\n#background { background-color:%1; color:%2; }"
                "#background QLabel, #background QPushButton { color:%2; }").arg(mainSurface, text));
        } else if (sidePanels.contains(name)) {
            setThemeOverride(widget, QStringLiteral("\n#%1 { background-color:%2; color:%3; }").arg(name, sideSurface, text));
        } else if (mainPanels.contains(name)) {
            setThemeOverride(widget, QStringLiteral("\n#%1 { background-color:%2; color:%3; }").arg(name, mainSurface, text));
        } else if (name == QStringLiteral("lineEdit")) {
            setThemeOverride(widget, QStringLiteral("\n#lineEdit { background-color:%1; color:%2; }").arg(inputSurface, text));
        } else if (name == QStringLiteral("pageMusicList")) {
            const QString selected = dark ? QStringLiteral("#3a3b3f") : QStringLiteral("#efefef");
            const QString scroll = dark ? QStringLiteral("#292a2d") : QStringLiteral("#ffffff");
            const QString handle = dark ? QStringLiteral("#55575c") : QStringLiteral("#e3e3e3");
            setThemeOverride(widget, QStringLiteral(
                "\n#pageMusicList { background-color:%1; color:%2; border:none; }"
                "#pageMusicList::item:selected { background-color:%3; }"
                "QScrollBar:vertical { background-color:%4; }"
                "QScrollBar::handle:vertical { background-color:%5; }")
                .arg(mainSurface, text, selected, scroll, handle));
        } else if (name == QStringLiteral("playAllBtn")) {
            const QString button = dark ? QStringLiteral("#3a3b3f") : QStringLiteral("#e3e3e3");
            const QString hover = dark ? QStringLiteral("#1a9b75") : QStringLiteral("#1ecd97");
            setThemeOverride(widget, QStringLiteral(
                "\n#playAllBtn { background-color:%1; color:%2; }"
                "#playAllBtn:hover { background-color:%3; }").arg(button, text, hover));
        } else if (name == QStringLiteral("volumeWidget")) {
            setThemeOverride(widget, QStringLiteral("\n#volumeWidget { background-color:%1; color:%2; }").arg(mainSurface, text));
        } else if (name == QStringLiteral("silenceBtn")) {
            const QString hover = dark ? QStringLiteral("#3a3b3f") : QStringLiteral("#e0e0e0");
            setThemeOverride(widget, QStringLiteral("\n#silenceBtn:hover { background-color:%1; }").arg(hover));
        } else if (name == QStringLiteral("inSlider")) {
            const QString track = dark ? QStringLiteral("#55575c") : QStringLiteral("#ececec");
            setThemeOverride(widget, QStringLiteral("\n#inSlider { background-color:%1; }").arg(track));
        }
    }
}
}

ThemeManager::ThemeManager(QObject *parent) : QObject(parent)
{
    m_currentTheme = QStringLiteral("default");
}

QStringList ThemeManager::themes() const
{
    return QStringList() << QStringLiteral("default") << QStringLiteral("dark");
}

QString ThemeManager::currentTheme() const { return m_currentTheme; }

void ThemeManager::applySaved()
{
    QSettings settings;
    const QString saved = settings.value(QStringLiteral("appearance/theme"), QStringLiteral("default")).toString();
    apply(themes().contains(saved) ? saved : QStringLiteral("default"));
}

bool ThemeManager::apply(const QString &themeName)
{
    if (!themes().contains(themeName)) return false;
    m_currentTheme = themeName;
    QSettings settings;
    settings.setValue(QStringLiteral("appearance/theme"), themeName);
    if (qApp) {
        qApp->setProperty("darkTheme", themeName == QStringLiteral("dark"));
        applyWidgetOverrides(themeName);
    }
    emit themeChanged(themeName);
    return true;
}
