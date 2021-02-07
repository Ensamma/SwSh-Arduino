/*  Boolean Check Box Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QHBoxLayout>
#include <QLabel>
#include "BooleanCheckBoxOption.h"


BooleanCheckBoxOption::BooleanCheckBoxOption(
    QString label,
    bool default_value
)
    : m_label(std::move(label))
    , m_default(default_value)
    , m_current(default_value)
{}
void BooleanCheckBoxOption::load_default(const QJsonValue& json){
    m_default = json.toBool();
}
void BooleanCheckBoxOption::load_current(const QJsonValue& json){
    m_current = json.toBool();
}
QJsonValue BooleanCheckBoxOption::write_default() const{
    return QJsonValue(m_default);
}
QJsonValue BooleanCheckBoxOption::write_current() const{
    return QJsonValue(m_current);
}

void BooleanCheckBoxOption::restore_defaults(){
    m_current = m_default;
}


BooleanCheckBoxOptionUI::BooleanCheckBoxOptionUI(QWidget& parent, BooleanCheckBoxOption& value)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(m_value.m_label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);
    m_box = new QCheckBox(this);
    m_box->setChecked(m_value);
    layout->addWidget(m_box, 1);
    connect(
        m_box, &QCheckBox::stateChanged,
        this, [=](int){ m_value.m_current = m_box->isChecked(); }
    );
}
void BooleanCheckBoxOptionUI::restore_defaults(){
    m_value.restore_defaults();
    m_box->setChecked(m_value);
}
