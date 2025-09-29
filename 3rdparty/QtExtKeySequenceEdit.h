#include <QKeySequenceEdit>
#include <QKeySequence>

class QtExtKeySequenceEdit : public QKeySequenceEdit {
    Q_OBJECT
public:
    explicit QtExtKeySequenceEdit(QWidget *parent = 0);
    ~QtExtKeySequenceEdit();

    QKeySequence keySequence() const;

public slots:
    void setKeySequence(const QKeySequence &keySequence);

protected:
    void keyPressEvent(QKeyEvent *pEvent);

private:
    int m_num;
    QKeySequence m_keySequence;
};
