// QJSONConfig -- A Qt JSON config parser
// By: zxunge 
// Available at: https://github.com/zxunge/QJSONConfig

#include "qjsonconfig.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QMessageLogger>

// TODO: readFunc & writeFunc: Add nested config items support
/* static */ bool QJSONConfig::readFunc(QIODevice &device, QSettings::SettingsMap &map)
{
    QTextStream stream(&device);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    stream.setEncoding(QStringConverter::Utf8);
#else
    stream.setCodec("UTF-8");
#endif
    QString data { stream.readAll() };
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8(), &jsonError);

    if (jsonDoc.isNull())
    {
        QJCFG_WARNING() << QObject::tr("Null config json.");
        return false;
    }
    if (jsonError.error != QJsonParseError::NoError)
    {
        QJCFG_WARNING() << QObject::tr("JSON parse error:") << jsonError.errorString();
        return false;
    }
    if (jsonDoc.isEmpty())
    {
        QJCFG_WARNING() << QObject::tr("Empty config json.");
        return false;
    }
    if (!jsonDoc.isObject()) 
    {
        QJCFG_WARNING() << QObject::tr("json's not object.");
        return false;
    }
            
    QJsonObject obj = jsonDoc.object();
    for(const QString &key: obj.keys())
    {
        QJsonValue jvalue = obj[key];
        map.insert(key, jvalue);
    }        
    return true;
}

/* static */ bool QJSONConfig::writeFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
    QTextStream stream(&device);
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
    stream.setEncoding(QStringConverter::Utf8);
#else
    stream.setCodec("UTF-8");
#endif
    QJsonObject rootObj;
    QJsonDocument jsonDoc;

    // Generate JSON data
    // We also want a nested structure
    for (QMap<QString, QVariant>::const_iterator itor = map.constBegin(); itor != map.constEnd(); ++itor)
    {
        QStringList keys {itor.key().split('/')};
        QJsonObject currentObj;

        // Build the deepest QJsonObject
        currentObj.insert(keys.last(), QJsonValue::fromVariant(itor.value()));

        // Build the outside QJsonObject
        for (int i {keys.size() - 2}; i > 0; --i) {
            currentObj[keys[i]] = currentObj;
            currentObj = currentObj[keys[i]].toObject();
        }
        rootObj.insert(keys[0], currentObj);
        
        // obj.insert(itor.key(), QJsonValue::fromVariant(itor.value()));
    }
        
    jsonDoc.setObject(rootObj);
    stream << jsonDoc.toJson(QJsonDocument::Indented);
    return true;
}

QVariant QJSONConfig::getValue(const QString& key, const QVariant& defaultValue) const
{
    return m_interSettings->value(key, defaultValue);
}

void QJSONConfig::setValue(const QString& key, const QVariant& value)
{
    m_interSettings->setValue(key, value);
}

void QJSONConfig::sync()
{
    m_interSettings->sync();
}

void QJSONConfig::clear()
{
    m_interSettings->clear();
}
