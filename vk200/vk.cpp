#include "vk.h"
#include "ui_vk.h"

Vk::Vk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Vk)
{
    ui->setupUi(this);
}

Vk::~Vk()
{
    delete ui;
}
