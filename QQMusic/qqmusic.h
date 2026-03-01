#ifndef QQMUSIC_H
#define QQMUSIC_H

#include <QWidget>

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
private slots:
    void on_quit_clicked();

private:
    Ui::QQMusic *ui;
};
#endif // QQMUSIC_H
