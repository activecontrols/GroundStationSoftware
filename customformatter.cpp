// #include "customformatter.h"
#include <QtGraphs/qvalue3daxis.h>

static const qreal oneDayMs = 60.0 * 60.0 * 24.0 * 1000.0;

/*
CustomFormatter::CustomFormatter(QObject *parent) :
    QValue3DAxisFormatter(parent)
{
    qRegisterMetaType<QValue3DAxisFormatter *>();
}

CustomFormatter::~CustomFormatter()
{
}

QValue3DAxisFormatter *CustomFormatter::createNewInstance() const
{
    return new CustomFormatter();
}

void CustomFormatter::populateCopy(QValue3DAxisFormatter &copy)
{
    QValue3DAxisFormatter::populateCopy(copy);

    CustomFormatter *customFormatter = static_cast<CustomFormatter *>(&copy);
    customFormatter->m_originDate = m_originDate;
    customFormatter->m_selectionFormat = m_selectionFormat;
}

void CustomFormatter::recalculate()
{
    // We want our axis to always have gridlines at date breaks

    // Convert range into QDateTimes
    QDateTime minTime = valueToDateTime(qreal(axis()->min()));
    QDateTime maxTime = valueToDateTime(qreal(axis()->max()));

    // Find out the grid counts
    QTime midnight(0, 0);
    QDateTime minFullDate(minTime.date(), midnight);
    int gridCount = 0;
    if (minFullDate != minTime)
        minFullDate = minFullDate.addDays(1);
    QDateTime maxFullDate(maxTime.date(), midnight);

    gridCount += minFullDate.daysTo(maxFullDate) + 1;
    int subGridCount = axis()->subSegmentCount() - 1;

    // Reserve space for position arrays and label strings
    gridPositions().resize(gridCount);
    subGridPositions().resize((gridCount + 1) * subGridCount);
    labelPositions().resize(gridCount);
    labelStrings().reserve(gridCount);

    // Calculate positions and format labels
    qint64 startMs = minTime.toMSecsSinceEpoch();
    qint64 endMs = maxTime.toMSecsSinceEpoch();
    qreal dateNormalizer = endMs - startMs;
    qreal firstLineOffset = (minFullDate.toMSecsSinceEpoch() - startMs) / dateNormalizer;
    qreal segmentStep = oneDayMs / dateNormalizer;
    qreal subSegmentStep = 0;
    if (subGridCount > 0)
        subSegmentStep = segmentStep / qreal(subGridCount + 1);

    for (int i = 0; i < gridCount; i++) {
        qreal gridValue = firstLineOffset + (segmentStep * qreal(i));
        gridPositions()[i] = float(gridValue);
        labelPositions()[i] = float(gridValue);
        labelStrings() << minFullDate.addDays(i).toString(axis()->labelFormat());
    }

    for (int i = 0; i <= gridCount; i++) {
        if (subGridPositions().size()) {
            for (int j = 0; j < subGridCount; j++) {
                float position;
                if (i)
                    position =  gridPositions().at(i - 1) + subSegmentStep * (j + 1);
                else
                    position =  gridPositions().at(0) - segmentStep + subSegmentStep * (j + 1);
                if (position > 1.0f || position < 0.0f)
                    position = gridPositions().at(0);
                subGridPositions()[i * subGridCount + j] = position;
            }
        }
    }
}
*/
