/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  2 Feb 2012 11:01:52pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
#include "FileImporter.h"
#include "FileExporter.h"
#include "LocationUpdater.h"
#include "StoredSettings.h"
#include "MainWindow.h"
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent (MainWindow* mainWindow)
    : m_mainWindow(mainWindow),
      m_lastImportedFile(String::empty),
      m_dbPath(String::empty),
      m_selectedUser(0),
      m_lastImportFolder(String::empty),
      m_selectedFileToImport(String::empty),
      m_selectFolder(false),
      m_lastExportFolder(String::empty),
      m_btFileImport (0),
      m_labelName (0),
      m_userSelectComboBox (0),
      m_btHashCheck (0),
      m_btSelectFile (0),
      m_btSelectFolder (0),
      m_sqlQuery (0),
      m_labelImport (0),
      m_labelExport (0),
      m_btExport (0),
      m_labelSqlQuery (0),
      m_currentDbLabel (0),
      m_statusLabel (0),
      m_currentDbLabelTitle (0)
{
    addAndMakeVisible (m_btFileImport = new TextButton (L"btFileImport"));
    m_btFileImport->setButtonText (L"Import");
    m_btFileImport->setColour (TextButton::buttonColourId, Colour (0xffab5757));
    m_btFileImport->setColour (TextButton::buttonOnColourId, Colour (0xff003c00));

    addAndMakeVisible (m_labelName = new Label (L"labelName",
                                                L"Name"));
    m_labelName->setFont (Font (15.0000f, Font::plain));
    m_labelName->setJustificationType (Justification::centredLeft);
    m_labelName->setEditable (false, false, false);
    m_labelName->setColour (TextEditor::textColourId, Colours::black);
    m_labelName->setColour (TextEditor::backgroundColourId, Colour (0x0));
    m_labelName->setColour (TextEditor::highlightColourId, Colours::green);

    addAndMakeVisible (m_userSelectComboBox = new ComboBox (L"userSelectComboBox"));
    m_userSelectComboBox->setEditableText (true);
    m_userSelectComboBox->setJustificationType (Justification::centredLeft);
    m_userSelectComboBox->setTextWhenNothingSelected (String::empty);
    m_userSelectComboBox->setTextWhenNoChoicesAvailable (L"(no choices)");
    m_userSelectComboBox->addListener (this);

    addAndMakeVisible (m_btHashCheck = new ToggleButton (L"btHashCheck"));
    m_btHashCheck->setButtonText (L"Check md5");
    m_btHashCheck->setToggleState (true, false);

    addAndMakeVisible (m_btSelectFile = new TextButton (L"SelectFile"));
    m_btSelectFile->setButtonText (L"Select file");

    addAndMakeVisible (m_btSelectFolder = new ToggleButton (L"btSelectFolder"));
    m_btSelectFolder->setButtonText (L"Recursive import");

    addAndMakeVisible (m_sqlQuery = new TextEditor (L"sqlQuery"));
    m_sqlQuery->setMultiLine (true);
    m_sqlQuery->setReturnKeyStartsNewLine (true);
    m_sqlQuery->setReadOnly (false);
    m_sqlQuery->setScrollbarsShown (true);
    m_sqlQuery->setCaretVisible (true);
    m_sqlQuery->setPopupMenuEnabled (true);
    m_sqlQuery->setText (String::empty);

    addAndMakeVisible (m_labelImport = new Label (L"labelImport",
                                                  L"IMPORT"));
    m_labelImport->setFont (Font (24.0000f, Font::plain));
    m_labelImport->setJustificationType (Justification::centred);
    m_labelImport->setEditable (false, false, false);
    m_labelImport->setColour (TextEditor::textColourId, Colours::black);
    m_labelImport->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_labelExport = new Label (L"labelExport",
                                                  L"EXPORT"));
    m_labelExport->setFont (Font (24.0000f, Font::plain));
    m_labelExport->setJustificationType (Justification::centred);
    m_labelExport->setEditable (false, false, false);
    m_labelExport->setColour (TextEditor::textColourId, Colours::black);
    m_labelExport->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_btExport = new TextButton (L"btExport"));
    m_btExport->setButtonText (L"Export GPX file");
    m_btExport->setColour (TextButton::buttonColourId, Colour (0xff00bf00));
    m_btExport->setColour (TextButton::buttonOnColourId, Colours::green);

    addAndMakeVisible (m_labelSqlQuery = new Label (L"labelSqlQuery",
                                                    L"Enter SQL query (beginning with WHERE statement):"));
    m_labelSqlQuery->setFont (Font (15.0000f, Font::plain));
    m_labelSqlQuery->setJustificationType (Justification::centredLeft);
    m_labelSqlQuery->setEditable (false, false, false);
    m_labelSqlQuery->setColour (TextEditor::textColourId, Colours::black);
    m_labelSqlQuery->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_currentDbLabel = new Label (L"currentDbLabel",
                                                     L"no database"));
    m_currentDbLabel->setFont (Font (15.0000f, Font::plain));
    m_currentDbLabel->setJustificationType (Justification::centredLeft);
    m_currentDbLabel->setEditable (false, false, false);
    m_currentDbLabel->setColour (TextEditor::textColourId, Colours::black);
    m_currentDbLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_statusLabel = new Label (L"statusLabel",
                                                  String::empty));
    m_statusLabel->setFont (Font (15.0000f, Font::plain));
    m_statusLabel->setJustificationType (Justification::centredLeft);
    m_statusLabel->setEditable (false, false, false);
    m_statusLabel->setColour (TextEditor::textColourId, Colours::black);
    m_statusLabel->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_currentDbLabelTitle = new Label (L"currentDbLabelTitle",
                                                          L"DB:"));
    m_currentDbLabelTitle->setFont (Font (15.0000f, Font::plain));
    m_currentDbLabelTitle->setJustificationType (Justification::centredLeft);
    m_currentDbLabelTitle->setEditable (false, false, false);
    m_currentDbLabelTitle->setColour (TextEditor::textColourId, Colours::black);
    m_currentDbLabelTitle->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
	m_btFileImport->addListener (this);
	m_btHashCheck->addListener (this);
	m_btSelectFile->addListener (this);
	m_btSelectFolder->addListener (this);
	m_btExport->addListener (this);

	m_userSelectComboBox->setEnabled(false);
	m_btSelectFile->setEnabled(false);
	m_btFileImport->setEnabled(false);
	DBG_SCOPE();

