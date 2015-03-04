#ifndef FIXTUREMAINTIMINGUI_H
#define FIXTUREMAINTIMINGUI_H

#include <QWidget>
#include <QString>
#include <QList>
#include <QMenu>

namespace Ui {
class FixtureMainTimingUI;
}

class FixtureMainTimingUI : public QWidget
{
    Q_OBJECT

public:
    explicit FixtureMainTimingUI(QWidget *parent = 0);
    ~FixtureMainTimingUI();

    void setFixtureName(QString name);
    void addFaderNames(QList<QString> name);

private:
    Ui::FixtureMainTimingUI *ui;
    QMenu *m_btnMenu;
};

#endif // FIXTUREMAINTIMINGUI_H