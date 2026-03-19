#ifndef QQMUSIC_H
#define QQMUSIC_H

#include <QWidget>
#include "volumetool.h"

QT_BEGIN_NAMESPACE
namespace Ui { class QQMusic; }
QT_END_NAMESPACE

class QQMusic : public QWidget
{
    Q_OBJECT

public:
    QQMusic(QWidget *parent = nullptr);
    ~QQMusic();

    void initUI();
    void connectSignalAndSlots();
    QJsonArray randomPicture();
private slots:
    void on_quit_clicked();
    void on_btForm_clicked(int pageId);
    void on_volume_clicked();

    void on_addLocal_clicked();

protected:
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

private:
    Ui::QQMusic *ui;
    QPoint dragPosition;
    VolumeTool *volumeTool;
};
#endif // QQMUSIC_H
