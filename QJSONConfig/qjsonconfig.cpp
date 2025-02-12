// QJSONConfig -- A Qt JSON config parser
// By: zxunge 
// Available at: https://github.com/zxunge/QJSONConfig

#include "qjsonconfig.h"
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>

// Merge QJsonObject recursively
static void mergeJsonObjects(QJsonObject &target, const QJsonObject &source) 
{
    for (auto it = source.begin(); it != source.end(); ++it) 
    {
        QString key = it.key();
        QJsonValue sourceValue = it.value();
        if (target.contains(key)) 
        {
            QJsonValue targetValue = target.value(key);
            // If the current key values are objects in both target and source, then merge them recursively
            if (targetValue.isObject() && sourceValue.isObject()) 
            {
                QJsonObject mergedObject = targetValue.toObject();
                mergeJsonObjects(mergedObject, sourceValue.toObject());
                target.insert(key, mergedObject);
            } 
            else
                // Else, cover target with source
                target.insert(key, sourceValue);
        } 
        else
            // Directly insert a non-existing key
            target.insert(key, sourceValue);
    }
}

// For recursive reading
static void read(QString finalKey, const QJsonObject &obj, QSettings::SettingsMap &map)
{
    for (const QString &key : obj.keys())
    {
        if (obj[key].isObject())
        {
            finalKey += key + "/";
            read(finalKey, obj[key].toObject(), map);
        }
        else
        {
            finalKey += key;
            map.insert(finalKey, obj[key].toVariant());
        }
    }
}

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
        map = QSettings::SettingsMap();
        return true;
    }
    if (!jsonDoc.isObject()) 
    {
        QJCFG_WARNING() << QObject::tr("json's not object.");
        return false;
    }
    
    read("", jsonDoc.object(), map);
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
        QJsonObject currentObj, superObj;

        // Build the deepest QJsonObject
        currentObj.insert(keys.last(), QJsonValue::fromVariant(itor.value()));

        // Build the outside QJsonObject
        for (
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            qsizetype
#else
            int
#endif
            i {keys.size() - 2}; i > 0; --i) 
        {
            superObj[keys[i]] = currentObj;
            currentObj.swap(superObj);
            superObj = QJsonObject();
        }
        // Already root?
        if (keys.size() != 1)
        {
            QJsonObject tempObj;
            tempObj.insert(keys[0], currentObj);
            mergeJsonObjects(rootObj, tempObj);
        }
        else
            rootObj.insert(keys[0], QJsonValue::fromVariant(itor.value()));
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

bool QJSONConfig::empty()
{
    return m_interSettings->isEmpty();
}
