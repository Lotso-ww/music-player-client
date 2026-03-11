#ifndef RECBOX_H
#define RECBOX_H

#include <QWidget>
#include <QJsonArray>

namespace Ui {
class RecBox;
}

class RecBox : public QWidget
{
    Q_OBJECT

public:
    explicit RecBox(QWidget *parent = nullptr);
    ~RecBox();

    // 初始化
    void initRecBoxUi(QJsonArray data, int row);
    void createRecItem();

private slots:
    void on_btDown_clicked();

    void on_btUp_clicked();

private:
    Ui::RecBox *ui;
    int row; // 记录当前RecBox实际总⾏数
    int col; // 记录当前RecBox实际每行有几个元素

    int currentIndex; // 标记当先显⽰第⼏组图⽚和推荐信息
    int count; // 标记imageList中元素按照col分组总数

    QJsonArray imageList; // 保存界⾯上的图⽚, ⾥⾯实际为key、value键值对
};

#endif // RECBOX_H
