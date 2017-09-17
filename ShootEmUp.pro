TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

QMAKE_CFLAGS += -ansi -Wall -pedantic-errors


SOURCES += \
    Sources/animation.c \
    Sources/coldetect.c \
    Sources/main.c \
    Sources/ship.c \
    Sources/shooting.c \
    Sources/ui.c

DISTFILES += \
    Resources/Font/arial.ttf \
    Resources/Font/Consolas.ttf \
    Resources/sheet.xml \
    Resources/Background/blueFilled.png \
    Resources/Background/starfieldVFilled.png \
    Resources/redthruster.png \
    Resources/sheet.png


HEADERS += \
    Headers/animation.h \
    Headers/coldetect.h \
    Headers/ship.h \
    Headers/shooting.h \
    Headers/structs.h \
    Headers/ui.h


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

INCLUDEPATH += /usr/include/allegro5 \
    Headers
