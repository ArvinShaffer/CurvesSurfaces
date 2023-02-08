#include "curvessurfaces.h"
#include "ui_curvessurfaces.h"

CurvesSurfaces::CurvesSurfaces(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CurvesSurfaces)
{
    ui->setupUi(this);
}

CurvesSurfaces::~CurvesSurfaces()
{
    delete ui;
}

