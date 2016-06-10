 QT += widgets \
         multimedia \
        sql
CONFIG += c++11

SOURCES += \
    main.cpp \
    qcomputer.cpp \
    computer.cpp \
    operatorFactory.cpp \
    operator.cpp \
    litterale.cpp \
    pile.cpp \
    operatorLogique.cpp \
    operatorAutre.cpp \
    operatorClassique.cpp \
    storage.cpp



HEADERS += \
    qcomputer.h \
    computer.h \
    operator.h \
    operatorFactory.h \
    litterale.h \
    pile.h \
    operatorAutre.h \
    operatorClassique.h \
    operatorLogique.h \
    storage.h

RESOURCES += \
    res.qrc

