#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "DivListTextEdit.h"

MainWindow::MainWindow(QWidget * parent) :
    QMainWindow(parent),
    m_pUI(new Ui::MainWindow)
{
    m_pUI->setupUi(this);

    QObject::connect(m_pUI->ActionIncreaseIndentation, SIGNAL(triggered()),
                     m_pUI->textEdit, SLOT(textIncreaseIndentation()));
    QObject::connect(m_pUI->ActionInsertOrderedList, SIGNAL(triggered()),
                     m_pUI->textEdit, SLOT(textInsertOrderedList()));
}

MainWindow::~MainWindow()
{
    delete m_pUI;
}
