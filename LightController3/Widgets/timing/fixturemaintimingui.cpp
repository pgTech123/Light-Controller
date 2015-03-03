#include "fixturemaintimingui.h"
#include "ui_fixturemaintimingui.h"

FixtureMainTimingUI::FixtureMainTimingUI(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FixtureMainTimingUI)
{
    ui->setupUi(this);
    this->setLayout(ui->horizontalLayout);
    this->setFixedHeight(175);
    ui->labelFixtureName->setFixedWidth(125);
    ui->toolButtonFaders->setFixedWidth(125);

    m_btnMenu = new QMenu;
}

FixtureMainTimingUI::~FixtureMainTimingUI()
{
    delete ui;
    delete m_btnMenu;
}

void FixtureMainTimingUI::setFixtureName(QString name)
{
    ui->labelFixtureName->setText(name);
}

void FixtureMainTimingUI::addFaderNames(QList<QString> names)
{
    int numberOfFaders = names.size();

    for(int i = 0; i < numberOfFaders; i++)
    {
        QAction *action = m_btnMenu->addAction(names.at(i));
        //TODO: connect action
    }
    ui->toolButtonFaders->setMenu(m_btnMenu);
}
