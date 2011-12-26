/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Dec 2011 1:00:14pm

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
//[/Headers]

#include "MainComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
MainComponent::MainComponent ()
    : m_statusMessage(String::empty),
      m_lastImportedFile(String::empty),
      m_dbPath(String::empty),
      m_selectedUser(0),
      m_lastImportFolder(String::empty),
      m_selectedFileToImport(String::empty),
      m_selectFolder(false),
      m_lastExportFolder(String::empty),
      createDbButton (0),
      m_dbChooser (0),
      m_btFileImport (0),
      m_labelName (0),
      m_userSelectComboBox (0),
      m_btHashCheck (0),
      m_btAbout (0),
      m_btExecuteSqlScript (0),
      m_btSelectFile (0),
      m_btUpdateLocations (0),
      m_btSelectFolder (0),
      m_sqlQuery (0),
      m_labelImport (0),
      m_labelExport (0),
      m_btExport (0),
      m_labelSqlQuery (0),
      m_btHelp (0)
{
    addAndMakeVisible (createDbButton = new TextButton (L"createDbButton"));
    createDbButton->setButtonText (L"create new DB");
    createDbButton->setColour (TextButton::buttonOnColourId, Colour (0xff003c00));

    addAndMakeVisible (m_dbChooser = new FilenameComponent ("database file", File::nonexistent, true, false, false, "*.sqlite;*.db",String::empty, "(choose database file)"));
    m_dbChooser->setName (L"dbChooser");

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

    addAndMakeVisible (m_btAbout = new TextButton (L"btAbout"));
    m_btAbout->setButtonText (L"About");

    addAndMakeVisible (m_btExecuteSqlScript = new TextButton (L"ExecuteSqlScript"));
    m_btExecuteSqlScript->setButtonText (L"Execute Sql Script");

    addAndMakeVisible (m_btSelectFile = new TextButton (L"SelectFile"));
    m_btSelectFile->setButtonText (L"Select file");

    addAndMakeVisible (m_btUpdateLocations = new TextButton (L"UpdateLocations"));
    m_btUpdateLocations->setButtonText (L"Update locations");

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

    addAndMakeVisible (m_btHelp = new TextButton (L"btHelp"));
    m_btHelp->setButtonText (L"Help");


    //[UserPreSize]
    createDbButton->addListener (this);
    m_btFileImport->addListener (this);
    m_btHashCheck->addListener (this);
    m_btAbout->addListener (this);
    m_btExecuteSqlScript->addListener (this);
    m_btSelectFile->addListener (this);
    m_btUpdateLocations->addListener (this);
    m_btSelectFolder->addListener (this);
    m_btExport->addListener (this);
    m_btHelp->addListener(this);

    m_dbChooser->addListener(this);
    m_userSelectComboBox->setEnabled(false);
    m_btSelectFile->setEnabled(false);
    m_btFileImport->setEnabled(false);
    m_btExecuteSqlScript->setEnabled(false);
    m_btUpdateLocations->setEnabled(false);
    DBG_SCOPE();
    //[/UserPreSize]

    setSize (630, 300);


    //[Constructor] You can add your own custom stuff here..
    m_statusMessage = "Ready to import!";

	m_dbChooser->setRecentlyUsedFilenames(StoredSettings::getInstance()->recentFiles.getAllFilenames());
	m_lastImportFolder = StoredSettings::getInstance()->getLastImportFolder();
	m_btSelectFolder->setToggleState(StoredSettings::getInstance()->getSelectFolders(), false);
	m_lastExportFolder = StoredSettings::getInstance()->getLastExportFolder();

    m_helpComponent = new HelpComponent();
    //[/Constructor]
}

MainComponent::~MainComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
	int recentFileNum = m_dbChooser->getRecentlyUsedFilenames().size();
	for (int i = 0; i < recentFileNum; ++i)
    {
		StoredSettings::getInstance()->recentFiles.addFile(m_dbChooser->getRecentlyUsedFilenames()[recentFileNum-1-i]);
    }
	StoredSettings::getInstance()->setLastImportFolder(m_lastImportFolder);
	StoredSettings::getInstance()->setSelectFolders(m_btSelectFolder->getToggleState());
	StoredSettings::getInstance()->setLastExportFolder(m_lastExportFolder);

	StoredSettings::deleteInstance();

    //[/Destructor_pre]

    deleteAndZero (createDbButton);
    deleteAndZero (m_dbChooser);
    deleteAndZero (m_btFileImport);
    deleteAndZero (m_labelName);
    deleteAndZero (m_userSelectComboBox);
    deleteAndZero (m_btHashCheck);
    deleteAndZero (m_btAbout);
    deleteAndZero (m_btExecuteSqlScript);
    deleteAndZero (m_btSelectFile);
    deleteAndZero (m_btUpdateLocations);
    deleteAndZero (m_btSelectFolder);
    deleteAndZero (m_sqlQuery);
    deleteAndZero (m_labelImport);
    deleteAndZero (m_labelExport);
    deleteAndZero (m_btExport);
    deleteAndZero (m_labelSqlQuery);
    deleteAndZero (m_btHelp);


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
    g.fillRoundedRectangle (365.0f, 77.0f, 256.0f, 195.0f, 10.0000f);

    g.setColour (Colour (0xffb8c4c7));
    g.fillRoundedRectangle (8.0f, 77.0f, 333.0f, 195.0f, 10.0000f);

    //[UserPaint] Add your own custom painting code here..
    g.setColour(Colours::black);
    g.setFont(12);
    g.drawSingleLineText(m_statusMessage, 15, getHeight()-10);
    //[/UserPaint]
}

