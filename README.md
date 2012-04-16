# GpxDBImporterExporter

GpxDBImporterExporter is an application to import GPX files int an sqlite3 database for easy maintanance. You can also export the database back to a GPX file.

Thanks to Daniel Belasco Rogers for the location list.

## Release notes

### v1.6.0

* Bounding boxes of locations are now polygons instead of radius in degrees.
* New location resource format (GML).
* Import/export locations.
* Database statistics window.
* Faster location update.
* Fixes in database class.
* Unit testing.
* Linux install scripts.
* Application icon.
* Online help.

### v1.5.0

* Major GUI overhaul.
* Started with unit testing.
* A lot of under the hood stuff.

## Screenshot

![GpxDBImporterExporter](https://github.com/ptrv/GpxDBImporterExporter/raw/master/screenshot.png "GpxDBImporterExporter")

## Development

To change project properties, JUCE source code and Introjucer (JUCE's project creation tool) are required.

### Prerequisites

You can get the Introjucer by checking out the JUCE repository

    git clone --depth 1 git://juce.git.sourceforge.net/gitroot/juce/juce

and build Introjucer from source

    cd /path/to/JUCE
    cd extras/Introjucer/Builds/Linux (or MacOSX)
    make

run Introjucer

    build/Introjucer (or Xcode project file)

and open the GpxDBImporterExporter.jucer file to edit project settings.

### Building

#### Mac

There is an Xcode project file under `cd Builds/MacOSX/`.

#### Linux

    cd Builds/Linux
    make

For an optimized release version without debugging symbols and debug console text.

    cd Builds/Linux
    make CONFIG=Release


## TODOs

* Integrate libspatialite
* Option for spatialite database
* More unit testing
* More locations in GML format
* Refactor MainComponent, FileImporter and FileExporter
* Better debug messages

