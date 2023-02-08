#ifndef CURVESSURFACES_H
#define CURVESSURFACES_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class CurvesSurfaces; }
QT_END_NAMESPACE

class CurvesSurfaces : public QMainWindow
{
    Q_OBJECT

public:
    CurvesSurfaces(QWidget *parent = nullptr);
    ~CurvesSurfaces();

private:
    Ui::CurvesSurfaces *ui;
};
#endif // CURVESSURFACES_H
