QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    mainwindow.cpp

HEADERS += \
    ../img_proc/profile.h \
    garbage.h \
    mainwindow.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../../../OpenCV/build/install/x64/vc16/lib/ -lopencv_world452
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../../../OpenCV/build/install/x64/vc16/lib/ -lopencv_world452d
else:unix: LIBS += -L$$PWD/../../../OpenCV/build/install/x64/vc16/lib/ -lopencv_world452

INCLUDEPATH += $$PWD/../../../OpenCV/build/install/include
DEPENDPATH += $$PWD/../../../OpenCV/build/install/include

DISTFILES += \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/1_pipe.jpg \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/2_pipe.jpeg \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/3_pipe.jpeg \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2906.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2907.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2908.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2909.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2910.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2911.JPG \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2912.MOV \
    ../build-numbers_recognition-Desktop_Qt_5_15_1_MSVC2019_64bit-Debug/resources/IMG_2915.MOV