#ifdef JUCE_LINUX
	m_useNativeFileChooser = false;
#else
	m_useNativeFileChooser = true;
#endif
    //[/UserPreSize]

    setSize (630, 300);


    //[Constructor] You can add your own custom stuff here..
    setStatusMessage("Ready to import!");

	m_lastImportFolder = StoredSettings::getInstance()->getLastImportFolder();
	m_btSelectFolder->setToggleState(StoredSettings::getInstance()->getSelectFolders(), false);
	m_lastExportFolder = StoredSettings::getInstance()->getLastExportFolder();
    m_useLastDB = StoredSettings::getInstance()->useLastDatabase();
    m_lastDBFolder = StoredSettings::getInstance()->getLastDBFolder();

	m_helpComponent = new HelpComponent();
    
    if (m_useLastDB) 
    {
        if (StoredSettings::getInstance()->recentFiles.getNumFiles() > 0) 
        {
            openDatabase(File(StoredSettings::getInstance()->recentFiles.getFile(0)));
        }
    }
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	StoredSettings::getInstance()->setLastImportFolder(m_lastImportFolder);
	StoredSettings::getInstance()->setSelectFolders(m_btSelectFolder->getToggleState());
	StoredSettings::getInstance()->setLastExportFolder(m_lastExportFolder);
    StoredSettings::getInstance()->useLastDatabase(m_useLastDB);
    StoredSettings::getInstance()->setLastDBFolder(m_lastDBFolder);
    
	StoredSettings::deleteInstance();

    //[/Destructor_pre]

    deleteAndZero (m_btFileImport);
    deleteAndZero (m_labelName);
    deleteAndZero (m_userSelectComboBox);
    deleteAndZero (m_btHashCheck);
    deleteAndZero (m_btSelectFile);
    deleteAndZero (m_btSelectFolder);
    deleteAndZero (m_sqlQuery);
    deleteAndZero (m_labelImport);
    deleteAndZero (m_labelExport);
    deleteAndZero (m_btExport);
    deleteAndZero (m_labelSqlQuery);
    deleteAndZero (m_currentDbLabel);
    deleteAndZero (m_statusLabel);
    deleteAndZero (m_currentDbLabelTitle);


    //[Destructor]. You can add your own custom destruction code here..
	deleteAndZero(m_helpComponent);
    //[/Destructor]
}

