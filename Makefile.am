#AWE-4000R Project
bin_PROGRAMS = awe4000r

FLTFLAGS = -s 65536 
export FLTFLAGS

awe4000r_SOURCES = main.cpp

EXTRA_DIST = main.cpp

awe4000r_LDADD = ./APP/libaweapp.a ./APP/PROGRAM/libaweprg.a ./APP/SALE/libawesale.a ./APP/INVMANAGE/libaweinv.a ./APP/REPORT/libawerpt.a ./APP/MAINTAIN/libawemtn.a ./APP/API/libaweapi.a ./APP/FISCAL/libawefiscal.a ./APP/COMMON/libawecommon.a ./APP/YWXML/libaweywxml.a ./APP/NETMODULE/libnetmodule.a ./APP/SERIAL/libserial.a ./GUI/libawegui.a ./DB/libawedb.a ./TPL/libawetpl.a ./DRV/libawedrv.a ./SYS/libawesys.a ./LIB/libsqlite3.a ./LIB/libpthread.a ./LIB/libz.a


SUBDIRS = SYS LIB GUI DB TPL APP DRV 

INCLUDES = -I./SYS -I./LIB -I./GUI -I./DB -I./DRV -I./TPL -I./APP  -I./APP/INVMANAGE -I./APP/MAINTAIN  -I./APP/FISCAL -I./APP/PROGRAM -I./APP/REPORT -I./APP/SALE  -I./APP/COMMON -I./APP/YWXML -I./APP/SERIAL -I./APP/API -I./APP/NETMODULE -I./APP/NETMODULE/proc -I./APP/NETMODULE/gui_net
