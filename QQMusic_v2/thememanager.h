#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H

#include <QObject>
#include <QStringList>

class ThemeManager : public QObject
{
    Q_OBJECT
public:
    explicit ThemeManager(QObject *parent = nullptr);
    QStringList themes() const;
    QString currentTheme() const;
    bool apply(const QString &themeName);
    void applySaved();

signals:
    void themeChanged(const QString &themeName);

private:
    QString m_currentTheme;
};

#endif
