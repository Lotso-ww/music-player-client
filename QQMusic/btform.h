#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>

namespace Ui {
class btForm;
}

class btForm : public QWidget
{
    Q_OBJECT

public:
    explicit btForm(QWidget *parent = nullptr);
    ~btForm();

    void setIconAndText(const QString& btIconUrl, const QString& btText);

private:
    Ui::btForm *ui;
};

#endif // BTFORM_H
