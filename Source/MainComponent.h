/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Feb 2012 9:17:32pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_DA2E8441__
#define __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_DA2E8441__

//[Headers]     -- You can add your own extra header files here --
#include "includes.h"
#include "DBConnector.h"
#include "HelpComponent.h"

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
	const std::vector<File> getFilesToImport();
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
	std::vector<String> m_selectedFilesToImport;
	bool m_selectFolder;
	String m_lastExportFolder;
	HelpComponent* m_helpComponent;

	void getAllCommands (Array <CommandID>& commands);
	const PopupMenu getMenuForIndex (int topLevelMenuIndex,
			const String& menuName);
	const StringArray getMenuBarNames();
	void getCommandInfo (CommandID commandID, ApplicationCommandInfo& result);
	ApplicationCommandTarget* getNextCommandTarget();
	void menuItemSelected (int menuItemID,
			int topLevelMenuIndex);
	bool perform (const InvocationInfo& info);

	enum CommandIDs
	{
		openDb					= 0x2000,
		openCreateNewDb			= 0x2001,
		openExecuteSql			= 0x2002,
		openUpdateLocations 	= 0x2003,
		showAbout              	= 0x2004,
		showHelp		       	= 0x2005
	};

	bool m_useNativeFileChooser;

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


#endif   // __JUCER_HEADER_MAINCOMPONENT_MAINCOMPONENT_DA2E8441__
