TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ansi -Wall -pedantic-errors


SOURCES += main.c \
    coldetect.c

DISTFILES += \
    sheet.png \
    sheet.xml


HEADERS += \
    coldetect.h \
    structs.h


LIBS += -L/usr/lib \
    -lallegro \
    -lallegro_acodec \
    -lallegro_audio \
    -lallegro_color \
    -lallegro_dialog \
    -lallegro_font \
    -lallegro_image \
    -lallegro_main \
    -lallegro_memfile \
    -lallegro_physfs \
    -lallegro_primitives \
    -lallegro_ttf

INCLUDEPATH += /usr/include/allegro5
