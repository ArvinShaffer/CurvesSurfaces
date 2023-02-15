QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += /usr/local/include/vtk-9.1 \
                /usr/local/include/opencascade

LIBS += -L/usr/local/lib  \
  -lTKG3d \
  -lvtkFiltersCore-9.1 \
  -lvtkCommonDataModel-9.1 \
  -lvtkCommonExecutionModel-9.1 \
  -lvtkCommonColor-9.1 \
  -lvtkCommonCore-9.1 \
  -lvtkFiltersSources-9.1 \
  -lvtkInteractionStyle-9.1 \
  -lvtkRenderingContextOpenGL2-9.1 \
  -lvtkRenderingCore-9.1 \
  -lvtkRenderingFreeType-9.1 \
  -lvtkRenderingGL2PSOpenGL2-9.1 \
  -lvtkRenderingOpenGL2-9.1 \
  -lvtkGUISupportQt-9.1 \
  -lvtkInteractionWidgets-9.1 \
  -lvtkRenderingAnnotation-9.1 \
  -lTKPrim \
  -lTKIVtk \
  -lTKMath \
  -lTKernel \
  -lTKTopAlgo \
  -lTKGeomAlgo \
  -lTKV3d \



SOURCES += \
    main.cpp \
    curvessurfaces.cpp

HEADERS += \
    curvessurfaces.h

FORMS += \
    curvessurfaces.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
