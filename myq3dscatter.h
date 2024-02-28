#ifndef MYQ3DSCATTER_H
#define MYQ3DSCATTER_H

#include <QWidget>
#include <Q3DScatter>

class MyQ3DScatter : public Q3DScatter
{
    Q_OBJECT
public:
    explicit MyQ3DScatter(QWidget *parent = nullptr);

    int getItemCount();
    void addData(qreal, qreal, qreal);
private:
    int m_itemCount;

    QScatter3DSeries *scat_series;
    QScatterDataArray *scat_array;
    QScatterDataItem *ptrToDataArray;
signals:
};

#endif // MYQ3DSCATTER_H
