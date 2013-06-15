#ifndef DIV_LIST_TEXT_EDIT_H
#define DIV_LIST_TEXT_EDIT_H

#include <QTextEdit>

class DivListTextEdit : public QTextEdit
{
    Q_OBJECT
public:
    explicit DivListTextEdit(QWidget * parent = NULL);
    virtual ~DivListTextEdit() {}

protected:
    virtual void keyPressEvent(QKeyEvent * pEvent);

public slots:
    void textInsertOrderedList();
    void textIncreaseIndentation();
};

#endif // DIV_LIST_TEXT_EDIT_H
