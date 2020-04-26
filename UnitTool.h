#ifndef UNITTOOL_H
#define UNITTOOL_H

#include <QPointF>
#include <QRectF>


class  UnitTool
{
public:
    UnitTool();
    static int mmToPixel(double mm);        // 将毫米单位和像素单位进行换算
    static double pixelToMM(double pixel);  // 将像素单位转换为毫米单位

    static QRectF getBox(QPointF& point1,
                         QPointF& point2);     // 获得两个点组成的方形
    static QRect getBox(QPoint point1,
                        QPoint point2);        // 获得两个点组成的方形
    static double pointSizeToMM(double pointsize);  // 点大小转换为毫米单位
    static bool equal(double a, double b);      // 因为double的误差，用来判断两个数是否相等
};

#endif // UNITTOOL_H
