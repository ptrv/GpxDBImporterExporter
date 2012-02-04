//
//  DBImporterWindow.h
//  GpxDBImporterExporter
//
//  Created by Peter Vasil on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GpxDBImporterExporter_MainWindow_h
#define GpxDBImporterExporter_MainWindow_h

#include "includes.h"
#include "MainComponent.h"

/**
 This is the top-level window that we'll pop up. Inside it, we'll create and
 show a component from the MainComponent.cpp file (you can open this file using
 the Jucer to edit it).
 */
class MainWindow  : public DocumentWindow
{
public:
	//==============================================================================
	MainWindow()
	: DocumentWindow (ProjectInfo::projectName,
			Colours::lightgrey,
			DocumentWindow::minimiseButton | DocumentWindow::closeButton,
			true)
	{
		// Create an instance of our main content component, and add it
		// to our window.

		setResizable(false, false);

		MainComponent* contentComp = new MainComponent(this);

		commandManager.registerAllCommandsForTarget (contentComp);
		commandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());

		addKeyListener (commandManager.getKeyMappings());


		setContentOwned (contentComp, true);

#ifdef JUCE_MAC
        setMenuBar(nullptr);
        MenuBarModel::setMacMainMenu(contentComp);
#else
        setMenuBar (contentComp);
#endif

		contentComp->setApplicationCommandManagerToWatch (&commandManager);

		centreWithSize (getWidth(), getHeight());

		setVisible (true);
	}

	~MainWindow()
	{
		setMenuBar (nullptr);

#if JUCE_MAC  // ..and also the main bar if we're using that on a Mac...
		MenuBarModel::setMacMainMenu (nullptr);
#endif
		clearContentComponent();
	}

	//==============================================================================
	void closeButtonPressed()
	{
		JUCEApplication::getInstance()->systemRequestedQuit();
	}

	ApplicationCommandManager commandManager;
};


#endif
