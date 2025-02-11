// QJSONConfig -- A Qt JSON config parser
// By: zxunge 
// Available at: https://github.com/zxunge/QJSONConfig

#include <QString>
#include <QSettings>
#include <QVariant>
#include <QIODevice>

class QJSONConfig
{
private:
    QString m_cfgFile;
    QSettings *m_interSettings;

public:
    explicit ConfigManager(const QString &filePath = "config.json")
        : m_cfgFile(filePath) { QSettings::Format format { QSettings::registerFormat("json", &readFunc, &writeFunc) }; m_interSettings = new QSettings(filePath, format); }
    
    bool sync();
    void clear();
    QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& key, const QVariant& value);
    QVariant &operator[](const QString &cfgKey);

private:
    bool readFunc(QIODevice &device, QSettings::SettingsMap &map);
    bool writeFunc(QIODevice &device, const QSettings::SettingsMap &map);
};
