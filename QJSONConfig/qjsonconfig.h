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
    // Client class: distinguish between lvalue and rvalue
    class Proxy {
    public:
        Proxy(QJSONConfig& container, QString cfgKey) 
            : container(container), key(cfgKey) {}

        // Convert into value (rvalue)
        operator QVariant() const {
            return container.m_interSettings->value(key);
        }

        // Assignment (lvalue)
        Proxy& operator=(QVariant value) {
            container.m_interSettings->setValue(key, value);
            return *this;
        }

    private:
        QJSONConfig& container;
        QString key;
    };

public:
    explicit QJSONConfig(const QString &filePath = "config.json")
        : m_cfgFile(filePath) { QSettings::Format format { QSettings::registerFormat("json", &readFunc, &writeFunc) }; m_interSettings = new QSettings(filePath, format); }
    ~QJSONConfig() { delete m_interSettings; }
    
    void sync();
    void clear();
    QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& key, const QVariant& value);
    Proxy operator[](const QString &cfgKey) { return Proxy(*this, cfgKey); }

private:
    static bool readFunc(QIODevice &device, QSettings::SettingsMap &map);
    static bool writeFunc(QIODevice &device, const QSettings::SettingsMap &map);
};
