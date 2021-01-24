/*  Right-Side Panel Options
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_RightPanel_H
#define PokemonAutomation_RightPanel_H

#include <QWidget>

class MainWindow;

class RightPanel : public QObject{
    Q_OBJECT

public:
    RightPanel(QString name)
        : m_name(std::move(name))
    {}
    virtual ~RightPanel() = default;

    const QString& name() const{ return m_name; }
    virtual QWidget* make_ui(MainWindow& parent) = 0;

protected:
    QString m_name;
};


#endif
