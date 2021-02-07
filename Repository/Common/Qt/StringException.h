/*  Simple (and incomplete) Expression Evaluator
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <memory>
#include <QString>

//#include <iostream>
//using std::cout;
//using std::endl;

class StringException{
public:
    StringException(const char* str)
        : m_message(QString::fromUtf8(str))
    {
//        cout << str << endl;
    }
    StringException(const std::string& str)
        : m_message(QString::fromUtf8(str.c_str()))
    {
//        cout << str << endl;
    }
    StringException(QString str)
        : m_message(std::move(str))
    {
//        cout << str.toUtf8().data() << endl;
    }

    const QString& message() const{ return m_message; }
//    QString message() const{ return ""; }

private:
    QString m_message;
};



