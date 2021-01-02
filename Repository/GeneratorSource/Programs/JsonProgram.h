/*  Program from JSON File.
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <memory>
#include <vector>
#include "Options/SingleStatementOption.h"
#include "Program.h"


class Program_JsonFile : public Program{
public:
    Program_JsonFile(const QString& filepath);
    Program_JsonFile(const QJsonObject& obj);

    virtual bool is_valid() const override;
    virtual void restore_defaults() override;

    virtual QJsonArray parameters_json() const override;
    virtual std::string parameters_cpp() const override;

    virtual QWidget* make_options_body(QWidget& parent) override;

private:
    std::vector<std::unique_ptr<ConfigItem>> m_options;
};
