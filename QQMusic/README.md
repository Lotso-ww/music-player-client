# QQMusic P0 基线

## 构建

使用 Qt 5.14.2、C++11 和 qmake。Windows 下使用 Qt 自带的 MinGW 7.3 工具链：

```text
$env:PATH = "D:\\QT5\\Tools\\mingw730_64\\bin;D:\\QT5\\5.14.2\\mingw73_64\\bin;$env:PATH"
qmake QQMusic.pro CONFIG+=debug
mingw32-make -f Makefile -j2
qmake p0-tests.pro CONFIG+=debug
mingw32-make -f Makefile -j2
test-build\\bin\\qqmusic_tests.exe
```

本机已配置 Qt 时，可直接自动执行 Debug 构建和 P0 测试：

```powershell
powershell -NoProfile -ExecutionPolicy Bypass -File .\scripts\verify-p0.ps1
```

脚本固定使用 `D:\QT5\5.14.2\mingw73_64` 与 `D:\QT5\Tools\mingw730_64`，不要混用系统 MinGW 12.x。

Release 构建将 `CONFIG+=debug` 替换为 `CONFIG+=release`。应用数据库位于 Qt `QStandardPaths::AppDataLocation` 对应目录，不写入工作目录。

## 日志规范

使用 `qDebug()` 记录开发诊断，使用 `qWarning()` 记录可恢复异常，使用 `qCritical()` 记录数据库、单实例和持久化失败。日志不得包含密码、token 或完整授权头。

## P0 验收

自动化回归位于 `tests/`；播放列表、托盘退出、Alt+F4、损坏媒体和无歌词切歌还需按 `docs/reviews/` 中的手工记录执行。
