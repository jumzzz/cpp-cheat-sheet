TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    threadsafe_stack.cpp


win32 {
    ## Windows common build here

    win32-msvc* {
        #MSVC_VER = $$(VisualStudioVersion) $$(BUILD_PROJ)


#        QT += webenginewidgets

        !contains(QT_ARCH, x86_64) {
            #message("  x86 build")
            #message("  MSVC_VER = $$MSVC_VER")

            ## Windows x86 (32bit) specific build here
            equals(MSVC_VER, 10.0){ message("  msvc 2010 32bit") }
            equals(MSVC_VER, 11.0){ message("  msvc 2012 32bit") }
            equals(MSVC_VER, 12.0){ message("  msvc 2013 32bit") }
            equals(MSVC_VER, 14.0){ message("  msvc 2015 32bit") }

        } else {
            CONFIG  +=  win64
            DEFINES += _WIN64
            #message("  x86_64 build")
            #message("  MSVC_VER = $$MSVC_VER")

            ## Windows x64 (64bit) specific build here
            equals(MSVC_VER, 10.0){ message("  msvc 2010 64bit") }
            equals(MSVC_VER, 11.0){ message("  msvc 2012 64bit") }
            equals(MSVC_VER, 12.0){ message("  msvc 2013 64bit") }
            equals(MSVC_VER, 14.0){ message("  msvc 2015 64bit") }

            INCLUDEPATH += "C:/Program Files (x86)/Windows Kits/10/Include/10.0.10240.0/ucrt"
            LIBS += -L"C:/Program Files (x86)/Windows Kits/10/Lib/10.0.10240.0/ucrt/x64"


        }
    } else {
        # gcc or g++ compiler
        #message(Qt version: $$[QT_VERSION])
        #message($$QMAKESPEC)

        QMAKE_CXXFLAGS += -std=c++11
        #QMAKE_CXXFLAGS += -O3 #enable compiler optimization.

#        QT += webenginewidgets
    }
}
win64 : message("  using win64 scope !!!")

HEADERS += \
    threadsafe_stack.h
