#include "counter.h"



void Counter::setMax(int var)
{
    max = var;
}

int Counter::returnMax()
{
    return max;
}

void Counter::setValue(bool value)
{
    if (value) {
        m_value += 1;
    } else {
        m_value = 0;
    }
    emit valueChanged(m_value);
}
