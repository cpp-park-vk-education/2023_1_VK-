#ifndef CONFIGURATIONWINDOW_H
#define CONFIGURATIONWINDOW_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui {
class ConfigurationWindow;
}
QT_END_NAMESPACE

class IConfigurationWindow {
    virtual void btnSave() = 0;
    virtual void btnBack() = 0;
    virtual void saveConfig(const QString& configURLS) = 0;
    // Метод сохраняет данные, введенные пользователем в окно конфигурации для дальнейшего отображения при следующем открытии
    virtual void saveData() = 0;
    // Метод загружает данные, введенные пользователем в окно конфигурации при предыдущем открытии окна
    virtual void loadData() = 0;
    virtual void showTheme() = 0;
    virtual void connectSignals() = 0;
};

class ConfigurationWindow : public QDialog, public IConfigurationWindow {
    Q_OBJECT

public:
    explicit ConfigurationWindow(QWidget *parent = nullptr);
    ~ConfigurationWindow();

public:
    Ui::ConfigurationWindow *ui;
    bool configAdded;

signals:
    void backMainWindow();
    void valueChangedConfigAdded(bool value);

public slots:
    void btnSave() override;
    void btnBack() override;
    void saveConfig(const QString& configURLS) override;
    void saveData() override;
    void loadData() override;
    void showTheme() override;
    void connectSignals() override;
};

#endif // CONFIGURATIONWINDOW_H
