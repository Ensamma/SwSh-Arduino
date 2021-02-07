/*  Time Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QHBoxLayout>
#include <QLabel>
#include "Common/Clientside/PrettyPrint.h"
#include "Common/Qt/StringException.h"
#include "Common/Qt/ExpressionEvaluator.h"
#include "TimeExpressionOption.h"

template class TimeExpressionOption<uint16_t>;
template class TimeExpressionOption<uint32_t>;

template class TimeExpressionOptionUI<uint16_t>;
template class TimeExpressionOptionUI<uint32_t>;


template <typename Type>
TimeExpressionOption<Type>::TimeExpressionOption(
    QString label,
    Type min_value,
    Type max_value,
    QString default_value
)
    : m_label(std::move(label))
    , m_min_value(min_value)
    , m_max_value(max_value)
    , m_default(default_value)
    , m_current(std::move(default_value))
{
    update();
}
template <typename Type>
void TimeExpressionOption<Type>::load_default(const QJsonValue& json){
    m_default = json.toString();
    update();
}
template <typename Type>
void TimeExpressionOption<Type>::load_current(const QJsonValue& json){
    m_current = json.toString();
    update();
}
template <typename Type>
QJsonValue TimeExpressionOption<Type>::write_default() const{
    return QJsonValue(m_default);
}
template <typename Type>
QJsonValue TimeExpressionOption<Type>::write_current() const{
    return QJsonValue(m_current);
}

template <typename Type>
bool TimeExpressionOption<Type>::is_valid() const{
    return m_error.isEmpty();
}
template <typename Type>
void TimeExpressionOption<Type>::restore_defaults(){
    m_current = m_default;
    update();
}


template <typename Type>
bool TimeExpressionOption<Type>::set_value(const QString& str){
    m_current = str;
    return update();
}
template <typename Type>
QString TimeExpressionOption<Type>::time_string() const{
    if (!m_error.isEmpty()){
        return "<font color=\"red\">" + m_error + "</font>";
    }
    return PokemonAutomation::ticks_to_time(m_value).c_str();
}
template <typename Type>
bool TimeExpressionOption<Type>::update(){
    if (m_current.isEmpty() || m_current.isNull()){
        m_error = "Expression is empty.";
        return false;
    }
    uint32_t value;
    try{
        value = parse_ticks_i32(m_current);
    }catch (const StringException& str){
        m_error = str.message();
        return false;
    }catch (...){
        m_error = "Unknown Error";
        return false;
    }
    m_value = (Type)value;

    if (value < m_min_value){
        m_error = "Overflow: Number is too small.";
        return false;
    }
    if (value > m_max_value){
        m_error = "Overflow: Number is too large.";
        return false;
    }
    m_error.clear();
    return true;
}
template <typename Type>
TimeExpressionOptionUI<Type>::TimeExpressionOptionUI(QWidget& parent, TimeExpressionOption<Type>& value)
    : QWidget(&parent)
    , m_value(value)
{
    QHBoxLayout* layout = new QHBoxLayout(this);
    QLabel* text = new QLabel(m_value.m_label, this);
    layout->addWidget(text, 1);
    text->setWordWrap(true);
    QVBoxLayout* rows = new QVBoxLayout();
    layout->addLayout(rows, 1);

    QHBoxLayout* row0 = new QHBoxLayout();
    rows->addLayout(row0);
    QHBoxLayout* row1 = new QHBoxLayout();
    rows->addLayout(row1);

    m_box = new QLineEdit(m_value.m_current, this);
    row0->addWidget(m_box);
    row0->addWidget(new QLabel("ticks", this));

    QLabel* seconds = new QLabel(m_value.time_string(), this);
    seconds->setAlignment(Qt::AlignHCenter);
    row1->addWidget(seconds);

    connect(
        m_box, &QLineEdit::textChanged,
        this, [=](const QString& text){
//            cout << text.toUtf8().data() << endl;
            m_value.set_value(text);
            seconds->setText(m_value.time_string());
        }
    );
}
template <typename Type>
void TimeExpressionOptionUI<Type>::restore_defaults(){
    m_value.restore_defaults();
    m_box->setText(m_value.m_current);
}
