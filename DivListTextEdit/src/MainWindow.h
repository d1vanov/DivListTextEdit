#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget * parent = NULL);
    ~MainWindow();

private:
    Ui::MainWindow * m_pUI;
};

#endif // MAIN_WINDOW_H