void MainComponent::resized()
{
    createDbButton->setBounds (182, 233, 144, 24);
    m_dbChooser->setBounds (8, 40, 613, 24);
    m_btFileImport->setBounds (22, 233, 128, 24);
    m_labelName->setBounds (166, 111, 72, 24);
    m_userSelectComboBox->setBounds (22, 112, 136, 24);
    m_btHashCheck->setBounds (232, 112, 96, 24);
    m_btAbout->setBounds (8, 16, 40, 16);
    m_btExecuteSqlScript->setBounds (182, 193, 144, 24);
    m_btSelectFile->setBounds (22, 197, 128, 24);
    m_btUpdateLocations->setBounds (182, 154, 144, 24);
    m_btSelectFolder->setBounds (22, 154, 130, 24);
    m_sqlQuery->setBounds (376, 136, 236, 88);
    m_labelImport->setBounds (16, 80, 320, 24);
    m_labelExport->setBounds (376, 80, 216, 24);
    m_btExport->setBounds (376, 233, 236, 24);
    m_labelSqlQuery->setBounds (372, 112, 244, 24);
    m_btHelp->setBounds (581, 16, 40, 16);
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
//const String& MainComponent
void MainComponent::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == createDbButton)
    {
        //[UserButtonCode_createDbButton] -- add your button handler code here..
        createNewDb();
        //[/UserButtonCode_createDbButton]
    }
    else if (buttonThatWasClicked == m_btFileImport)
    {
        //[UserButtonCode_m_btFileImport] -- add your button handler code here..
        importFile();
        //[/UserButtonCode_m_btFileImport]
    }
    else if (buttonThatWasClicked == m_btHashCheck)
    {
        //[UserButtonCode_m_btHashCheck] -- add your button handler code here..
        //[/UserButtonCode_m_btHashCheck]
    }
    else if (buttonThatWasClicked == m_btAbout)
    {
        //[UserButtonCode_m_btAbout] -- add your button handler code here..
        showAboutWindow();
        //[/UserButtonCode_m_btAbout]
    }
    else if (buttonThatWasClicked == m_btExecuteSqlScript)
    {
        //[UserButtonCode_m_btExecuteSqlScript] -- add your button handler code here..
        executeSqlScript();
        //[/UserButtonCode_m_btExecuteSqlScript]
    }
    else if (buttonThatWasClicked == m_btSelectFile)
    {
        //[UserButtonCode_m_btSelectFile] -- add your button handler code here..
        selectFileToImport();
        //[/UserButtonCode_m_btSelectFile]
    }
    else if (buttonThatWasClicked == m_btUpdateLocations)
    {
        //[UserButtonCode_m_btUpdateLocations] -- add your button handler code here..
        updateLocations();
        //[/UserButtonCode_m_btUpdateLocations]
    }
    else if (buttonThatWasClicked == m_btSelectFolder)
    {
        //[UserButtonCode_m_btSelectFolder] -- add your button handler code here..
        //[/UserButtonCode_m_btSelectFolder]
    }
    else if (buttonThatWasClicked == m_btExport)
    {
        //[UserButtonCode_m_btExport] -- add your button handler code here..
		exportGpxFile();
        //[/UserButtonCode_m_btExport]
    }
    else if (buttonThatWasClicked == m_btHelp)
    {
        //[UserButtonCode_m_btHelp] -- add your button handler code here..
		showHelpWindow();
        //[/UserButtonCode_m_btHelp]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void MainComponent::filenameComponentChanged (FilenameComponent* fileComponentThatHasChanged)
{
    if ( fileComponentThatHasChanged == m_dbChooser )
    {
        m_dbPath = fileComponentThatHasChanged->getCurrentFile().getFullPathName();
        DBG_VAL(m_dbPath);
        if (fileComponentThatHasChanged->getCurrentFile().existsAsFile())
        {
            m_userSelectComboBox->setEnabled(true);
            m_btSelectFile->setEnabled(true);
            m_btExecuteSqlScript->setEnabled(true);
            m_btUpdateLocations->setEnabled(true);

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
            m_userSelectComboBox->setEnabled(false);
            m_btSelectFile->setEnabled(false);
            m_btExecuteSqlScript->setEnabled(false);
            m_btUpdateLocations->setEnabled(false);
        }
    }
}
void MainComponent::selectFileToImport()
{
    m_selectedFilesToImport.clear();



    if(m_btSelectFolder->getToggleState())
    {
        FileChooser importDialog("Please select folder with gpx files...", File(m_lastImportFolder), "*.gpx", true);
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
            m_statusMessage = "Selected file: " + m_lastImportedFile;
            m_btFileImport->setEnabled(true);
            repaint();
        }
    }
    else
    {
        FileChooser importDialog("Please select gpx files...", File(m_lastImportFolder), "*.gpx", true);
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
                    m_statusMessage = "Selected file: " + m_lastImportedFile;
                    m_btFileImport->setEnabled(true);
                    repaint();
                }
                else
                {
                    m_btFileImport->setEnabled(false);
                    m_statusMessage = "The selected file was not valid!";
                    repaint();
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
                            "*.sqlite;*.db");

    if (saveDialog.browseForFileToSave(true))
    {
        if (saveDialog.getResult().exists())
        {
            saveDialog.getResult().deleteFile();
        }
        File dbFile(saveDialog.getResult());

        DBConnector* dbCon = new DBConnector(dbFile.getFullPathName());
        dbCon->setupDbConnection();
        dbCon->createNewDb();
        dbCon->insertPredefinedData();
        dbCon->closeDbConnection();
        delete dbCon;
        m_dbChooser->setCurrentFile(File(dbFile.getFullPathName()), true, true);
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
        m_statusMessage = fileImporter.getStatus();
        repaint();
    }
    else
    {
        m_statusMessage = "Import canceled!";
        repaint();
    }
}

