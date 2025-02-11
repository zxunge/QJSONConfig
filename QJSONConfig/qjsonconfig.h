// QJSONConfig -- A Qt JSON config parser

#include <QString>
#include <QSettings>
#include <QVariant>

class QJSONConfig
{
private:
    QString m_cfgFile;
    QSettings m_interSettings;
public:
    explicit ConfigManager(const QString &filePath = "config.json")
        : m_cfgFile(filePath) {}
    bool read();
    bool save() const;
    QVariant getValue(const QString& key, const QVariant& defaultValue = QVariant()) const;
    void setValue(const QString& key, const QVariant& value);
    QVariant &operator[](const QString &cfgKey);
    
};
