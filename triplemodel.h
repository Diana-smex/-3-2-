#ifndef TRIPLEMODEL_H
#define TRIPLEMODEL_H

#include <QObject>
#include <QSettings>

class TripleModel : public QObject
{
    Q_OBJECT

public:
    explicit TripleModel(QObject* parent = nullptr);

    int a() const;
    int b() const;
    int c() const;

    void setA(int newA);
    void setB(int newB);
    void setC(int newC);

    void saveState();
    void loadState();

signals:
    void dataChanged();
    void valueRejected();

private:
    int m_a;
    int m_b;
    int m_c;

    void normalizeValues();
};

#endif // TRIPLEMODEL_H