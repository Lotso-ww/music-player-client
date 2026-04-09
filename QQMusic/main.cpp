#include "qqmusic.h"
#include <QMessageBox>
#include <QSharedMemory>
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

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
    shareMemory.create(1); // 我们并不是真的需要创建一块共享内存,只需要可以达到我们的目的就行了
    QQMusic w;
    w.show();
    return a.exec();
}
