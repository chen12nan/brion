#设置工程运行的时候搜索头文件路径

#greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
EPOINCLUDE =../../src

INCLUDEPATH += $$EPOINCLUDE/database\
               $$EPOINCLUDE/model\
               $$EPOINCLUDE/utility\
               $$EPOINCLUDE/weather\
               $$EPOINCLUDE/datetime\
               $$EPOINCLUDE/widgets


# 如果没有$$EPOINCLUDE/,那么就不能包含头文件。 #include<cfunction/EPCFunction.h>
# 因为头文件搜索路径不是从$$EPOINCLUDE 开始。


DESTDIR = $(HOME)/.build/lib
UI_DIR = .uidir
MOC_DIR = .moc
OBJECTS_DIR = .obj
RCC_DIR = .rcc

