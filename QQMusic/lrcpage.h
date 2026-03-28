#ifndef LRCPAGE_H
#define LRCPAGE_H

#include <QWidget>

namespace Ui {
class LrcPage;
}

class LrcPage : public QWidget
{
    Q_OBJECT

public:
    explicit LrcPage(QWidget *parent = nullptr);
    ~LrcPage();

private:
    Ui::LrcPage *ui;
};

#endif // LRCPAGE_H