//==============================================================================
void MainComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff959d9d));

    g.setColour (Colour (0xffa9c0b6));
    g.fillRoundedRectangle (344.0f, 46.0f, 271.0f, 195.0f, 10.0000f);

    g.setColour (Colour (0xffb8c4c7));
    g.fillRoundedRectangle (18.0f, 46.0f, 302.0f, 195.0f, 10.0000f);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void MainComponent::resized()
{
    m_btFileImport->setBounds (32, 208, 272, 23);
    m_labelName->setBounds (256, 80, 56, 29);
    m_userSelectComboBox->setBounds (40, 83, 192, 23);
    m_btHashCheck->setBounds (176, 120, 104, 23);
    m_btSelectFile->setBounds (32, 168, 272, 23);
    m_btSelectFolder->setBounds (32, 120, 130, 23);
    m_sqlQuery->setBounds (360, 107, 240, 87);
    m_labelImport->setBounds (16, 51, 320, 23);
    m_labelExport->setBounds (376, 56, 216, 23);
    m_btExport->setBounds (360, 208, 240, 23);
    m_labelSqlQuery->setBounds (352, 83, 256, 23);
    m_currentDbLabel->setBounds (56, 8, 552, 24);
    m_statusLabel->setBounds (24, 248, 584, 24);
    m_currentDbLabelTitle->setBounds (23, 8, 40, 24);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void MainComponent::comboBoxChanged (ComboBox* comboBoxThatHasChanged)
{
    //[UsercomboBoxChanged_Pre]
    //[/UsercomboBoxChanged_Pre]

    if (comboBoxThatHasChanged == m_userSelectComboBox)
    {
        //[UserComboBoxCode_m_userSelectComboBox] -- add your combo box handling code here..
        //[/UserComboBoxCode_m_userSelectComboBox]
    }

    //[UsercomboBoxChanged_Post]
    //[/UsercomboBoxChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
	if (buttonThatWasClicked == m_btFileImport)
	{
		importFile();
	}
	else if (buttonThatWasClicked == m_btHashCheck)
	{
	}
	else if (buttonThatWasClicked == m_btSelectFile)
	{
		selectFileToImport();
	}
	else if (buttonThatWasClicked == m_btSelectFolder)
	{
	}
	else if (buttonThatWasClicked == m_btExport)
	{
		exportGpxFile();
	}
}

void MainComponent::selectFileToImport()
{
	m_selectedFilesToImport.clear();



	if(m_btSelectFolder->getToggleState())
	{
		FileChooser importDialog("Please select folder with gpx files...",
				File(m_lastImportFolder), "*.gpx", m_useNativeFileChooser);
		if (importDialog.browseForDirectory())
		{
			File importDir (importDialog.getResult());

			DirectoryIterator dirIter(importDir, true, "*.gpx");
			//            bool isBtEnabled = false;
			while(dirIter.next())
			{
				File importFile (dirIter.getFile());
				if(importFile.existsAsFile() && importFile.getFileExtension() == ".gpx")
				{
					m_selectedFileToImport = importFile.getFullPathName();
					m_selectedFilesToImport.push_back(m_selectedFileToImport);
					m_lastImportedFile = importFile.getFileName();
				}
			}
			m_lastImportFolder = importDir.getFullPathName();
			setStatusMessage("Selected file: " + m_lastImportedFile);
			m_btFileImport->setEnabled(true);
			repaint();
		}
	}
	else
	{
		FileChooser importDialog("Please select gpx files...",
				File(m_lastImportFolder), "*.gpx", m_useNativeFileChooser);
		if (importDialog.browseForMultipleFilesToOpen())
		{
			for(int i = 0; i < importDialog.getResults().size(); ++i)
			{
				File importFile (importDialog.getResults()[i]);
				if (importFile.existsAsFile() && importFile.getFileExtension() == ".gpx")
				{
					m_selectedFileToImport = importFile.getFullPathName();
					m_selectedFilesToImport.push_back(m_selectedFileToImport);
					m_lastImportedFile = importFile.getFileName();
					m_lastImportFolder = importFile.getParentDirectory().getFullPathName();
					setStatusMessage("Selected file: " + m_lastImportedFile);
					m_btFileImport->setEnabled(true);
				}
				else
				{
					m_btFileImport->setEnabled(false);
					setStatusMessage("The selected file was not valid!");
				}

			}
		}
	}
}
const File MainComponent::getFileToImport()
{
	File fileToImport(m_selectedFileToImport);
	return fileToImport;
}

const std::vector<File> MainComponent::getFilesToImport()
{
	std::vector<File> filesToImport;
	for(unsigned int i = 0; i < m_selectedFilesToImport.size(); ++i)
	{
		File fileToImport(m_selectedFilesToImport[i]);
		filesToImport.push_back(fileToImport);
	}
	return filesToImport;
}
void MainComponent::createNewDb()
{
	FileChooser saveDialog ("Please select the file to save new database to...",
			File::getSpecialLocation (File::userHomeDirectory),
			"*.sqlite;*.db", m_useNativeFileChooser);

	if (saveDialog.browseForFileToSave(true))
	{
		if (saveDialog.getResult().exists())
		{
			saveDialog.getResult().deleteFile();
		}
		File dbFile(saveDialog.getResult());

		setCurrentWorkingDb(dbFile);

		DBConnector* dbCon = new DBConnector(dbFile.getFullPathName());
		dbCon->setupDbConnection();
		dbCon->createNewDb();
		dbCon->insertLocationData();
		dbCon->closeDbConnection();
		delete dbCon;
	}
}

void MainComponent::setCurrentWorkingDb(const File& file)
{
	m_dbPath = file.getFullPathName();
	m_currentDbLabel->setText(m_dbPath, true);
	StoredSettings::getInstance()->recentFiles.addFile(file);
	m_userSelectComboBox->setEnabled(true);
	m_btSelectFile->setEnabled(true);
    m_lastDBFolder = file.getParentDirectory().getFullPathName();
	DBG_VAL(m_dbPath);
}
void MainComponent::openDatabase(const File& file)
{
	if (file.existsAsFile())
	{
		setCurrentWorkingDb(file);

		DBConnector* dbCon = new DBConnector(m_dbPath);
		dbCon->setupDbConnection();

		std::vector<String> users;
		m_userSelectComboBox->clear();
		if (dbCon->getAvailableUsers(users))
		{
			for (unsigned int i = 0; i < users.size(); ++i)
			{
				m_userSelectComboBox->addItem(users[i], i+1);
			}
		}
		dbCon->closeDbConnection();
		m_userSelectComboBox->setSelectedId(1);
		delete dbCon;
	}
	else
	{
		m_dbPath = String::empty;
		m_currentDbLabel->setText("no working database", true);
		m_userSelectComboBox->setEnabled(false);
		m_btSelectFile->setEnabled(false);
	}
}

void MainComponent::importFile()
{

	if(m_userSelectComboBox->getSelectedId() == 0)
	{
		String tmpUsertext = m_userSelectComboBox->getText();
		// small hack for empty combobox
		if(tmpUsertext[0] == '\0')
		{
			String title = "Error";
			String message = "You have to enter a name!";
			AlertWindow::showMessageBox(AlertWindow::WarningIcon, title, message, "OK");
			return;
		}
		DBConnector* dbCon = new DBConnector(m_dbPath);
		dbCon->setupDbConnection();
		int userid = -1;
		dbCon->getLastId(userid, "user");
		if(userid == -1){
			++userid;
		}
		++userid;
		if (!dbCon->checkIfUserExists(tmpUsertext))
		{
			dbCon->insertUser(userid, tmpUsertext);
			int numItems = m_userSelectComboBox->getNumItems();
			m_userSelectComboBox->addItem(tmpUsertext, numItems+1);
			m_userSelectComboBox->setSelectedId(numItems+1, true);
		}
		dbCon->closeDbConnection();
		delete dbCon;
	}

	FileImporter fileImporter(m_dbPath,
			getFilesToImport(),
			m_userSelectComboBox->getSelectedId(),
			m_btHashCheck->getToggleState(),
			false);
	DBG_VAL(m_btHashCheck->getToggleState());
	if (fileImporter.runThread())
	{
		setStatusMessage(fileImporter.getStatus());
	}
	else
	{
		setStatusMessage("Import canceled!");
	}
}

void MainComponent::updateLocations()
{
	LocationUpdater locationUpdater(m_dbPath);

	if (locationUpdater.runThread())
	{
		setStatusMessage(locationUpdater.getStatus());
	}
	else
	{
	}
}

void MainComponent::executeSqlScript()
{
	FileChooser sqlScriptChooser("Please select the sql file to execute...",
			File::getSpecialLocation (File::userHomeDirectory),
			"*.sql", m_useNativeFileChooser);
	if (sqlScriptChooser.browseForFileToOpen())
	{
		File sqlFile (sqlScriptChooser.getResult());
		if (sqlFile.existsAsFile() && sqlFile.getFileExtension() == ".sql")
		{
			DBConnector dbcon(m_dbPath);
			dbcon.setupDbConnection();
			dbcon.executeSqlScript(sqlFile);
			dbcon.closeDbConnection();
			setStatusMessage("Executed SQL script!");
		}
		else
		{
			setStatusMessage("File not valid!");
		}
	}
}
void MainComponent::setStatusMessage(const String& statusMessage)
{
	m_statusLabel->setText(statusMessage, true);
}
void MainComponent::showAboutWindow()
{
	String title = ProjectInfo::projectName;
	title << " Version " << ProjectInfo::versionString;
	String message = RC_COMPANY_STR;
	message += ". All rights reserved.\nhttp://petervasil.net";
	AlertWindow::showMessageBox(AlertWindow::InfoIcon, title, message, "OK");
}

void MainComponent::exportGpxFile()
{
	FileChooser gpxExportChooser("",
			File(m_lastExportFolder),
			"*.gpx", m_useNativeFileChooser);
	if (gpxExportChooser.browseForFileToSave(true))
	{
		File gpxExportFile (gpxExportChooser.getResult());

		if (gpxExportFile.existsAsFile())
		{
			gpxExportFile.deleteFile();
		}

		m_lastExportFolder = gpxExportFile.getParentDirectory().getFullPathName();

		DBG_VAL(m_sqlQuery->getText());
		FileExporter fileExporter(m_dbPath, gpxExportFile.getFullPathName(),
				m_sqlQuery->getText());

		if (fileExporter.runThread())
		{
			setStatusMessage(fileExporter.getStatus());
		}
		else
		{
		}
	}
}

void MainComponent::showHelpWindow()
{
	Colour color(0,0,0);
	DialogWindow::showModalDialog("Help", m_helpComponent, nullptr, color, true);
}

void MainComponent::openDbFileChooser()
{
	FileChooser dbChooser("Select a database file...", File::nonexistent,
			"*.sqlite;*.db", m_useNativeFileChooser);

	if (dbChooser.browseForFileToOpen()) {
		openDatabase(dbChooser.getResult());
	} else {

	}
}

void MainComponent::toggleUseLastDB()
{
    m_useLastDB = !m_useLastDB;
    StoredSettings::getInstance()->useLastDatabase(m_useLastDB);
}

const StringArray MainComponent::getMenuBarNames()
{
	const char* const names[] = { "Database", "Tools", "Help", nullptr };

	return StringArray (names);
}

const PopupMenu MainComponent::getMenuForIndex (int menuIndex, const String& /*menuName*/)
{
	ApplicationCommandManager* commandManager = &m_mainWindow->commandManager;
	PopupMenu menu;

	if (menuIndex == 0)
	{
        menu.addCommandItem(commandManager, openCreateNewDb);
        menu.addSeparator();

		menu.addCommandItem (commandManager, openDb);
		PopupMenu recentFiles;
		StoredSettings::getInstance()->recentFiles.createPopupMenuItems (recentFiles, 100, true, true);
		menu.addSubMenu ("Recent", recentFiles);
        
        menu.addSeparator();
        menu.addCommandItem(commandManager, useLastDatabase);


#if ! JUCE_MAC
        menu.addSeparator();
        menu.addCommandItem (commandManager, StandardApplicationCommandIDs::quit);
#endif
	}
	else if (menuIndex == 1)
	{
		menu.addCommandItem(commandManager, openExecuteSql);
		menu.addCommandItem(commandManager, openUpdateLocations);
	}
	else if (menuIndex == 2)
	{
		menu.addCommandItem (commandManager, showHelp);
		menu.addSeparator();
		menu.addCommandItem (commandManager, showAbout);
	}

	return menu;
}

void MainComponent::menuItemSelected (int menuItemID, int /*topLevelMenuIndex*/)
{
	// most of our menu items are invoked automatically as commands, but we can handle the
	// other special cases here..
	if (menuItemID >= 100 && menuItemID < 200)
	{
		// open a file from the "recent files" menu
		const File file (StoredSettings::getInstance()->recentFiles.getFile (menuItemID - 100));

		openDatabase(file);
	}
}

ApplicationCommandTarget* MainComponent::getNextCommandTarget()
{
	// this will return the next parent component that is an ApplicationCommandTarget (in this
	// case, there probably isn't one, but it's best to use this method in your own apps).
	return findFirstTargetParentComponent();
}

void MainComponent::getAllCommands (Array <CommandID>& commands)
{
	// this returns the set of all commands that this target can perform..
	const CommandID ids[] = {
			openDb,
            useLastDatabase,
			openCreateNewDb,
			openExecuteSql,
			openUpdateLocations,
			showAbout,
			showHelp
	};

	commands.addArray (ids, numElementsInArray (ids));
}

// This method is used when something needs to find out the details about one of the commands
// that this object can perform..
void MainComponent::getCommandInfo (CommandID commandID, ApplicationCommandInfo& result)
{
	const String generalCategory ("General");
	const String toolsCategory ("Tools");

	switch (commandID)
	{
	case openDb:
		result.setInfo("Open", "Open a database", generalCategory, 0);
		result.addDefaultKeypress('o', ModifierKeys::commandModifier);
		break;

    case useLastDatabase:
        result.setInfo("Start with last", "Use last open database on startup", generalCategory, 0);
        result.setTicked(m_useLastDB);
        break;
            
	case openCreateNewDb:
		result.setInfo("New", "Create an new database", generalCategory, 0);
        result.addDefaultKeypress('n', ModifierKeys::commandModifier);
		break;

	case openExecuteSql:
		result.setInfo("Execute SQL", "Execute SQL commands from a file", toolsCategory, 0);
		if(m_dbPath.isEmpty())
		{
			result.setActive(false);
		}
		break;

	case openUpdateLocations:
		result.setInfo("Update locations", "Update locations table", toolsCategory, 0);
		if(m_dbPath.isEmpty())
		{
			result.setActive(false);
		}
		break;

	case showAbout:
		result.setInfo ("About", "Shows about dialog", generalCategory, 0);
		result.addDefaultKeypress ('i', ModifierKeys::commandModifier);
		break;

	case showHelp:
		result.setInfo ("Help", "Shows the help winodow", generalCategory, 0);
		result.addDefaultKeypress ('e', ModifierKeys::commandModifier);
		break;


	default:
		break;
	};
}

// this is the ApplicationCommandTarget method that is used to actually perform one of our commands..
bool MainComponent::perform (const InvocationInfo& info)
{
	switch (info.commandID)
	{
	case openDb:
		openDbFileChooser();
		break;
    case useLastDatabase:
        toggleUseLastDB();
        break;
	case openCreateNewDb:
		createNewDb();
		break;
	case openExecuteSql:
		executeSqlScript();
		break;
	case openUpdateLocations:
		updateLocations();
		break;
	case showAbout:
		showAboutWindow();
		break;

	case showHelp:
		showHelpWindow();
		break;


	default:
		return false;
	};

	return true;
}

//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public ButtonListener, public MenuBarModel, public ApplicationCommandTarget"
                 constructorParams="MainWindow* mainWindow" variableInitialisers="m_mainWindow(mainWindow),&#10;m_lastImportedFile(String::empty),&#10;m_dbPath(String::empty),&#10;m_selectedUser(0),&#10;m_lastImportFolder(String::empty),&#10;m_selectedFileToImport(String::empty),&#10;m_selectFolder(false),&#10;m_lastExportFolder(String::empty)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="630" initialHeight="300">
  <BACKGROUND backgroundColour="ff959d9d">
    <ROUNDRECT pos="344 46 271 195" cornerSize="10" fill="solid: ffa9c0b6" hasStroke="0"/>
    <ROUNDRECT pos="18 46 302 195" cornerSize="10" fill="solid: ffb8c4c7" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="btFileImport" id="aaf7a5d5ad023c70" memberName="m_btFileImport"
              virtualName="" explicitFocusOrder="0" pos="32 208 272 23" bgColOff="ffab5757"
              bgColOn="ff003c00" buttonText="Import" connectedEdges="0" needsCallback="0"
              radioGroupId="0"/>
  <LABEL name="labelName" id="d12a7f71f2f9072c" memberName="m_labelName"
         virtualName="" explicitFocusOrder="0" pos="256 80 56 29" edTextCol="ff000000"
         edBkgCol="0" hiliteCol="ff008000" labelText="Name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="userSelectComboBox" id="8a20420f87159086" memberName="m_userSelectComboBox"
            virtualName="" explicitFocusOrder="0" pos="40 83 192 23" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="btHashCheck" id="f57535ef2b3948a3" memberName="m_btHashCheck"
                virtualName="" explicitFocusOrder="0" pos="176 120 104 23" buttonText="Check md5"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="1"/>
  <TEXTBUTTON name="SelectFile" id="a2ca34bc3838524" memberName="m_btSelectFile"
              virtualName="" explicitFocusOrder="0" pos="32 168 272 23" buttonText="Select file"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TOGGLEBUTTON name="btSelectFolder" id="b7267804ee41b214" memberName="m_btSelectFolder"
                virtualName="" explicitFocusOrder="0" pos="32 120 130 23" buttonText="Recursive import"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="sqlQuery" id="bf020fa85a006130" memberName="m_sqlQuery"
              virtualName="" explicitFocusOrder="0" pos="360 107 240 87" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="labelImport" id="4e41f1eb2f8efcb2" memberName="m_labelImport"
         virtualName="" explicitFocusOrder="0" pos="16 51 320 23" edTextCol="ff000000"
         edBkgCol="0" labelText="IMPORT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <LABEL name="labelExport" id="6445d57ea63016db" memberName="m_labelExport"
         virtualName="" explicitFocusOrder="0" pos="376 56 216 23" edTextCol="ff000000"
         edBkgCol="0" labelText="EXPORT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="btExport" id="31f23fb02423c975" memberName="m_btExport"
              virtualName="" explicitFocusOrder="0" pos="360 208 240 23" bgColOff="ff00bf00"
              bgColOn="ff008000" buttonText="Export GPX file" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <LABEL name="labelSqlQuery" id="8c65361201f22786" memberName="m_labelSqlQuery"
         virtualName="" explicitFocusOrder="0" pos="352 83 256 23" edTextCol="ff000000"
         edBkgCol="0" labelText="Enter SQL query (beginning with WHERE statement):"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="currentDbLabel" id="86585fd27c353241" memberName="m_currentDbLabel"
         virtualName="" explicitFocusOrder="0" pos="56 8 552 24" edTextCol="ff000000"
         edBkgCol="0" labelText="no database" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <LABEL name="statusLabel" id="9a3c32a95fee571e" memberName="m_statusLabel"
         virtualName="" explicitFocusOrder="0" pos="24 248 584 24" edTextCol="ff000000"
         edBkgCol="0" labelText="" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
  <LABEL name="currentDbLabelTitle" id="648ae203d8899e03" memberName="m_currentDbLabelTitle"
         virtualName="" explicitFocusOrder="0" pos="23 8 40 24" edTextCol="ff000000"
         edBkgCol="0" labelText="DB:" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
