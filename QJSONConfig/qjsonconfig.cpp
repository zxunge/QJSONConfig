// QJSONConfig -- A Qt JSON config parser
// By: zxunge 
// Available at: https://github.com/zxunge/QJSONConfig

#include "qjsonconfig.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>
#include <QMetaType>

/* static */ bool QJSONConfig::readFunc(QIODevice &device, QSettings::SettingsMap &map)
{
    QTextStream stream(&device);
    stream.setCodec("UTF-8");
    QString data { stream.readAll() };
    QJsonParseError jsonError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(data.toUtf8(), &jsonError);

    if (!jsonDoc.isNull() && jsonError.error == QJsonParseError::NoError && !jsonDoc.isEmpty())
    {
        if (jsonDoc.isObject()) 
        {
            QJsonObject obj = jsonDoc.object();
            for(const QString &key: obj.keys())
            {
                QJsonValue jvalue = obj[key];
                map.insert(key, jvalue);
            }
        }
        else
            return false;
      
        return true;
    }
    else
        return false;
}

/* static */ bool QJSONConfig::writeFunc(QIODevice &device, const QSettings::SettingsMap &map)
{
    QTextStream stream(&device);
    stream.setCodec("UTF-8");
    QJsonObject obj;
    QJsonDocument jsonDoc;

    // Generate JSON data
    for (QMap<QString, QVariant>::const_iterator itor = map.constBegin(); itor != map.constEnd(); ++itor)
    {
        switch(itor.value().type())
        {
        case QMetaType::QString:
            obj.insert(itor.key(), QJsonValue(itor.value().toString()));
            break;
        case QMetaType::Int:
            obj.insert(itor.key(), QJsonValue(itor.value().toInt()));
            break;
        case QMetaType::Double:
            obj.insert(itor.key(), QJsonValue(itor.value().toDouble()));
            break;
        case QMetaType::Bool:
            obj.insert(itor.key(), QJsonValue(itor.value().toBool()));
            break;
        default:
            return false;
        }
    }
        
    jsonDoc.setObject(obj);
    stream << jsonDoc.toJson(QJsonDocument::Indented);
    return true;
}

QVariant QJSONConfig::getValue(const QString& key, const QVariant& defaultValue = QVariant())
{
    return m_interSettings->value(cfgKey, defaultValue);
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
