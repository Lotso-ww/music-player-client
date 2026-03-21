#ifndef LISTITEMBOX_H
#define LISTITEMBOX_H

#include <QWidget>

namespace Ui {
class ListItemBox;
}

class ListItemBox : public QWidget
{
    Q_OBJECT

public:
    explicit ListItemBox(QWidget *parent = nullptr);
    ~ListItemBox();

    void setMusicName(const QString& musicName);
    void setMusicSinger(const QString& musicSinger);
    void setMusicAlbum(const QString& musicAlbum);
protected:
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
private:
    Ui::ListItemBox *ui;
};

#endif // LISTITEMBOX_H
