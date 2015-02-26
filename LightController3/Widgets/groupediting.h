#ifndef GROUPEDITING_H
#define GROUPEDITING_H

#include <QDialog>

namespace Ui {
class GroupEditing;
}

class GroupEditing : public QDialog
{
    Q_OBJECT

public:
    explicit GroupEditing(QWidget *parent = 0);
    ~GroupEditing();

private:
    Ui::GroupEditing *ui;
};

#endif // GROUPEDITING_H
