#include "QtExtKeySequenceEdit.h"

#include <QKeyEvent>

QtExtKeySequenceEdit::QtExtKeySequenceEdit(QWidget *parent)
    : QKeySequenceEdit(parent)
    , m_num(0)
{
}

QKeySequence QtExtKeySequenceEdit::keySequence() const
{
    return m_keySequence;
}

void QtExtKeySequenceEdit::setKeySequence(const QKeySequence &keySequence)
{
    m_keySequence = keySequence;
    QKeySequenceEdit::setKeySequence(m_keySequence);
}

void QtExtKeySequenceEdit::keyPressEvent(QKeyEvent *pEvent)
{
    pEvent->accept();

    int key = pEvent->key();
    if (key == Qt::Key_unknown ||
        key == Qt::Key_Control ||
        key == Qt::Key_Shift ||
        key == Qt::Key_Alt ||
        key == Qt::Key_Meta)
    {
        return;
    }

    if (key == Qt::Key_Backspace || key == Qt::Key_Delete)
    {
        m_num = 0;
        m_keySequence = QKeySequence();
        QKeySequenceEdit::setKeySequence(m_keySequence);
        return;
    }

    int modifiers = pEvent->modifiers();
    if (modifiers & Qt::ControlModifier)
    {
        key += Qt::CTRL;
    }
    if (modifiers & Qt::ShiftModifier)
    {
        key += Qt::SHIFT;
    }
    if (modifiers & Qt::AltModifier)
    {
        key += Qt::ALT;
    }
    if (modifiers & Qt::MetaModifier)
    {
        key += Qt::META;
    }

    if (m_num == 0)
    {
        m_keySequence = QKeySequence(key);
    }
    else
    {
        int key_count = m_keySequence.count();
        if (key_count > 0)
        {
            QVector<int> keys;
            for (int i = 0; i < key_count; ++i)
            {
                keys.append(m_keySequence[i]);
            }
            keys.append(key);
            m_keySequence = QKeySequence(keys);
        }
    }

    QKeySequenceEdit::setKeySequence(m_keySequence);
    m_num++;
}
