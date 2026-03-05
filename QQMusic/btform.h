#ifndef BTFORM_H
#define BTFORM_H

#include <QWidget>
#include <QPropertyAnimation>

namespace Ui {
class btForm;
}

class btForm : public QWidget
{
    Q_OBJECT

public:
    explicit btForm(QWidget *parent = nullptr);
    ~btForm();

    void setIconAndText(const QString& btIconUrl, const QString& btText, int pageId);
    int getPageId()const;
    void clearBg();
protected:
    void mousePressEvent(QMouseEvent *event);
signals:
    void btClick(int id);
private:
    Ui::btForm *ui;
    int pageId;

    QPropertyAnimation* line1Animat;
    QPropertyAnimation* line2Animat;
    QPropertyAnimation* line3Animat;
    QPropertyAnimation* line4Animat;
};

#endif // BTFORM_H
