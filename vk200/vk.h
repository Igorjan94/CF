#ifndef VK_H
#define VK_H

#include <QWidget>

namespace Ui {
class Vk;
}

class Vk : public QWidget
{
    Q_OBJECT

public:
    explicit Vk(QWidget *parent = 0);
    ~Vk();

private:
    Ui::Vk *ui;
};

#endif // VK_H
