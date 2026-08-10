#include "qqmusic.h"
#include <QMessageBox>
#include <QSharedMemory>
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFile>
#include <QSettings>
#include <QStandardPaths>

namespace {
void configureProjectIdentity(QApplication &application)
{
    const QString legacyDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    QSettings legacySettings;
    const QVariant legacyTheme = legacySettings.value(QStringLiteral("appearance/theme"));

    application.setOrganizationName(QStringLiteral("QQMusicProject"));
    application.setOrganizationDomain(QStringLiteral("qqmusic-project.local"));
    application.setApplicationName(QStringLiteral("QQMusicProject"));

    const QString projectDataPath = QStandardPaths::writableLocation(QStandardPaths::AppDataLocation);
    const QString projectDatabase = QDir(projectDataPath).filePath(QStringLiteral("QQMusic.db"));
    const QString legacyDatabase = QDir(legacyDataPath).filePath(QStringLiteral("QQMusic.db"));
    if (!QFileInfo::exists(projectDatabase) && QFileInfo::exists(legacyDatabase)) {
        QDir().mkpath(projectDataPath);
        if (!QFile::copy(legacyDatabase, projectDatabase))
            qWarning() << "Legacy database migration failed:" << legacyDatabase;
    }

    QSettings projectSettings;
    if (!projectSettings.contains(QStringLiteral("appearance/theme")) && legacyTheme.isValid())
        projectSettings.setValue(QStringLiteral("appearance/theme"), legacyTheme);
}
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    configureProjectIdentity(a);

    // 创建共享内存
    QSharedMemory shareMemory("QQMusic");

    // 当程序第一次运行时,由于共享内存还没创建出来,所以一定会失败
    // 当程序第二次运行时,由于共享内存已经被前一次运行的时候申请好,所以第二次一定会成功
    // 由于只能运行一定实例,所以我们直接让第二个实例直接退出即可.
    if(shareMemory.attach())
    {
        QMessageBox::information(nullptr, "QQMusic提示", "QQMusic已经在运行");
        return 0;
    }
    if(!shareMemory.create(1))
    {
        qCritical() << "单实例共享内存初始化失败:" << shareMemory.errorString();
        QMessageBox::critical(nullptr, "QQMusic提示", "无法初始化单实例控制：" + shareMemory.errorString());
        return 1;
    }
    QQMusic w;
    w.show();
    return a.exec();
}
