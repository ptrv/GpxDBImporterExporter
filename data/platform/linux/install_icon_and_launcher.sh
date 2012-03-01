#!/bin/sh

BASEDIR=$(dirname $0)

ICON_PATH=$HOME/.local/share/icons
LAUNCHER_PATH=$HOME/.local/share/applications
BIN_PATH=$HOME/bin

echo "\nGpxDBImporterExporter installer :)\n"
echo "Install executable..."
mkdir -p $BIN_PATH
cp $BASEDIR/../../../Builds/Linux/build/GpxDBImporterExporter $BIN_PATH

echo "Install launcher..."
mkdir -p $LAUNCHER_PATH
cp $BASEDIR/gpxdbimporterexporter.desktop $LAUNCHER_PATH

echo "Install icon..."
mkdir -p $ICON_PATH
cp $BASEDIR/../../icon/gpxdbimporterexporter_icon.png $ICON_PATH

echo "Done."
