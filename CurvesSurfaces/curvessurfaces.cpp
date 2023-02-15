#include "curvessurfaces.h"
#include "ui_curvessurfaces.h"
#include <vtkSphereSource.h>


#include <vtkActor.h>
#include <vtkInteractorStyleTrackballCamera.h>
#include <vtkNamedColors.h>
#include <vtkNew.h>
#include <vtkObjectFactory.h>
#include <vtkPointPicker.h>
#include <vtkPolyDataMapper.h>
#include <vtkProperty.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkRendererCollection.h>
#include <vtkSphereSource.h>
#include <vtkGenericOpenGLRenderWindow.h>

namespace {

// Define interaction style
class MouseInteractorStylePP : public vtkInteractorStyleTrackballCamera
{
public:
    static MouseInteractorStylePP* New();
    vtkTypeMacro(MouseInteractorStylePP, vtkInteractorStyleTrackballCamera);

    virtual void OnLeftButtonDown() override
    {
        std::cout << "Picking pixel: " << this->Interactor->GetEventPosition()[0]
                  << " " << this->Interactor->GetEventPosition()[1] << std::endl;
        this->Interactor->GetPicker()->Pick(this->Interactor->GetEventPosition()[0],
                this->Interactor->GetEventPosition()[1],
                0, // always zero.
                this->Interactor->GetRenderWindow()
                ->GetRenderers()
                ->GetFirstRenderer());
        double picked[3];
        this->Interactor->GetPicker()->GetPickPosition(picked);
        std::cout << "Picked value: " << picked[0] << " " << picked[1] << " "
                  << picked[2] << std::endl;
        // Forward events
        vtkInteractorStyleTrackballCamera::OnLeftButtonDown();
    }
};

vtkStandardNewMacro(MouseInteractorStylePP);

} // namespace
CurvesSurfaces::CurvesSurfaces(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::CurvesSurfaces)
{
    ui->setupUi(this);

    QObject::connect(ui->actionBezier, &QAction::triggered, this, &CurvesSurfaces::bezier);
    QObject::connect(ui->actionTest, &QAction::triggered, this, &CurvesSurfaces::test);

    vtkNew<vtkNamedColors> colors;
    vtkNew<vtkRenderer> renderer;
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("CurvesSurfaces");
    this->ui->openGLWidget->interactor()->SetRenderWindow(renderWindow);


    vtkNew<vtkAxesActor> axes;

    //this->widget = vtkNew<vtkOrientationMarkerWidget>;
    double rgba[4]{0.0, 0.0, 0.0, 0.0};
    colors->GetColor("Carrot", rgba);
    this->widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    this->widget->SetOrientationMarker(axes);
    this->widget->SetInteractor(this->ui->openGLWidget->interactor());
    this->widget->SetViewport(0.0, 0.0, 0.4, 0.4);
    this->widget->SetEnabled(1);
    this->widget->InteractiveOn();

    renderer->GetActiveCamera()->Azimuth(50);
    renderer->GetActiveCamera()->Elevation(-30);

    renderer->ResetCamera();

    setCentralWidget(ui->openGLWidget);

    this->ui->openGLWidget->setRenderWindow(renderWindow);
    this->ui->openGLWidget->renderWindow()->Render();
    this->ui->openGLWidget->interactor()->Start();
}

CurvesSurfaces::~CurvesSurfaces()
{
    delete ui;
}




TopoDS_Shape
MakeBottle(const Standard_Real myWidth , const Standard_Real myHeight , const Standard_Real myThickness);

#include<Geom_BezierCurve.hxx>
void CurvesSurfaces::bezier()
{
    //BRepPrimAPI_MakeSphere mkSphere(5.);
    //BRepPrimAPI_MakeBox mkBox(1., 2., 3);
    //const TopoDS_Shape& shape = mkSphere.Shape();
    //const TopoDS_Shape& shape = mkBox.Shape();

    TColgp_Array1OfPnt controlPoints(1,4);

    controlPoints.SetValue(1,gp_Pnt(0.0,0.0,0.0));
    controlPoints.SetValue(2,gp_Pnt(1.0,0.0,1.0/3.0));
    controlPoints.SetValue(3,gp_Pnt(1.0,1.0,2.0/3.0));
    controlPoints.SetValue(4,gp_Pnt(1.0,1.0,1.0));

    Handle_Geom_Curve bezierCurve = new Geom_BezierCurve(controlPoints);
    //BRepBuilderAPI_MakeEdge mkBuilder(bezierCurve, bezierCurve->FirstParameter(), bezierCurve->LastParameter());
    BRepBuilderAPI_MakeEdge mkBuilder(bezierCurve);
    const TopoDS_Shape& shape = mkBuilder.Shape();

    setVtk(shape);
}


void CurvesSurfaces::setVtk(const TopoDS_Shape& shape)
{
    vtkNew<vtkNamedColors> colors;
    vtkNew<IVtkTools_ShapeDataSource> occSource;
    occSource->SetShape(new IVtkOCC_Shape(shape));

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(occSource->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> renderer;
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());

    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("CurvesSurfaces");

    this->ui->openGLWidget->setRenderWindow(renderWindow);

    vtkNew<vtkAxesActor> axes;
    double rgba[4]{0.0, 0.0, 0.0, 0.0};
    colors->GetColor("Carrot", rgba);
    this->widget->SetOutlineColor(rgba[0], rgba[1], rgba[2]);
    this->widget->SetOrientationMarker(axes);
    this->widget->SetInteractor(this->ui->openGLWidget->interactor());
    this->widget->SetViewport(0.0, 0.0, 0.2, 0.2);
    this->widget->SetEnabled(1);
    this->widget->InteractiveOn();

    renderer->GetActiveCamera()->Azimuth(50);
    renderer->GetActiveCamera()->Elevation(-30);

    renderer->ResetCamera();


    setCentralWidget(ui->openGLWidget);
    this->ui->openGLWidget->renderWindow()->Render();
    this->ui->openGLWidget->interactor()->Start();
}

void CurvesSurfaces::test()
{
    vtkNew<vtkNamedColors> colors;

    vtkNew<vtkSphereSource> sphereSource;
    sphereSource->Update();

    vtkNew<vtkPointPicker> pointPicker;

    // Create a mapper and actor
    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(sphereSource->GetOutputPort());
    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);
    actor->GetProperty()->SetColor(colors->GetColor3d("MistyRose").GetData());

    // Create a renderer, render window, and interactor
    vtkNew<vtkRenderer> renderer;
    vtkNew<vtkGenericOpenGLRenderWindow> renderWindow;
    renderWindow->AddRenderer(renderer);
    renderWindow->SetWindowName("PointPicker");

    this->ui->openGLWidget->interactor()->SetPicker(pointPicker);
    this->ui->openGLWidget->interactor()->SetRenderWindow(renderWindow);

    vtkNew<MouseInteractorStylePP> style;
    this->ui->openGLWidget->interactor()->SetInteractorStyle(style);

    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(colors->GetColor3d("SteelBlue").GetData());
    setCentralWidget(ui->openGLWidget);
    this->ui->openGLWidget->setRenderWindow(renderWindow);
    this->ui->openGLWidget->interactor()->Start();
}
