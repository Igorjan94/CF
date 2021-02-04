 HEADERS       = chatdialog.h
 SOURCES       = \
                 main.cpp \
    chatdialog.cpp
 FORMS         = chatdialog.ui
 QT           += network widgets

 # install
 target.path = $$[QT_INSTALL_EXAMPLES]/network/network-chat
 sources.files = $$SOURCES $$HEADERS $$RESOURCES $$FORMS network-chat.pro *.chat
 sources.path = $$[QT_INSTALL_EXAMPLES]/network/network-chat
 INSTALLS += target sources

 symbian {
     include($$QT_SOURCE_TREE/examples/symbianpkgrules.pri)
     LIBS += -lcharconv
     TARGET.CAPABILITY = "NetworkServices ReadUserData WriteUserData"
     TARGET.EPOCHEAPSIZE = 0x20000 0x2000000
 }
 maemo5: include($$QT_SOURCE_TREE/examples/maemo5pkgrules.pri)

 symbian: warning(This example might not fully work on Symbian platform)
 maemo5: warning(This example might not fully work on Maemo platform)
