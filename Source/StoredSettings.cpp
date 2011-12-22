/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#include "StoredSettings.h"

//==============================================================================
StoredSettings::StoredSettings()
: m_props (nullptr)
{
    flush();
}

StoredSettings::~StoredSettings()
{
    flush();
    m_props = nullptr;
    clearSingletonInstance();
}

juce_ImplementSingleton (StoredSettings);


//==============================================================================
PropertiesFile& StoredSettings::getProps()
{
    jassert (m_props != nullptr);
    return *m_props;
}

void StoredSettings::flush()
{
    if (m_props != nullptr)
    {
        m_props->setValue ("recentFiles", recentFiles.toString());
		//m_props->
    }
	
    m_props = nullptr;
	
	PropertiesFile::Options options;
	options.applicationName     = "GpxDBImporterExporter";
//    options.folderName          = "GpxDBImporterExporter";
    options.filenameSuffix      = "settings";
    options.osxLibrarySubFolder = "Application Support";

    m_props = new PropertiesFile (options);

	// recent files...
    recentFiles.restoreFromString (m_props->getValue ("recentFiles"));
    recentFiles.removeNonExistentFiles();
	
}

const String StoredSettings::getLastImportFolder() const 
{
	return m_props->getValue("lastImportFolder",
							 File::getSpecialLocation(File::userDesktopDirectory).getFullPathName());
}

void StoredSettings::setLastImportFolder (const String& folder)
{
	m_props->setValue("lastImportFolder", folder);
}

const String StoredSettings::getLastExportFolder() const 
{
	return m_props->getValue("lastExportFolder",
							 File::getSpecialLocation(File::userHomeDirectory).getFullPathName());
}

void StoredSettings::setLastExportFolder (const String& folder)
{
	m_props->setValue("lastExportFolder", folder);
}

bool StoredSettings::getSelectFolders() const
{
	return m_props->getBoolValue("selectFolder", false);
}
void StoredSettings::setSelectFolders (bool selectFolder)
{
	m_props->setValue("selectFolder", selectFolder);
}
