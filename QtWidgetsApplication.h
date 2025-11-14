#pragma once

#include <QtWidgets/QMainWindow>
#include "triplemodel.h"

class QLineEdit;
class QSpinBox;
class QSlider;
class QLabel;
class QVBoxLayout;
class QHBoxLayout;

class QtWidgetsApplication : public QMainWindow
{
    Q_OBJECT

public:
    QtWidgetsApplication(QWidget* parent = nullptr);
    ~QtWidgetsApplication();

private slots:
    void onAValueChanged();
    void onBValueChanged();
    void onCValueChanged();
    void onValueRejected();

    void onModelDataChanged();

private:
    void createUI();
    QHBoxLayout* createRowForValue(const QString& label, QLineEdit*& lineEdit, QSpinBox*& spinBox, QSlider*& slider);
    void blockWidgetSignals(bool block);

    TripleModel* m_model;

    QLineEdit* m_lineEditA;
    QSpinBox* m_spinBoxA;
    QSlider* m_sliderA;

    QLineEdit* m_lineEditB;
    QSpinBox* m_spinBoxB;
    QSlider* m_sliderB;

    QLineEdit* m_lineEditC;
    QSpinBox* m_spinBoxC;
    QSlider* m_sliderC;
};