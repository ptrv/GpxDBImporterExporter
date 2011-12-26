# Automatically generated makefile, created by the Introjucer
# Don't edit this file! Your changes will be overwritten when you re-save the Introjucer project!

ifndef CONFIG
  CONFIG=Debug
endif

ifeq ($(TARGET_ARCH),)
  TARGET_ARCH := -march=native
endif

# (this disables dependency generation if multiple architectures are set)
DEPFLAGS := $(if $(word 2, $(TARGET_ARCH)), , -MMD)

ifeq ($(CONFIG),Debug)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Debug
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -g -ggdb -O0
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../Common/juce/bin" -lfreetype -lpthread -lrt -lX11 -lGL -lGLU -lXinerama -lasound -lXext 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "DEBUG=1" -D "_DEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode"
  TARGET := GpxDBImporterExporterD
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

ifeq ($(CONFIG),Release)
  BINDIR := build
  LIBDIR := build
  OBJDIR := build/intermediate/Release
  OUTDIR := build
  CPPFLAGS := $(DEPFLAGS) -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode"
  CFLAGS += $(CPPFLAGS) $(TARGET_ARCH) -Os
  CXXFLAGS += $(CFLAGS) 
  LDFLAGS += -L$(BINDIR) -L$(LIBDIR) -L"/usr/X11R6/lib/" -L"../../../Common/juce/bin" -lfreetype -lpthread -lrt -lX11 -lGL -lGLU -lXinerama -lasound -lXext 
  LDDEPS :=
  RESFLAGS :=  -D "LINUX=1" -D "NDEBUG=1" -D "JUCER_LINUX_MAKE_7346DA2A=1" -I "/usr/include" -I "/usr/include/freetype2" -I "../../JuceLibraryCode"
  TARGET := GpxDBImporterExporter
  BLDCMD = $(CXX) -o $(OUTDIR)/$(TARGET) $(OBJECTS) $(LDFLAGS) $(RESOURCES) $(TARGET_ARCH)
endif

OBJECTS := \
  $(OBJDIR)/HelpComponent_6b43a81d.o \
  $(OBJDIR)/DBConnector_8d9b4c70.o \
  $(OBJDIR)/FileExporter_a2d28b06.o \
  $(OBJDIR)/FileImporter_5bc57237.o \
  $(OBJDIR)/LocationUpdater_8275cdb5.o \
  $(OBJDIR)/Main_90ebc5c2.o \
  $(OBJDIR)/MainComponent_a6ffb4a5.o \
  $(OBJDIR)/StoredSettings_dfdf196f.o \
  $(OBJDIR)/sqlite3_60b4edb2.o \
  $(OBJDIR)/sqlite3x_command_3258e75c.o \
  $(OBJDIR)/sqlite3x_connection_ca02d237.o \
  $(OBJDIR)/sqlite3x_exception_45f76f60.o \
  $(OBJDIR)/sqlite3x_reader_36a7a39c.o \
  $(OBJDIR)/sqlite3x_transaction_98a90b6f.o \
  $(OBJDIR)/BinaryData_ce4232d4.o \
  $(OBJDIR)/juce_core_aff681cc.o \
  $(OBJDIR)/juce_cryptography_25c7e826.o \
  $(OBJDIR)/juce_data_structures_bdd6d488.o \
  $(OBJDIR)/juce_events_79b2840.o \
  $(OBJDIR)/juce_graphics_c8f1e7a4.o \
  $(OBJDIR)/juce_gui_basics_a630dd20.o \
  $(OBJDIR)/juce_gui_extra_7767d6a8.o \

.PHONY: clean

$(OUTDIR)/$(TARGET): $(OBJECTS) $(LDDEPS) $(RESOURCES)
	@echo Linking GpxDBImporterExporter
	-@mkdir -p $(BINDIR)
	-@mkdir -p $(LIBDIR)
	-@mkdir -p $(OUTDIR)
	@$(BLDCMD)

clean:
	@echo Cleaning GpxDBImporterExporter
	-@rm -f $(OUTDIR)/$(TARGET)
	-@rm -rf $(OBJDIR)/*
	-@rm -rf $(OBJDIR)

$(OBJDIR)/HelpComponent_6b43a81d.o: ../../Source/HelpComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling HelpComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/DBConnector_8d9b4c70.o: ../../Source/DBConnector.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling DBConnector.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileExporter_a2d28b06.o: ../../Source/FileExporter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileExporter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/FileImporter_5bc57237.o: ../../Source/FileImporter.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling FileImporter.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/LocationUpdater_8275cdb5.o: ../../Source/LocationUpdater.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling LocationUpdater.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/Main_90ebc5c2.o: ../../Source/Main.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling Main.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/MainComponent_a6ffb4a5.o: ../../Source/MainComponent.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling MainComponent.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/StoredSettings_dfdf196f.o: ../../Source/StoredSettings.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling StoredSettings.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3_60b4edb2.o: ../../Source/sqlite3x/sqlite3.c
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3.c"
	@$(CC) $(CFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3x_command_3258e75c.o: ../../Source/sqlite3x/sqlite3x_command.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3x_command.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3x_connection_ca02d237.o: ../../Source/sqlite3x/sqlite3x_connection.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3x_connection.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3x_exception_45f76f60.o: ../../Source/sqlite3x/sqlite3x_exception.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3x_exception.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3x_reader_36a7a39c.o: ../../Source/sqlite3x/sqlite3x_reader.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3x_reader.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/sqlite3x_transaction_98a90b6f.o: ../../Source/sqlite3x/sqlite3x_transaction.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling sqlite3x_transaction.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/BinaryData_ce4232d4.o: ../../JuceLibraryCode/BinaryData.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling BinaryData.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_core_aff681cc.o: ../../JuceLibraryCode/modules/juce_core/juce_core.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_core.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_cryptography_25c7e826.o: ../../JuceLibraryCode/modules/juce_cryptography/juce_cryptography.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_cryptography.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_data_structures_bdd6d488.o: ../../JuceLibraryCode/modules/juce_data_structures/juce_data_structures.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_data_structures.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_events_79b2840.o: ../../JuceLibraryCode/modules/juce_events/juce_events.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_events.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_graphics_c8f1e7a4.o: ../../JuceLibraryCode/modules/juce_graphics/juce_graphics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_graphics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_basics_a630dd20.o: ../../JuceLibraryCode/modules/juce_gui_basics/juce_gui_basics.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_basics.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

$(OBJDIR)/juce_gui_extra_7767d6a8.o: ../../JuceLibraryCode/modules/juce_gui_extra/juce_gui_extra.cpp
	-@mkdir -p $(OBJDIR)
	@echo "Compiling juce_gui_extra.cpp"
	@$(CXX) $(CXXFLAGS) -o "$@" -c "$<"

-include $(OBJECTS:%.o=%.d)
