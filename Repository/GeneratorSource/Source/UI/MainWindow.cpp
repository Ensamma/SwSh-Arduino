/*  Main Window UI
 *
 *  From: https://github.com/Mysticial/Pokemon-Automation-SwSh-Arduino-Scripts
 *
 */

#include <QApplication>
#include <QDir>
#include <QMenuBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>
#include "Tools/Tools.h"
#include "Tools/PersistentSettings.h"
#include "SettingListUI.h"
#include "ProgramListUI.h"
#include "MainWindow.h"

//#include <iostream>
//using std::cout;
//using std::endl;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , m_right_panel_widget(nullptr)
{
    if (objectName().isEmpty())
        setObjectName(QString::fromUtf8("MainWindow"));
    resize(800, 600);
    m_centralwidget = new QWidget(this);
    m_centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
    setCentralWidget(m_centralwidget);
    m_menubar = new QMenuBar(this);
    m_menubar->setObjectName(QString::fromUtf8("menubar"));
    setMenuBar(m_menubar);
//    m_statusbar = new QStatusBar(this);
//    m_statusbar->setObjectName(QString::fromUtf8("statusbar"));
//    setStatusBar(m_statusbar);

    setWindowTitle(STRING_POKEMON + " Automation .hex Generator (" + VERSION + ")");

    QMetaObject::connectSlotsByName(this);

    QHBoxLayout* hbox = new QHBoxLayout(m_centralwidget);

    QVBoxLayout* left = new QVBoxLayout();
    hbox->addLayout(left, 2);
    left->setAlignment(Qt::AlignTop);
    left->addWidget(new QLabel("<b><font size=5>Device and Program:</font></b>", this));


    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Board Type:", this));
    left->addWidget(m_mcu_list = new BoardList(*this));

    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Select a Program:", this));
    m_program_list = new ProgramListUI(*this);
    left->addWidget(m_program_list);

    left->addSpacerItem(new QSpacerItem(10, 10));
    left->addWidget(new QLabel("<b>Global Settings:", this));
    m_settings_list = new SettingsListUI(*this);
    left->addWidget(m_settings_list);

#if 0
    int width = std::max(
        m_program_list->text_width(),
        m_settings_list->text_width()
    );
#else
    int width = 300;
#endif
//    cout << "Width = " << width << endl;
    m_program_list->setMaximumWidth(width);
    m_settings_list->setMaximumWidth(width);

    QHBoxLayout* support = new QHBoxLayout();
    left->addLayout(support);
//    support->setMargin(0);

    QVBoxLayout* links = new QVBoxLayout();
    support->addLayout(links);

    {
        QLabel* discord = new QLabel(this);
        links->addWidget(discord);
        discord->setText("<a href=\"" + DISCORD + "\">Discord Server</a>");
        discord->setTextFormat(Qt::RichText);
        discord->setTextInteractionFlags(Qt::TextBrowserInteraction);
        discord->setOpenExternalLinks(true);
    }
    {
        QLabel* github = new QLabel(this);
        links->addWidget(github);
        github->setText("<a href=\"" + GITHUB_REPO + "/blob/master/Documentation/README.md\">Online Documentation</a>");
        github->setTextFormat(Qt::RichText);
        github->setTextInteractionFlags(Qt::TextBrowserInteraction);
        github->setOpenExternalLinks(true);
    }
    {
        QLabel* github = new QLabel(this);
        links->addWidget(github);
        github->setText("<a href=\"" + GITHUB_REPO + "\">GitHub Repository</a>");
        github->setTextFormat(Qt::RichText);
        github->setTextInteractionFlags(Qt::TextBrowserInteraction);
        github->setOpenExternalLinks(true);
    }

    QPushButton* about = new QPushButton("About", this);
    support->addWidget(about);
    connect(
        about, &QPushButton::clicked,
        this, [&](bool){
            QMessageBox box;
            box.information(
                nullptr,
                "About",
                STRING_POKEMON + " Automation .hex Generator (" + VERSION + ")<br>" +
                "Copyright: 2020 - 2021<br>" +
                "<br>"
                "Made by the " + STRING_POKEMON + " Automation Discord Server.<br>"
                "<br>"
                "This program uses Qt and dynamically links to unmodified Qt libraries under LGPL.<br>"
            );
        }
    );


    hbox->addSpacerItem(new QSpacerItem(10, 10));

    QVBoxLayout* right = new QVBoxLayout();
    m_right_panel_layout = right;
    hbox->addLayout(right, 4);
    right->setAlignment(Qt::AlignTop);
    right->addWidget(new QLabel("<b><font size=5>Program Settings:</font></b>", this));
}

const std::string& MainWindow::current_board() const{
    return m_mcu_list->get_board();
}
void MainWindow::change_panel(RightPanel& panel){
    if (m_right_panel_widget != nullptr){
        m_right_panel_layout->removeWidget(m_right_panel_widget);
        delete m_right_panel_widget;
        m_right_panel_widget = nullptr;
    }
    m_right_panel_widget = panel.make_ui(*this);
    m_right_panel_layout->addWidget(m_right_panel_widget);
}






