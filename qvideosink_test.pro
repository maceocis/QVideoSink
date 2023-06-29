TEMPLATE = app
TARGET = qvideosink_test

QT += qml multimedia multimedia-private quick

CONFIG += c++11
CONFIG += link_pkgconfig debug

QT_CONFIG -= no-pkg-config
PKGCONFIG = \
    gstreamer-1.0 \
    gstreamer-video-1.0 \
    gstreamer-app-1.0 \

HEADERS += producer.h \
    gstpipeline.h \
    rendyboi.h \
    videoBuffer.h
SOURCES += main.cpp producer.cpp \
    gstpipeline.cpp \
    rendyboi.cpp \
    videoBuffer.cpp
RESOURCES += qml.qrc

# Default rules for deployment.
unix:!android: target.path = /root
!isEmpty(target.path): INSTALLS += target
