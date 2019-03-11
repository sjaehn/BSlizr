BUNDLE = BSlizzr.lv2
INSTALL_DIR = /usr/lib/lv2
CC = g++
TK = src/BWidgets/DrawingSurface.cpp src/BWidgets/DisplayDial.cpp src/BWidgets/Dial.cpp src/BWidgets/DisplayVSlider.cpp src/BWidgets/VSlider.cpp src/BWidgets/VScale.cpp src/BWidgets/HSwitch.cpp src/BWidgets/DisplayHSlider.cpp src/BWidgets/HSlider.cpp src/BWidgets/HScale.cpp src/BWidgets/RangeWidget.cpp src/BWidgets/ValueWidget.cpp src/BWidgets/Knob.cpp src/BWidgets/Label.cpp src/BWidgets/FocusWidget.cpp src/BWidgets/Window.cpp src/BWidgets/Widget.cpp src/BWidgets/BStyles.cpp src/BWidgets/BColors.cpp src/BWidgets/BEvents.cpp src/BWidgets/BValues.cpp src/BWidgets/cairoplus.c src/BWidgets/pugl/pugl_x11.c

$(BUNDLE): clean BSlizzr.so BSlizzr_GUI.so
	cp manifest.ttl BSlizzr.ttl surface.png LICENSE $(BUNDLE)
	
all: $(BUNDLE)

BSlizzr.so: ./src/BSlizzr.cpp
	mkdir -p $(BUNDLE)
	$(CC) $< -o $(BUNDLE)/$@ -std=c++11 -shared -fvisibility=hidden -fPIC -DPIC `pkg-config --cflags --libs lv2`
	
BSlizzr_GUI.so: ./src/BSlizzr_GUI.cpp
	mkdir -p $(BUNDLE)	
	$(CC) $< $(TK) -o $(BUNDLE)/$@ -std=c++11 -shared -fvisibility=hidden -DPUGL_HAVE_CAIRO -fPIC -DPIC `pkg-config --cflags --libs lv2 x11 cairo`

install: $(BUNDLE)
	mkdir -p $(INSTALL_DIR)
	rm -rf $(INSTALL_DIR)/$(BUNDLE)
	cp -R $(BUNDLE) $(INSTALL_DIR)
	
.PHONY: all

clean:
	rm -rf $(BUNDLE)
