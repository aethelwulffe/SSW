#CXXFLAGS = -I../include -I/usr/local/lib/wx/include/gtk2-ansi-release-2.8 \
#            -I/usr/local/include/wx-2.8 \
#            -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXGTK__ -pthread -g 

#LIBS = -L/usr/local/lib -pthread -lwx_gtk2_richtext-2.8 -lwx_gtk2_aui-2.8 -lwx_gtk2_xrc-2.8 \
#       -lwx_gtk2_qa-2.8 -lwx_gtk2_html-2.8 -lwx_gtk2_adv-2.8 -lwx_gtk2_core-2.8 \
#       -lwx_base_xml-2.8 -lwx_base_net-2.8 -lwx_base-2.8

CXXFLAGS = -I../../include -g `wx-config-3.0 --cxxflags` -Wall -Woverloaded-virtual -DLINUX -fprofile-arcs -ftest-coverage

LIBS = `wx-config-3.0 --libs`

PICFLAGS = -fPIC -DPIC

#CXXFLAGS = -I../include -I/home/tstephen/src/wxGTK-2.8.7/buildgtkm/lib/wx/include/gtk2-ansi-release-static-2.8 -I/home/tstephen/src/wxGTK-2.8.7/include -I/home/tstephen/src/wxGTK-2.8.7/contrib/include -D_FILE_OFFSET_BITS=64 -D_LARGE_FILES -D__WXGTK__ -pthread -g
#LIBS = -L/home/tstephen/src/wxGTK-2.8.7/buildgtkm/lib -pthread   /home/tstephen/src/wxGTK-2.8.7/buildgtkm/lib/libwx_gtk2-2.8.a -pthread -L/lib -lgtk-x11-2.0 -lgdk-x11-2.0 -latk-1.0 -lgdk_pixbuf-2.0 -lm -lpango-1.0 -lgobject-2.0 -lgmodule-2.0 -ldl -lgthread-2.0 -lglib-2.0 -lXinerama -lXxf86vm -lSM -lwxregex-2.8 -lwxexpat-2.8 -lwxtiff-2.8 -lwxjpeg-2.8 -lwxpng-2.8 -lwxzlib-2.8 -ldl -lm

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

OBJS = BattleSimFrame.o LocalGameDialog.o ScenarioDialog.o ScenarioEditorGUI.o

TARGET = libbattleSim.a

all $(TARGET): $(OBJS)
	ar rcsu $(TARGET) $(OBJS)

	
objs: $(OBJS)
	rm -f *.gcda
	rm -f *.gcov
	rm -f *.gcno

.PHONY:
clean:
	rm -f $(OBJS)
	rm -f $(TARGET)


# DO NOT DELETE

BattleSimFrame.o: ../../include/battleSim/BattleSimFrame.h
BattleSimFrame.o: ../../include/battleSim/LocalGameDialog.h
LocalGameDialog.o: ../../include/battleSim/LocalGameDialog.h
LocalGameDialog.o: ../../include/battleSim/ScenarioDialog.h
LocalGameDialog.o: ../../include/battleSim/ScenarioEditorGUI.h
LocalGameDialog.o: ../../include/strategic/FFleet.h
LocalGameDialog.o: ../../include/core/FPObject.h ../../include/core/FObject.h
LocalGameDialog.o: ../../include/ships/FVehicle.h
LocalGameDialog.o: ../../include/core/FGameConfig.h
LocalGameDialog.o: ../../include/weapons/FWeapon.h
LocalGameDialog.o: ../../include/defenses/FDefense.h
ScenarioDialog.o: ../../include/battleSim/ScenarioDialog.h
ScenarioDialog.o: ../../include/tactical/FBattleScreen.h
ScenarioDialog.o: ../../include/Frontier.h ../../include/wxWidgets.h
ScenarioDialog.o: ../../include/tactical/FBattleBoard.h
ScenarioDialog.o: ../../include/strategic/FFleet.h
ScenarioDialog.o: ../../include/core/FPObject.h ../../include/core/FObject.h
ScenarioDialog.o: ../../include/ships/FVehicle.h
ScenarioDialog.o: ../../include/core/FGameConfig.h
ScenarioDialog.o: ../../include/weapons/FWeapon.h
ScenarioDialog.o: ../../include/defenses/FDefense.h
ScenarioDialog.o: ../../include/core/FPoint.h ../../include/core/FHexPath.h
ScenarioDialog.o: ../../include/core/FHexMap.h
ScenarioDialog.o: ../../include/tactical/FBattleDisplay.h
ScenarioEditorGUI.o: ../../include/battleSim/ScenarioEditorGUI.h
ScenarioEditorGUI.o: ../../include/strategic/FFleet.h
ScenarioEditorGUI.o: ../../include/core/FPObject.h
ScenarioEditorGUI.o: ../../include/core/FObject.h
ScenarioEditorGUI.o: ../../include/ships/FVehicle.h
ScenarioEditorGUI.o: ../../include/core/FGameConfig.h
ScenarioEditorGUI.o: ../../include/weapons/FWeapon.h
ScenarioEditorGUI.o: ../../include/defenses/FDefense.h
ScenarioEditorGUI.o: ../../include/tactical/FBattleScreen.h
ScenarioEditorGUI.o: ../../include/Frontier.h ../../include/wxWidgets.h
ScenarioEditorGUI.o: ../../include/tactical/FBattleBoard.h
ScenarioEditorGUI.o: ../../include/core/FPoint.h
ScenarioEditorGUI.o: ../../include/core/FHexPath.h
ScenarioEditorGUI.o: ../../include/core/FHexMap.h
ScenarioEditorGUI.o: ../../include/tactical/FBattleDisplay.h
