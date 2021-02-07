/*  Simple Integer Option
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_SimpleIntegerOption_H
#define PokemonAutomation_SimpleIntegerOption_H

#include <QJsonValue>
#include <QLineEdit>

template <typename Type>
class SimpleIntegerOption{
public:
    SimpleIntegerOption(
        QString label,
        Type min_value,
        Type max_value,
        Type default_value
    );
    void load_default(const QJsonValue& json);
    void load_current(const QJsonValue& json);
    QJsonValue write_default() const;
    QJsonValue write_current() const;

    operator Type() const{ return m_current; }
    Type value() const{ return m_current; }

    bool is_valid() const;
    void restore_defaults();

protected:
    template <typename> friend class SimpleIntegerOptionUI;
    const QString m_label;
    const Type m_min_value;
    const Type m_max_value;
    Type m_default;
    Type m_current;
};


template <typename Type>
class SimpleIntegerOptionUI : public QWidget{
public:
    SimpleIntegerOptionUI(QWidget& parent, SimpleIntegerOption<Type>& value);
    void restore_defaults();

private:
    SimpleIntegerOption<Type>& m_value;
    QLineEdit* m_box;
};


#endif
