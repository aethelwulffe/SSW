CXXFLAGS = -I../include -I../../src/include -g `wx-config --cxxflags` -Wall -Woverloaded-virtual -DLINUX -fprofile-arcs -ftest-coverage

LIBS = `wx-config --libs` -L./weapons -lweaponsTests -L./core -lcoreTests \
       -lcppunit -L../src/strategic -lstrategic -L../src/gui -lgui -L../src/ships -lships \
       -L../src/tactical -ltactical -L../src/weapons -lweapons -L../src/core -lcore 
       

#################### the implicit rules #############################

# NB: we use the old style suffix rules (.c.o) and not the GNU make
#     implicit rules (%.o: %.c) because they are more portable, in
#     particular the BSD make understands the former but not the
#     latter
.SUFFIXES: .o .c .cpp .cxx .rsrc .r

.c.o:
	$(CC) -c $(CFLAGS) $(PICFLAGS) -o $@ $<

.cpp.o:
	$(CXX) -c $(CXXFLAGS) $(PICFLAGS) -o $@ $<

.cxx.o:
	$(CXX) -c $(CXXFLAGS) $(PICFLAGS) -o $@ $<

.rsrc.r:
	$(DEREZ) $^ Carbon.r -useDF > $@

############################# Paths #################################

OBJS = SSWTests.o #FPointTest.o FObjectTest.o FWeaponTest.o #FApp.o Frontier.o FMainFrame.o

OBJ_LIBS = libcoreTests.a libweaponsTests.a #libguiTests.a libshipsTests.a libstrategicTests.a libtacticalTests.a

TARGET = SSWTests

all: $(OBJ_LIBS) $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LIBS)

libcoreTests.a:
	@ cd core; $(MAKE) $@
	
libguiTests.a:
	@ cd gui; $(MAKE) $@
	
libshipsTests.a:
	@ cd ships; $(MAKE) $@
	
libstrategicTests.a:
	@ cd strategic; $(MAKE) $@
	
libtacticalTests.a:
	@ cd tactical; $(MAKE) $@
	
libweaponsTests.a:
	@ cd weapons; $(MAKE) $@
	
objs: $(OBJS)
	rm *.gcda
	rm *.gcov
	rm *.gcno

.PHONY:
all_clean:
	@ cd core; ${MAKE} clean
#	@ cd gui; ${MAKE} clean
#	@ cd ships; ${MAKE} clean
#	@ cd strategic; ${MAKE} clean
#	@ cd tactical; ${MAKE} clean
	@ cd weapons; ${MAKE} clean
	rm $(OBJS)
	rm $(TARGET)
	
clean:
	rm $(OBJS)
	rm $(TARGET)


# DO NOT DELETE

SSWTests.o: core/FPointTest.h ../include/core/FPoint.h core/FObjectTest.h
SSWTests.o: ../include/core/FObject.h weapons/FWeaponTest.h
SSWTests.o: ../include/weapons/FWeapon.h ../include/core/FPObject.h
SSWTests.o: ../include/core/FObject.h