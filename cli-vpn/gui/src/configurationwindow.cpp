#include "configurationwindow.h"
#include "ui_configurationwindow.h"
#include <QTextStream>
#include <QFile>

#include <iostream>


ConfigurationWindow::ConfigurationWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConfigurationWindow) {
    ui->setupUi(this);
    setFixedSize(420, 549);

    if (qApp->palette().windowText().color() == Qt::black) {
        ui->lightTheme->setVisible(true);
        ui->darkTheme->setVisible(false);
    } else {
        ui->lightTheme->setVisible(false);
        ui->darkTheme->setVisible(true);
    }

    connect(ui->btnBack, SIGNAL(clicked(bool)), this, SLOT(btnBack()));
    connect(ui->btnSave,SIGNAL(clicked(bool)),this, SLOT(btnSave()));
}

ConfigurationWindow::~ConfigurationWindow() {
    delete ui;
}

void ConfigurationWindow::btnBack() {
    this->close();
    emit backMainWindow();
}

void ConfigurationWindow::saveConfig(const QString& configURLS) {
    QString filePath = "configuration.txt";
    QFile file(filePath);
    if (file.open(QIODevice::ReadWrite | QIODevice::Truncate | QIODevice::Text)) {
        file.resize(0);
        QTextStream out(&file);
        out << "URLlist = " << configURLS;
        file.close();
    }
}

void ConfigurationWindow::btnSave() {
    QString configURLS = ui->pteConfiguration->toPlainText();
    configURLS = configURLS.replace("\n", ",");
    saveConfig(configURLS);
    emit valueChangedConfigAdded(true);
}

