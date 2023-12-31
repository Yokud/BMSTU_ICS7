QT -= gui

CONFIG += c++17 console
CONFIG -= app_bundle

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    exceptions/exceptions.cpp \
    main.cpp \
    matrix/absmatrix.cpp \
    unit_tests/unittests.cpp

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    const_iterator/const_iterator.h \
    exceptions/exceptions.h \
    iterator/iterator.h \
    matrix/absmatrix.h \
    matrix/matrix.h \
    unit_tests/unittests.h \
    matrix/matrix_bool_methods.hpp \
    matrix/matrix_constrs.hpp \
    matrix/matrix_ins_del.hpp \
    matrix/matrix_iterator.hpp \
    matrix/matrix_math_methods.hpp \
    matrix/matrix_operators.hpp \
    matrix/matrix_private.hpp \
    matrix/matrix_row.hpp \
    iterator/iterator.hpp \
    const_iterator/const_iterator.hpp \
