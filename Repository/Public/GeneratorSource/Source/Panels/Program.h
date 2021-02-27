/*  Parent Class for all Programs
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#ifndef PokemonAutomation_Program_H
#define PokemonAutomation_Program_H

#include <thread>
#include <QObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <QPushButton>
#include "UI/BoardList.h"
#include "RightPanel.h"

class Program : public RightPanel{
public:
    static const QString JSON_PROGRAM_NAME;
    static const QString JSON_DESCRIPTION;
    static const QString JSON_PARAMETERS;

    static const QString BUILD_BUTTON_NORMAL;
    static const QString BUILD_BUTTON_BUSY;

public:
    Program(const QString& name, const QString& description);
    Program(const QJsonObject& obj);
    ~Program();

    const QString& description() const{ return m_description; }

    virtual bool is_valid() const{ return true; }
    virtual void restore_defaults(){}

    QJsonDocument to_json() const;
    std::string to_cfile() const;

    QString save_json() const;
    QString save_cfile() const;

    void save_and_build(const std::string& board);

    virtual QWidget* make_ui(MainWindow& parent) override;

protected:
    virtual QWidget* make_options_body(QWidget& parent);
    virtual QJsonArray parameters_json() const{ return QJsonArray(); }
    virtual std::string parameters_cpp() const{ return ""; }
    virtual void from_json(const QJsonDocument&){}

private:
    QString m_description;
    QPushButton* m_build_button;
    std::thread m_builder;
};





#endif
