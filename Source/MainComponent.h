/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Feb 2012 2:01:58pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_AF64F8FD__
#define __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_AF64F8FD__

//[Headers]     -- You can add your own extra header files here --
#include "includes.h"
#include "DBConnector.h"
#include "HelpComponent.h"
#include "DBStatsComponent.h"

class MainWindow;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class MainComponent  : public Component,
                       public ButtonListener,
                       public MenuBarModel,
                       public ApplicationCommandTarget,
                       public ComboBoxListener
{
public:
    //==============================================================================
    MainComponent (MainWindow* mainWindow);
    ~MainComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
	const File getFileToImport();
	const Array<File> getFilesToImport();
	void createNewDb();
	void selectFileToImport();
	void importFile();
	void executeSqlScript();
	void updateLocations();
	const String& getDbPath();
	void setStatusMessage(const String& statusMessage);
	void showAboutWindow();
	void exportGpxFile();
	void buttonClicked (Button* buttonThatWasClicked);
	void showHelpWindow();
	void openDatabase(const File& file);
	void openDbFileChooser();
	void setCurrentWorkingDb(const File& file);
    void toggleUseLastDB();
    void toggleRadiusDegree();
    const char getBoundingsType();
    void exportLocations();
    void importLocations();
    void showOnlineHelp();
    void showDBStats();
    void setDBStats();
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();
    void comboBoxChanged (ComboBox* comboBoxThatHasChanged);



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.

    MainWindow* m_mainWindow;
	//DBConnector* m_dbCon;
	String m_lastImportedFile;
	String m_dbPath;
	int m_selectedUser;
	String m_lastImportFolder;
	String m_selectedFileToImport;
	Array<String> m_selectedFilesToImport;
	bool m_selectFolder;
	String m_lastExportFolder;
    String m_lastDBFolder;
	HelpComponent* m_helpComponent;
	DBStatsComponent* m_dbStatsComp;

	void getAllCommands (Array <CommandID>& commands);
	PopupMenu getMenuForIndex (int topLevelMenuIndex, const String& menuName);
	StringArray getMenuBarNames();
	void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);
	ApplicationCommandTarget* getNextCommandTarget();
	void menuItemSelected (int menuItemID,
			int topLevelMenuIndex);
	bool perform (const InvocationInfo& info);

	enum CommandIDs
	{
		openDb					= 0x2000,
		openCreateNewDb			= 0x2001,
        useLastDatabase         = 0x2002,
        useOldStyleRadius		= 0x2003,
		openExecuteSql			= 0x2004,
		openUpdateLocations 	= 0x2005,
		showAbout              	= 0x2006,
		showHelp		       	= 0x2007,
		openExportLocations		= 0x2008,
		openImportLocations		= 0x2009,
		openOnlineHelp			= 0x2010,
		openDBStats				= 0x2011
	};

	bool m_useNativeFileChooser;
    bool m_useLastDB;
    bool m_useRadiusDegree;

//    char m_boundingsType;
    //[/UserVariables]

    //==============================================================================
    TextButton* m_btFileImport;
    Label* m_labelName;
    ComboBox* m_userSelectComboBox;
    ToggleButton* m_btHashCheck;
    TextButton* m_btSelectFile;
    ToggleButton* m_btSelectFolder;
    TextEditor* m_sqlQuery;
    Label* m_labelImport;
    Label* m_labelExport;
    TextButton* m_btExport;
    Label* m_labelSqlQuery;
    Label* m_currentDbLabel;
    Label* m_statusLabel;
    Label* m_currentDbLabelTitle;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    MainComponent (const MainComponent&);
    const MainComponent& operator= (const MainComponent&);
};


#endif   // __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_AF64F8FD__
