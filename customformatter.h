#ifndef CUSTOMFORMATTER_H
#define CUSTOMFORMATTER_H

#include <QValue3DAxis>
#include <QDateTime>
/*
class CustomFormatter : public QValue3DAxisFormatter
{
    Q_OBJECT
    Q_PROPERTY(QDate originDate READ originDate WRITE setOriginDate NOTIFY originDateChanged)
    Q_PROPERTY(QString selectionFormat READ selectionFormat WRITE setSelectionFormat NOTIFY selectionFormatChanged)
public:
    explicit CustomFormatter(QObject *parent = nullptr);
    virtual ~CustomFormatter();

    virtual QValue3DAxisFormatter *createNewInstance() const;
    virtual void populateCopy(QValue3DAxisFormatter &copy);
    virtual void recalculate();
    virtual QString stringForValue(qreal value, const QString &format);

    QDate originDate() const;
    QString selectionFormat() const;

public Q_SLOTS:
    void setOriginDate(const QDate &date);
    void setSelectionFormat(const QString &format);

Q_SIGNALS:
    void originDateChanged(const QDate &date);
    void selectionFormatChanged(const QString &format);

private:
    Q_DISABLE_COPY(CustomFormatter)

    QDateTime valueToDateTime(qreal value) const;

    QDate m_originDate;
    QString m_selectionFormat;
};
*/
#endif // CUSTOMFORMATTER_H
