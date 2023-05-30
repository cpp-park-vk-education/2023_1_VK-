#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QScreen>
#include <QStyle>
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    filePath = "configuration.txt";
    clearConfig(filePath);

    setFixedSize(420, 549);

    buttonClicked = false;
    buttonCountryClicked = false;
    configAdded = false;



    ui->setupUi(this);
    ui->lbFoxTail->setVisible(false);
    ui->lbConfigUsageOn->setVisible(false);
    ui->lbConfigUsageOff->setVisible(true);

    darkMode();


    connect(ui->actionNewCountry, &QAction::triggered, this, &MainWindow::showCountries);

    connect(ui->LightMode, &QAction::triggered, this, &MainWindow::lightMode);
    connect(ui->DarkMode, &QAction::triggered, this, &MainWindow::darkMode);

    connect(ui->btnTurnVpn,SIGNAL(clicked(bool)),this, SLOT(turnOnVPN()));

    connect(ui->showStatistics, &QAction::triggered, this, &MainWindow::showStatics);
    connect(ui->showAuthorization, &QAction::triggered, this, &MainWindow::showAuthorization);
    connect(ui->showConfiguration, &QAction::triggered, this, &MainWindow::showConfiguration);

    connect(ui->connectPoland, &QAction::triggered, this, &MainWindow::connectionPoland);
    connect(ui->connectNetherlands, &QAction::triggered, this, &MainWindow::connectionNetherlands);
}

MainWindow::~MainWindow() {
    delete ui;
    delete countriesWindow;
    delete configurationWindow;
}

void MainWindow::showCountries() {
    countriesWindow = new Countries();
    connect(countriesWindow, &Countries::backMainWindow, this, &MainWindow::show);
    connect(countriesWindow, &Countries::valueChangedNameTun, this, &MainWindow::setValueNameTun);
    connect(countriesWindow, &Countries::valueChangedButtonCountryClicked, this, &MainWindow::setValueButtonCountryClicked);
    connect(countriesWindow, &Countries::valueChangedDefaultConfiguration, this, &MainWindow::setValueDefaultConfiguration);

    countriesWindow->show();
    this->close();
}

void MainWindow::setValueButtonCountryClicked(bool value) {
    ui->lbCountryMessage->setVisible(false);
    buttonCountryClicked = value;
}

void MainWindow::setValueDefaultConfiguration(const std::string& value) {
    defaultConfiguration = value;
}

void MainWindow::setValueNameTun(const std::string& value) {
    nameTun = value;
}

void MainWindow::clearConfig(const QString& filePath) {
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        file.resize(0);
        file.close();
    }
}

void MainWindow::setValueConfigAdded(bool value) {
    configAdded = value;
    if (value) {
        ui->lbConfigUsageOn->setVisible(true);
        ui->lbConfigUsageOff->setVisible(false);
    } else {
        ui->lbConfigUsageOn->setVisible(false);
        ui->lbConfigUsageOff->setVisible(true);
    }
}


void MainWindow::turnOnVPN() {
    if (buttonCountryClicked) {
        ui->lbCountryMessage->setVisible(false);
        if (!buttonClicked) {
            ui->btnTurnVpn->setStyleSheet("QPushButton {border-image:url(:/img/TurnON.png); width: 50px; height: 50px;}");
            ui->lbFoxTail->setVisible(true);
            buttonClicked = true;

            if (!configAdded) {
                clearConfig(filePath);
            } else {
                configAdded = false;
            }
            QFile file(filePath);
            if (file.open(QIODevice::Append | QIODevice::Text)) {
                QTextStream stream(&file);
                stream << QString::fromStdString(nameTun) << QString::fromStdString(defaultConfiguration) << "\n";
                file.close();
            }
        } else {
            ui->btnTurnVpn->setStyleSheet("QPushButton {border-image:url(:/img/TurnOFF.png); width: 50px; height: 50px;}");
            ui->lbFoxTail->setVisible(false);
            ui->lbConfigUsageOn->setVisible(false);
            ui->lbConfigUsageOff->setVisible(true);
            buttonClicked = false;
            buttonCountryClicked = false;
        }
    } else {
        ui->lbCountryMessage->setVisible(true);
        ui->btnTurnVpn->setStyleSheet("QPushButton {border-image:url(:/img/TurnOFF.png); width: 50px; height: 50px;}");
    }

}



void MainWindow::lightMode() {
    QPalette lightPalette;

    lightPalette.setColor(QPalette::Window, QColor(228, 227, 217));
    lightPalette.setColor(QPalette::WindowText, Qt::black);
    lightPalette.setColor(QPalette::Base, Qt::lightGray);
    lightPalette.setColor(QPalette::AlternateBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipBase, Qt::white);
    lightPalette.setColor(QPalette::ToolTipText, Qt::black);
    lightPalette.setColor(QPalette::Text, Qt::black);
    lightPalette.setColor(QPalette::Button, Qt::lightGray);
    lightPalette.setColor(QPalette::ButtonText, Qt::black);
    lightPalette.setColor(QPalette::BrightText, Qt::red);
    lightPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    lightPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    lightPalette.setColor(QPalette::HighlightedText, Qt::white);

    qApp->setPalette(lightPalette);

    ui->lightTheme->setVisible(true);
    ui->darkTheme->setVisible(false);
}

void MainWindow::connectionPoland() {
    defaultConfiguration.clear();

    defaultConfiguration = "\nEndpoint = 45.82.15.27";
    nameTun = "PL_tun";
    ui->lbCountryMessage->setVisible(false);
    buttonCountryClicked = true;
}

void MainWindow::connectionNetherlands() {
    defaultConfiguration.clear();

    defaultConfiguration = "\nEndpoint = 46.19.69.219";
    nameTun = "NL_tun";
    ui->lbCountryMessage->setVisible(false);
    buttonCountryClicked = true;
}


void MainWindow::darkMode() {
    QPalette darkPalette;

    darkPalette.setColor(QPalette::Window, QColor(65, 71, 84));
    darkPalette.setColor(QPalette::WindowText, Qt::white);
    darkPalette.setColor(QPalette::Base, QColor(25, 25, 25));
    darkPalette.setColor(QPalette::AlternateBase, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ToolTipBase, Qt::white);
    darkPalette.setColor(QPalette::ToolTipText, Qt::white);
    darkPalette.setColor(QPalette::Text, Qt::white);
    darkPalette.setColor(QPalette::Button, QColor(53, 53, 53));
    darkPalette.setColor(QPalette::ButtonText, Qt::white);
    darkPalette.setColor(QPalette::BrightText, Qt::red);
    darkPalette.setColor(QPalette::Link, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::Highlight, QColor(42, 130, 218));
    darkPalette.setColor(QPalette::HighlightedText, Qt::black);

    qApp->setPalette(darkPalette);


    ui->darkTheme->setVisible(true);
    ui->lightTheme->setVisible(false);

}


void MainWindow::showStatics() {
    statics.show();
}


void MainWindow::showAuthorization() {
    authentication.show();
}


void MainWindow::showConfiguration() {
    configurationWindow = new ConfigurationWindow();
    connect(configurationWindow, &ConfigurationWindow::backMainWindow, this, &MainWindow::show);
    connect(configurationWindow, &ConfigurationWindow::valueChangedConfigAdded, this, &MainWindow::setValueConfigAdded);

    configurationWindow->show();
    this->close();
}

