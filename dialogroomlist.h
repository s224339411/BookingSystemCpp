#ifndef DIALOGROOMLIST_H
#define DIALOGROOMLIST_H

#include <QDialog>
#include <vector>
#include "room.h"

namespace Ui {
class DialogRoomList;
}

class DialogRoomList : public QDialog
{
    Q_OBJECT

public:
    explicit DialogRoomList(QWidget *parent = nullptr);
    ~DialogRoomList();

private:
    Ui::DialogRoomList *ui;
    std::vector<room> rooms;
};

#endif // DIALOGROOMLIST_H
