#include "DivListTextEdit.h"
#include <QTextCursor>
#include <QTextList>
#include <QTextBlock>
#include <QTextBlockFormat>
#include <QString>
#include <QKeyEvent>
#include <QTextDocumentFragment>

DivListTextEdit::DivListTextEdit(QWidget * parent) :
    QTextEdit(parent)
{}

void DivListTextEdit::keyPressEvent(QKeyEvent * pEvent)
{
    if (pEvent->key() == Qt::Key_Backspace)
    {
        QTextCursor cursor = QTextEdit::textCursor();
        if (cursor.selection().isEmpty() && cursor.currentList())
        {
            QTextList * pList = cursor.currentList();
            QTextBlock block = cursor.block();
            int itemNumber = pList->itemNumber(block) + 1;
            int numItems = pList->count();
            if ( (pList->format().style() == QTextListFormat::ListDecimal) &&
                 (itemNumber != numItems) &&
                 (QString(block.text().trimmed()).isEmpty()) )
            {
                // ordered list + not the last item + empty item, specialized logic is required:
                // 1. Count the number of lines to process further
                int nLinesToLastItem = 0;
                if (!QString(pList->itemText(pList->item(numItems - 1)).trimmed()).isEmpty())
                {
                    QTextCursor cursorCurrentPosition(cursor);
                    while(!cursorCurrentPosition.atEnd()) {
                        ++nLinesToLastItem;
                        cursorCurrentPosition.movePosition(QTextCursor::Down);
                        QTextBlock regularBlock = cursorCurrentPosition.block();
                        if (pList->itemNumber(regularBlock) == numItems) {
                            cursorCurrentPosition.movePosition(QTextCursor::Down);
                            break;
                        }
                    }
                }
                // 2. Remove all the items including the explicitly removed one and all the following ones
                // NOTE: the text is NOT deleted here, only the ordered list items
                for(int i = numItems; i >= itemNumber; --i) {
                    pList->removeItem(i);
                }
                // 3. Insert empty block of text at the position where the cursor was
                QTextBlockFormat format;
                format.setIndent(std::max(format.indent() - 1, 0));
                cursor.setBlockFormat(format);
                QTextEdit::setTextCursor(cursor);
                // 4. Fix indentation of the remaining contents of the list
                QTextCursor cursorIndentFixer(cursor);
                for(int i = 0; i < nLinesToLastItem; ++i) {
                    cursorIndentFixer.movePosition(QTextCursor::Down);
                    QTextBlockFormat format = cursorIndentFixer.block().blockFormat();
                    format.setIndent(format.indent() - 1);
                    cursorIndentFixer.mergeBlockFormat(format);
                }
                // 5. Create a new list and fill it with saved items
                cursor.movePosition(QTextCursor::Down);
                QTextList * pNewList = cursor.createList(QTextListFormat::ListDecimal);

                for(int i = 1; i < nLinesToLastItem; ++i)
                {
                    cursor.movePosition(QTextCursor::Down);
                    if (cursor.currentList()) {
                        // increase indentation
                        QTextBlockFormat format = cursor.blockFormat();
                        format.setIndent(format.indent() + 1);
                        cursor.mergeBlockFormat(format);
                        continue;
                    }
                    else {
                        pNewList->add(cursor.block());
                    }
                }

                return;
            }
        }
    }

    QTextEdit::keyPressEvent(pEvent);
}

void DivListTextEdit::textIncreaseIndentation()
{
    QTextCursor cursor = QTextEdit::textCursor();
    cursor.beginEditBlock();

    if (cursor.currentList())
    {
        QTextListFormat listFormat = cursor.currentList()->format();
        listFormat.setIndent(listFormat.indent() + 1);
        cursor.createList(listFormat);
    }
    else
    {
        int start = cursor.anchor();
        int end = cursor.position();
        if (start > end)
        {
            start = cursor.position();
            end = cursor.anchor();
        }

        QList<QTextBlock> blocks;
        QTextBlock block = QTextEdit::document()->begin();
        while(block.isValid())
        {
            block = block.next();
            if ( ((block.position() >= start) && (block.position() + block.length() <= end) ) ||
                 block.contains(start) || block.contains(end) )
            {
                blocks << block;
            }
        }

        foreach(QTextBlock block, blocks)
        {
            QTextCursor currentCursor(block);
            QTextBlockFormat blockFormat = currentCursor.blockFormat();
            blockFormat.setIndent(blockFormat.indent() + 1);
            currentCursor.setBlockFormat(blockFormat);
        }
    }

    cursor.endEditBlock();
}

void DivListTextEdit::textInsertOrderedList()
{
    QTextListFormat::Style style = QTextListFormat::ListDecimal;

    QTextCursor cursor = QTextEdit::textCursor();
    cursor.beginEditBlock();

    QTextBlockFormat blockFormat = cursor.blockFormat();

    QTextListFormat listFormat;

    if (cursor.currentList()) {
        listFormat = cursor.currentList()->format();
    }
    else {
        listFormat.setIndent(blockFormat.indent() + 1);
        blockFormat.setIndent(0);
        cursor.setBlockFormat(blockFormat);
    }

    listFormat.setStyle(style);

    cursor.createList(listFormat);
    cursor.endEditBlock();
}
