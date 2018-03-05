#ifndef MENU_H
#define MENU_H

#include <QWidget>
#include <QAction>
#include <QLabel>

namespace Ui {
class Menu;
}

class Menu : public QWidget
{
    Q_OBJECT

signals:
    void signalCloseMainWidget(void);

public slots:
    void slotShowMenu(int globalX, int globalY);
    void slotCloseMenu(void);

public:
    explicit Menu(QWidget *parent = 0);
    ~Menu();

private:
    Ui::Menu *ui;

    QAction *m_addAction;
    QLabel *m_label;
};

#endif // MENU_H
