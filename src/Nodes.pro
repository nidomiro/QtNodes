QT	+= core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++14

TEMPLATE = lib

INCLUDEPATH += $$PWD
DESTDIR = $$PWD/../build

headerFiles.path = $$PWD/../build
headerFiles.files = $$PWD/*.h
INSTALLS += headerFiles

CONFIG(debug, debug|release) {
    mac: TARGET = $$join(TARGET,,,_debug)
    else: TARGET = $$join(TARGET,,,d)
 }

HEADERS += \
    connection.h \
    utils/color_utils.h \
    utils/math_util.h \
    iowidgets/qstring_io_graphics_widget.h \
    abstract_io_graphics_widget.h \
    connection_request.h \
    connector_graphics_widget.h \
    i_connection_register.h \
    node_graphics_widget.h \
    node_grid_scene.h \
    node_grid_view.h

SOURCES += \
    connection.cpp \
    iowidgets/qstring_io_graphics_widget.cpp \
    utils/color_utils.cpp \
    utils/math_util.cpp \
    abstract_io_graphics_widget.cpp \
    connection_request.cpp \
    connector_graphics_widget.cpp \
    node_graphics_widget.cpp \
    node_grid_scene.cpp \
    node_grid_view.cpp

FORMS +=




