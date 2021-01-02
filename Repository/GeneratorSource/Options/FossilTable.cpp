/*  Fossil Table
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <map>
#include <QJsonArray>
#include <QVBoxLayout>
#include <QLabel>
#include <QTableWidget>
#include <QHeaderView>
#include "Tools/Tools.h"
#include "FossilTable.h"

const QString FossilTable::OPTION_TYPE      = "FossilTable";
const QString FossilTable::JSON_GAME_SLOT   = "game_slot";
const QString FossilTable::JSON_USER_SLOT   = "user_slot";
const QString FossilTable::JSON_FOSSIL      = "fossil";
const QString FossilTable::JSON_REVIVES     = "revives";


int FossilTable_init = register_option(
    FossilTable::OPTION_TYPE,
        [](const QJsonObject& obj){
        return std::unique_ptr<ConfigItem>(
            new FossilTable(obj)
        );
    }
);

const std::vector<QString> FOSSIL_LIST{
    "Dracozolt",
    "Arctozolt",
    "Dracovish",
    "Arctovish",
};
const std::map<QString, int> FOSSIL_MAP{
    {"Dracozolt", 0},
    {"Arctozolt", 1},
    {"Dracovish", 2},
    {"Arctovish", 3},
};

std::vector<FossilTable::GameSlot> parse_fossil_slot(const QJsonObject& obj, const QString& key){
    std::vector<FossilTable::GameSlot> list;
    for (const auto& item : json_get_array(obj, key)){
        QJsonObject line = json_cast_object(item);
        FossilTable::GameSlot slot;

        slot.game_slot = json_get_int(line, FossilTable::JSON_GAME_SLOT);
        if (slot.game_slot < 1 || slot.game_slot > 2){
            throw "Config Error - Game slot is out of range.";
        }

        slot.user_slot = json_get_int(line, FossilTable::JSON_USER_SLOT);
        if (slot.user_slot < 1 || slot.user_slot > 8){
            throw "Config Error - User slot is out of range.";
        }

        QString str = json_get_string(line, FossilTable::JSON_FOSSIL);
        auto iter = FOSSIL_MAP.find(str);
        if (iter == FOSSIL_MAP.end()){
            throw "Config Error - Invalid Fossil Name.";
        }
        slot.fossil = (FossilTable::Fossil)iter->second;

        slot.revives = json_get_int(line, FossilTable::JSON_REVIVES);
        if (slot.revives < 0 || slot.revives > 965){
            throw "Config Error - Revives is out of range.";
        }

        list.emplace_back(slot);
    }
    return list;
}
QJsonArray write_fossil_slot(const std::vector<FossilTable::GameSlot>& list){
    QJsonArray ret;
    for (const auto& item : list){
        QJsonObject obj;
        obj.insert(FossilTable::JSON_GAME_SLOT, item.game_slot);
        obj.insert(FossilTable::JSON_USER_SLOT, item.user_slot);
        obj.insert(FossilTable::JSON_FOSSIL, FOSSIL_LIST[item.fossil]);
        obj.insert(FossilTable::JSON_REVIVES, item.revives);
        ret += std::move(obj);
    }
    return ret;
}

FossilTable::FossilTable(const QJsonObject& obj)
    : SingleStatementOption(obj)
    , m_default(parse_fossil_slot(obj, JSON_DEFAULT))
    , m_current(parse_fossil_slot(obj, JSON_CURRENT))
{}
bool FossilTable::is_valid() const{
    if (m_current.empty()){
        return false;
    }
    for (const auto& item : m_current){
        if (item.game_slot < 1 || item.game_slot > 2){
            return false;
        }
        if (item.user_slot < 1 || item.user_slot > 8){
            return false;
        }
        if (item.revives < 0 || item.revives > 965){
            return false;
        }
    }
    return true;
}
void FossilTable::restore_defaults(){
    m_current = m_default;
}
QJsonObject FossilTable::to_json() const{
    QJsonObject root = SingleStatementOption::to_json();
    root.insert(JSON_DEFAULT, write_fossil_slot(m_default));
    root.insert(JSON_CURRENT, write_fossil_slot(m_current));
    return root;
}
std::string FossilTable::to_cpp() const{
    std::string str;
    str += m_declaration.toUtf8().data();
    str += " = {\r\n";
    for (const auto& item : m_current){
        str += "    {";
        str += std::to_string(item.game_slot);
        str += ", ";
        str += std::to_string(item.user_slot);
        str += ", ";
        str += FOSSIL_LIST[item.fossil].toUtf8().data();
        str += ", ";
        str += std::to_string(item.revives);
        str += "},\r\n";
    }
    str += "};\r\n";
    return str;
}
QWidget* FossilTable::make_ui(QWidget& parent){
    return new FossilTableUI(parent, *this, m_label);
}


void FossilTableUI::add_row(int row, const FossilTable::GameSlot& game, int& index_ref){
    index_ref = row;
    m_table->setCellWidget(row, 0, make_game_slot_box(*m_table, index_ref, game.game_slot - 1));
    m_table->setCellWidget(row, 1, make_user_slot_box(*m_table, index_ref, game.user_slot - 1));
    m_table->setCellWidget(row, 2, make_fossil_slot_box(*m_table, index_ref, game.fossil));
    m_table->setCellWidget(row, 3, make_revives_slot_box(*m_table, index_ref, game.revives));
    m_table->setCellWidget(row, 4, make_insert_button(*m_table, index_ref));
    m_table->setCellWidget(row, 5, make_remove_button(*m_table, index_ref));
}
QComboBox* FossilTableUI::make_game_slot_box(QWidget& parent, int& row, int slot){
    QComboBox* box = new QComboBox(&parent);
    box->addItem("Slot 1");
    box->addItem("Slot 2");
    box->setCurrentIndex(slot);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].game_slot = index + 1;
        }
    );
    return box;
}
QComboBox* FossilTableUI::make_user_slot_box(QWidget& parent, int& row, int slot){
    QComboBox* box = new QComboBox(&parent);
    box->addItem("User 1");
    box->addItem("User 2");
    box->addItem("User 3");
    box->addItem("User 4");
    box->addItem("User 5");
    box->addItem("User 6");
    box->addItem("User 7");
    box->addItem("User 8");
    box->setCurrentIndex(slot);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].user_slot = index + 1;
        }
    );
    return box;
}
QComboBox* FossilTableUI::make_fossil_slot_box(QWidget& parent, int& row, FossilTable::Fossil fossil){
    QComboBox* box = new QComboBox(&parent);
    box->addItem(FOSSIL_LIST[0]);
    box->addItem(FOSSIL_LIST[1]);
    box->addItem(FOSSIL_LIST[2]);
    box->addItem(FOSSIL_LIST[3]);
    box->setCurrentIndex(fossil);
    connect(
        box, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
        this, [&](int index){
            m_value.m_current[row].fossil = (FossilTable::Fossil)index;
        }
    );
    return box;
}
QLineEdit* FossilTableUI::make_revives_slot_box(QWidget& parent, int& row, int revives){
    QLineEdit* box = new QLineEdit(&parent);
    QIntValidator* validator = new QIntValidator(0, 965, box);
    box->setValidator(validator);
    box->setText(QString::number(revives));
    box->setMaxLength(3);
    box->setMaximumWidth(50);
    box->setAlignment(Qt::AlignHCenter);
    connect(
        box, &QLineEdit::textChanged,
        this, [&, box](const QString& text){
            int revives = text.toInt();
            int fixed = revives;
            fixed = std::max(fixed, 0);
            fixed = std::min(fixed, 965);
            if (revives != fixed){
                box->setText(QString::number(fixed));
            }
            m_value.m_current[row].revives = fixed;
        }
    );
    return box;
}
QPushButton* FossilTableUI::make_insert_button(QWidget& parent, int& row){
    QPushButton* button = new QPushButton(&parent);
    QFont font;
    font.setBold(true);
    button->setFont(font);
    button->setText("Insert");
//    QSizePolicy policy;
//    policy.setHorizontalPolicy(QSizePolicy::Minimum);
//    policy.setHorizontalStretch(0);
//    button->setSizePolicy(policy);
    button->setMaximumWidth(60);
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = row;
            FossilTable::GameSlot item{1, 1, FossilTable::Dracovish, 960};

            //  Update data vector.
            m_value.m_current.insert(m_value.m_current.begin() + index, item);

            //  Update index vector.
            m_index_table.insert(m_index_table.begin() + index, std::unique_ptr<int>(new int(index)));
            int& new_row = *m_index_table[index];
            for (size_t c = 0; c < m_index_table.size(); c++){
                *m_index_table[c] = (int)c;
            }

            //  Update UI.
            m_table->insertRow(index);
            add_row(index, item, new_row);
        }
    );
    return button;
}
QPushButton* FossilTableUI::make_remove_button(QWidget& parent, int& row){
    QPushButton* button = new QPushButton(&parent);
    QFont font;
    font.setBold(true);
    button->setFont(font);
    button->setText("Delete");
    button->setMaximumWidth(60);
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = row;

            //  Update data vector.
            m_index_table.erase(m_index_table.begin() + index);

            //  Update index vector.
            for (size_t c = 0; c < m_index_table.size(); c++){
                *m_index_table[c] = (int)c;
            }
            m_value.m_current.erase(m_value.m_current.begin() + index);

            //  Update UI.
            m_table->removeRow(index);
        }
    );
    return button;
}


FossilTableUI::FossilTableUI(QWidget& parent, FossilTable& value, const QString& label)
    : QWidget(&parent)
    , m_value(value)
{
    QVBoxLayout* layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel(label, this));
    m_table = new QTableWidget(this);
    layout->addWidget(m_table);
    m_table->setColumnCount(6);

    QStringList header;
    header << "Game" << "User" << "Fossil" << "Revives" << "" << "";
    m_table->setHorizontalHeaderLabels(header);
    QFont font;
    font.setBold(true);
    m_table->horizontalHeader()->setFont(font);
    m_table->horizontalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);

    size_t rows = m_value.m_current.size();
    m_table->setRowCount(m_value.m_current.size() + 1);
    for (size_t c = 0; c < rows; c++){
        const auto& item = m_value.m_current[c];
        m_index_table.emplace_back(new int);
        add_row(c, item, *m_index_table.back());
    }

    QPushButton* button = new QPushButton(m_table);
    button->setText("Add Row");
    m_table->setCellWidget(m_value.m_current.size(), 0, button);
    connect(
        button, &QPushButton::clicked,
        this, [&](bool){
            int index = m_index_table.size();

            //  Update data vector.
            m_value.m_current.emplace_back(FossilTable::GameSlot{1, 1, FossilTable::Dracovish, 960});
            const auto& item = m_value.m_current.back();

            //  Update index vector.
            m_index_table.emplace_back(new int);

            //  Update UI.
            m_table->insertRow(index);
            add_row(index, item, *m_index_table.back());
        }
    );


}
FossilTableUI::~FossilTableUI(){

}









