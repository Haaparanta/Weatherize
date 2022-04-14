#ifndef COUNTER_H
#define COUNTER_H

#include <QObject>

//progress bar calculator
class Counter : public QObject
{
    Q_OBJECT

public:
    Counter() { m_value = 0; }

    int value() const { return m_value; }
    void setMax(int var);
    int returnMax();

public slots:
    void setValue(bool value);

signals:
    void valueChanged(int newValue);

private:
    int m_value;
    int max = 12;
};

#endif // COUNTER_H