void MainComponent::updateLocations()
{
    LocationUpdater locationUpdater(m_dbPath);

    if (locationUpdater.runThread())
    {
        m_statusMessage = locationUpdater.getStatus();
        repaint();
    }
    else
    {
    }
}

void MainComponent::executeSqlScript()
{
    FileChooser sqlScriptChooser("Please select the sql file to execute...",
                                 File::getSpecialLocation (File::userHomeDirectory),
                                 "*.sql");
    if (sqlScriptChooser.browseForFileToOpen())
    {
        File sqlFile (sqlScriptChooser.getResult());
        if (sqlFile.existsAsFile() && sqlFile.getFileExtension() == ".sql")
        {
            DBConnector dbcon(m_dbPath);
            dbcon.setupDbConnection();
            dbcon.executeSqlScript(sqlFile);
            dbcon.closeDbConnection();
            m_statusMessage = "Executed SQL script!";
        }
        else
        {
            m_statusMessage = "File not valid!";
        }
    }
}
void MainComponent::setStatusMessage(const String& statusMessage)
{
    m_statusMessage = statusMessage;
    repaint();
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
								 "*.gpx");
	if (gpxExportChooser.browseForFileToSave(true))
	{
		File gpxExportFile (gpxExportChooser.getResult());

		if (gpxExportFile.existsAsFile())
		{
			gpxExportFile.deleteFile();
		}

		m_lastExportFolder = gpxExportFile.getParentDirectory().getFullPathName();

		DBG_VAL(m_sqlQuery->getText());
		FileExporter fileExporter(m_dbPath, gpxExportFile.getFullPathName(), m_sqlQuery->getText());

		if (fileExporter.runThread())
		{
			m_statusMessage = fileExporter.getStatus();
			repaint();
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
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="MainComponent" componentName=""
                 parentClasses="public Component, public FilenameComponentListener, public ButtonListener"
                 constructorParams="" variableInitialisers="m_statusMessage(String::empty),&#10;m_lastImportedFile(String::empty),&#10;m_dbPath(String::empty),&#10;m_selectedUser(0),&#10;m_lastImportFolder(String::empty),&#10;m_selectedFileToImport(String::empty),&#10;m_selectFolder(false),&#10;m_lastExportFolder(String::empty)"
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="630" initialHeight="300">
  <BACKGROUND backgroundColour="ff959d9d">
    <ROUNDRECT pos="365 77 256 195" cornerSize="10" fill="solid: ffa9c0b6" hasStroke="0"/>
    <ROUNDRECT pos="8 77 333 195" cornerSize="10" fill="solid: ffb8c4c7" hasStroke="0"/>
  </BACKGROUND>
  <TEXTBUTTON name="createDbButton" id="dc303cca5155d8cc" memberName="createDbButton"
              virtualName="" explicitFocusOrder="0" pos="182 233 144 24" bgColOn="ff003c00"
              buttonText="create new DB" connectedEdges="0" needsCallback="0"
              radioGroupId="0"/>
  <GENERICCOMPONENT name="dbChooser" id="5d76df185c1046d4" memberName="m_dbChooser"
                    virtualName="" explicitFocusOrder="0" pos="8 40 613 24" class="FilenameComponent"
                    params="&quot;database file&quot;, File::nonexistent, true, false, false, &quot;*.sqlite;*.db&quot;,String::empty, &quot;(choose database file)&quot;"/>
  <TEXTBUTTON name="btFileImport" id="aaf7a5d5ad023c70" memberName="m_btFileImport"
              virtualName="" explicitFocusOrder="0" pos="22 233 128 24" bgColOff="ffab5757"
              bgColOn="ff003c00" buttonText="Import" connectedEdges="0" needsCallback="0"
              radioGroupId="0"/>
  <LABEL name="labelName" id="d12a7f71f2f9072c" memberName="m_labelName"
         virtualName="" explicitFocusOrder="0" pos="166 111 72 24" edTextCol="ff000000"
         edBkgCol="0" hiliteCol="ff008000" labelText="Name" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" bold="0" italic="0" justification="33"/>
  <COMBOBOX name="userSelectComboBox" id="8a20420f87159086" memberName="m_userSelectComboBox"
            virtualName="" explicitFocusOrder="0" pos="22 112 136 24" editable="1"
            layout="33" items="" textWhenNonSelected="" textWhenNoItems="(no choices)"/>
  <TOGGLEBUTTON name="btHashCheck" id="f57535ef2b3948a3" memberName="m_btHashCheck"
                virtualName="" explicitFocusOrder="0" pos="232 112 96 24" buttonText="Check md5"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="1"/>
  <TEXTBUTTON name="btAbout" id="35e7cbe575f6e964" memberName="m_btAbout" virtualName=""
              explicitFocusOrder="0" pos="8 16 40 16" buttonText="About" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="ExecuteSqlScript" id="838dae3d1c21f2c4" memberName="m_btExecuteSqlScript"
              virtualName="" explicitFocusOrder="0" pos="182 193 144 24" buttonText="Execute Sql Script"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="SelectFile" id="a2ca34bc3838524" memberName="m_btSelectFile"
              virtualName="" explicitFocusOrder="0" pos="22 197 128 24" buttonText="Select file"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TEXTBUTTON name="UpdateLocations" id="6d1185f0ad06adc6" memberName="m_btUpdateLocations"
              virtualName="" explicitFocusOrder="0" pos="182 154 144 24" buttonText="Update locations"
              connectedEdges="0" needsCallback="0" radioGroupId="0"/>
  <TOGGLEBUTTON name="btSelectFolder" id="b7267804ee41b214" memberName="m_btSelectFolder"
                virtualName="" explicitFocusOrder="0" pos="22 154 130 24" buttonText="Recursive import"
                connectedEdges="0" needsCallback="0" radioGroupId="0" state="0"/>
  <TEXTEDITOR name="sqlQuery" id="bf020fa85a006130" memberName="m_sqlQuery"
              virtualName="" explicitFocusOrder="0" pos="376 136 236 88" initialText=""
              multiline="1" retKeyStartsLine="1" readonly="0" scrollbars="1"
              caret="1" popupmenu="1"/>
  <LABEL name="labelImport" id="4e41f1eb2f8efcb2" memberName="m_labelImport"
         virtualName="" explicitFocusOrder="0" pos="16 80 320 24" edTextCol="ff000000"
         edBkgCol="0" labelText="IMPORT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <LABEL name="labelExport" id="6445d57ea63016db" memberName="m_labelExport"
         virtualName="" explicitFocusOrder="0" pos="376 80 216 24" edTextCol="ff000000"
         edBkgCol="0" labelText="EXPORT" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="24"
         bold="0" italic="0" justification="36"/>
  <TEXTBUTTON name="btExport" id="31f23fb02423c975" memberName="m_btExport"
              virtualName="" explicitFocusOrder="0" pos="376 233 236 24" bgColOff="ff00bf00"
              bgColOn="ff008000" buttonText="Export GPX file" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
  <LABEL name="labelSqlQuery" id="8c65361201f22786" memberName="m_labelSqlQuery"
         virtualName="" explicitFocusOrder="0" pos="372 112 244 24" edTextCol="ff000000"
         edBkgCol="0" labelText="Enter SQL query (beginning with WHERE statement):"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="btHelp" id="61093d1c9c1ac51d" memberName="m_btHelp" virtualName=""
              explicitFocusOrder="0" pos="581 16 40 16" buttonText="Help" connectedEdges="0"
              needsCallback="0" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
