#include "triplemodel.h"
#include <QDebug>

TripleModel::TripleModel(QObject* parent)
    : QObject(parent), m_a(0), m_b(50), m_c(100)
{
    loadState();
    normalizeValues();
    qDebug() << "Model created. Initial values: A=" << m_a << "B=" << m_b << "C=" << m_c;
}

int TripleModel::a() const { return m_a; }
int TripleModel::b() const { return m_b; }
int TripleModel::c() const { return m_c; }

void TripleModel::setA(int newA)
{
    if (m_a == newA) return;
    m_a = newA;

    if (m_b < m_a) m_b = m_a;
    if (m_c < m_a) m_c = m_a;

    emit dataChanged();
}

void TripleModel::setB(int newB)
{
    if (newB < m_a || newB > m_c) {
        emit valueRejected();
        return;
    }

    if (m_b == newB) return;
    m_b = newB;
    emit dataChanged();
}

void TripleModel::setC(int newC)
{
    if (m_c == newC) return;
    m_c = newC;

    if (m_b > m_c) m_b = m_c;
    if (m_a > m_c) m_a = m_c;

    emit dataChanged();
}

void TripleModel::normalizeValues()
{
    if (m_b < m_a) m_b = m_a;
    else if (m_b > m_c) m_b = m_c;
}

void TripleModel::saveState()
{
    QSettings settings("MyCompany", "Lab3_MVC");
    settings.setValue("a", m_a);
    settings.setValue("b", m_b);
    settings.setValue("c", m_c);
    qDebug() << "Model state saved.";
}

void TripleModel::loadState()
{
    QSettings settings("MyCompany", "Lab3_MVC");
    m_a = settings.value("a", 0).toInt();
    m_b = settings.value("b", 50).toInt();
    m_c = settings.value("c", 100).toInt();
    qDebug() << "Model state loaded.";
}