//
//  DBImporterWindow.h
//  GpxDBImporterExporter
//
//  Created by Peter Vasil on 2/1/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef GpxDBImporterExporter_DBImporterWindow_h
#define GpxDBImporterExporter_DBImporterWindow_h

#include "includes.h"
#include "MainComponent.h"

/**
 This is the top-level window that we'll pop up. Inside it, we'll create and
 show a component from the MainComponent.cpp file (you can open this file using
 the Jucer to edit it).
 */
class DBImporterWindow  : public DocumentWindow
{
public:
	//==============================================================================
	DBImporterWindow()
	: DocumentWindow (ProjectInfo::projectName,
			Colours::lightgrey,
			DocumentWindow::allButtons,
			true)
	{
		// Create an instance of our main content component, and add it
		// to our window.

		MainComponent* contentComp = new MainComponent(this);

		commandManager.registerAllCommandsForTarget (contentComp);
		commandManager.registerAllCommandsForTarget (JUCEApplication::getInstance());

		addKeyListener (commandManager.getKeyMappings());


		setContentOwned (contentComp, true);

		setMenuBar (contentComp);

		contentComp->setApplicationCommandManagerToWatch (&commandManager);

		centreWithSize (getWidth(), getHeight());

		setVisible (true);
	}

	~DBImporterWindow()
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
		// When the user presses the close button, we'll tell the app to quit. This
		// window will be deleted by our HelloWorldApplication::shutdown() method
		//
		JUCEApplication::getInstance()->systemRequestedQuit();
	}

	ApplicationCommandManager commandManager;
};


#endif
