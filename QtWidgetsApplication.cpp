#include "QtWidgetsApplication.h"

#include <QLineEdit>
#include <QSpinBox>
#include <QSlider>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QDebug>

QtWidgetsApplication::QtWidgetsApplication(QWidget* parent)
    : QMainWindow(parent), m_model(new TripleModel(this))
{
    // Убираем ui.setupUi(this) так как мы создаем интерфейс вручную
    createUI();
    onModelDataChanged();

    // Подключаем сигнал модели к нашему слоту обновления View
    connect(m_model, &TripleModel::dataChanged, this, &QtWidgetsApplication::onModelDataChanged);
    connect(m_model, &TripleModel::valueRejected, this, &QtWidgetsApplication::onValueRejected);

    qDebug() << "MainWindow created.";
}

QtWidgetsApplication::~QtWidgetsApplication()
{
    m_model->saveState();
    qDebug() << "MainWindow destroyed.";
}

void QtWidgetsApplication::createUI()
{
    auto* centralWidget = new QWidget;
    auto* mainLayout = new QVBoxLayout(centralWidget);

    // Создаем три строки для A, B, C
    mainLayout->addLayout(createRowForValue("A:", m_lineEditA, m_spinBoxA, m_sliderA));
    mainLayout->addLayout(createRowForValue("B:", m_lineEditB, m_spinBoxB, m_sliderB));
    mainLayout->addLayout(createRowForValue("C:", m_lineEditC, m_spinBoxC, m_sliderC));

    // Настраиваем диапазоны для всех виджетов
    m_spinBoxA->setRange(0, 100);
    m_sliderA->setRange(0, 100);

    m_spinBoxB->setRange(0, 100);
    m_sliderB->setRange(0, 100);

    m_spinBoxC->setRange(0, 100);
    m_sliderC->setRange(0, 100);

    // Подключаем сигналы виджетов к слотам
    // A
    connect(m_lineEditA, &QLineEdit::editingFinished, this, &QtWidgetsApplication::onAValueChanged);
    connect(m_spinBoxA, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtWidgetsApplication::onAValueChanged);
    connect(m_sliderA, &QSlider::valueChanged, this, &QtWidgetsApplication::onAValueChanged);
    // B
    connect(m_lineEditB, &QLineEdit::editingFinished, this, &QtWidgetsApplication::onBValueChanged);
    connect(m_spinBoxB, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtWidgetsApplication::onBValueChanged);
    connect(m_sliderB, &QSlider::valueChanged, this, &QtWidgetsApplication::onBValueChanged);
    // C
    connect(m_lineEditC, &QLineEdit::editingFinished, this, &QtWidgetsApplication::onCValueChanged);
    connect(m_spinBoxC, QOverload<int>::of(&QSpinBox::valueChanged), this, &QtWidgetsApplication::onCValueChanged);
    connect(m_sliderC, &QSlider::valueChanged, this, &QtWidgetsApplication::onCValueChanged);

    setCentralWidget(centralWidget);
    setWindowTitle("Lab 3.2 - MVC Triple");
    resize(600, 300);
}

QHBoxLayout* QtWidgetsApplication::createRowForValue(const QString& label, QLineEdit*& lineEdit, QSpinBox*& spinBox, QSlider*& slider)
{
    auto* layout = new QHBoxLayout;
    layout->addWidget(new QLabel(label));

    lineEdit = new QLineEdit;
    layout->addWidget(lineEdit);

    spinBox = new QSpinBox;
    layout->addWidget(spinBox);

    slider = new QSlider(Qt::Horizontal);
    layout->addWidget(slider);

    return layout;
}

void QtWidgetsApplication::onAValueChanged()
{
    QObject* sender = QObject::sender();
    int newValue = 0;

    if (sender == m_lineEditA) {
        newValue = m_lineEditA->text().toInt();
    }
    else if (sender == m_spinBoxA) {
        newValue = m_spinBoxA->value();
    }
    else if (sender == m_sliderA) {
        newValue = m_sliderA->value();
    }

    m_model->setA(newValue);
}

void QtWidgetsApplication::onBValueChanged()
{
    QObject* sender = QObject::sender();
    int newValue = 0;

    if (sender == m_lineEditB) {
        newValue = m_lineEditB->text().toInt();
    }
    else if (sender == m_spinBoxB) {
        newValue = m_spinBoxB->value();
    }
    else if (sender == m_sliderB) {
        newValue = m_sliderB->value();
    }

    m_model->setB(newValue);
}

void QtWidgetsApplication::onCValueChanged()
{
    QObject* sender = QObject::sender();
    int newValue = 0;

    if (sender == m_lineEditC) {
        newValue = m_lineEditC->text().toInt();
    }
    else if (sender == m_spinBoxC) {
        newValue = m_spinBoxC->value();
    }
    else if (sender == m_sliderC) {
        newValue = m_sliderC->value();
    }

    m_model->setC(newValue);
}

void QtWidgetsApplication::onModelDataChanged()
{
    qDebug() << "Updating View from Model. A=" << m_model->a() << "B=" << m_model->b() << "C=" << m_model->c();

    blockWidgetSignals(true);

    // Обновляем все виджеты для A
    m_lineEditA->setText(QString::number(m_model->a()));
    m_spinBoxA->setValue(m_model->a());
    m_sliderA->setValue(m_model->a());

    // Обновляем все виджеты для B
    m_lineEditB->setText(QString::number(m_model->b()));
    m_spinBoxB->setValue(m_model->b());
    m_sliderB->setValue(m_model->b());

    // Обновляем все виджеты для C
    m_lineEditC->setText(QString::number(m_model->c()));
    m_spinBoxC->setValue(m_model->c());
    m_sliderC->setValue(m_model->c());

    blockWidgetSignals(false);
}

void QtWidgetsApplication::blockWidgetSignals(bool block)
{
    m_lineEditA->blockSignals(block);
    m_spinBoxA->blockSignals(block);
    m_sliderA->blockSignals(block);

    m_lineEditB->blockSignals(block);
    m_spinBoxB->blockSignals(block);
    m_sliderB->blockSignals(block);

    m_lineEditC->blockSignals(block);
    m_spinBoxC->blockSignals(block);
    m_sliderC->blockSignals(block);
}
void QtWidgetsApplication::onValueRejected()
{
    // ПРИНУДИТЕЛЬНО возвращаем виджеты B к текущему значению из модели
    blockWidgetSignals(true);

    m_lineEditB->setText(QString::number(m_model->b()));
    m_spinBoxB->setValue(m_model->b());
    m_sliderB->setValue(m_model->b());

    blockWidgetSignals(false);
}