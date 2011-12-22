/*==========================================================
 Copyright (c) Peter Vasil, 2011
 ==========================================================*/

#include "includes.h"

class StoredSettings
{
public:
    //==============================================================================
    StoredSettings();
    ~StoredSettings();
	
    juce_DeclareSingleton (StoredSettings, false);
	
    PropertiesFile& getProps();
    void flush();
	
    //==============================================================================
    RecentlyOpenedFilesList recentFiles;
	
	const String getLastImportFolder() const;
    void setLastImportFolder (const String& folder);
	
	const String getLastExportFolder() const;
    void setLastExportFolder (const String& folder);

	bool getSelectFolders() const;
    void setSelectFolders (bool selectFoloder);
	
    //==============================================================================
    juce_UseDebuggingNewOperator
	
private:
    ScopedPointer<PropertiesFile> m_props;
	
};