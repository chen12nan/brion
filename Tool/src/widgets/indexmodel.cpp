#include "indexmodel.h"
#include <QDBusInterface>
#include <QDebug>

MetaData::MetaData(const QString &text, bool section)
    :m_text(text),
      m_pinyin(QString()),
      m_section(section),
      m_selected(false)
{

}

void MetaData::setPinyin(const QString &py)
{
    m_pinyin = py;
}

QString MetaData::pinyin() const
{
    return m_pinyin == QString() ? m_text : m_pinyin;
}

void MetaData::setText(const QString &text)
{
    m_text = text;
}

QString MetaData::text() const
{
    return m_text;
}

void MetaData::setKey(const QString &key)
{
    m_key = key;
}

QString MetaData::key() const
{
    return m_key;
}

void MetaData::setSection(bool section)
{
    m_section = section;
}

bool MetaData::section() const
{
    return m_section;
}

void MetaData::setSelected(bool selected)
{
    m_selected = selected;
}

bool MetaData::selected() const
{
    return m_selected;
}

bool MetaData::operator ==(const MetaData &md) const
{
    return m_text==md.m_text;
}

bool MetaData::operator >(const MetaData &md) const
{
    int x = QString::compare(m_pinyin, md.m_pinyin, Qt::CaseInsensitive);
    return x>0;
}

QDebug &operator<<(QDebug dbg, const MetaData &md)
{
    dbg.nospace()<<"text: "<<md.text()<<endl;
    /*
    dbg.nospace()<<"MetaData ( pinyin: "<<md.pinyin()<<" , ";
    dbg.nospace()<<"text: "<<md.text()<<" , ";
    dbg.nospace()<<"section: "<<md.section()<<" )";
    */
    return dbg.maybeSpace();
}

IndexModel::IndexModel(QObject *parent)
    :QAbstractListModel(parent)
{
}

void IndexModel::setMetaData(const QList<MetaData> &datas)
{
    m_datas = datas;
}

QList<MetaData> IndexModel::metaData() const
{
    return m_datas;
}

int IndexModel::indexOf(const MetaData &md)
{
    int index = 0;
    QList<MetaData>::iterator it = m_datas.begin();
    for(; it != m_datas.end(); ++it)
    {
        if((*it) == md && (*it).section())
        {
            return index;
        }
        index++;
    }

    return -1;
}

void IndexModel::setLetters(QList<QString> letters)
{
    m_letters = letters;
}

QList<QString> IndexModel::letters() const
{
    return m_letters;
}

int IndexModel::rowCount(const QModelIndex &parent) const
{
    return m_datas.count();
}

QVariant IndexModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();

    MetaData md = m_datas[index.row()];
    if(role == Qt::DisplayRole)
    {
        QVariant v;
        v.setValue(md);
        return v;
    }
    else if(role == Qt::BackgroundColorRole)
    {
        return QBrush(QColor(19, 89, 177));
    }
    else
        return QVariant();
}

Qt::ItemFlags IndexModel::flags(const QModelIndex &index) const
{
    QVariant var = index.data();
    MetaData md = var.value<MetaData>();
    if(md.section())
    {
        return Qt::NoItemFlags;
    }
    return QAbstractListModel::flags(index);
}
