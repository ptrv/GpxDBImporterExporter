/*
  ==============================================================================

    Application.h
    Created: 3 Feb 2012 12:58:13am
    Author:  Peter Vasil

  ==============================================================================
 */

#ifndef __APPLICATION_H_1F4ED1F6__
#define __APPLICATION_H_1F4ED1F6__


#include "includes.h"
#include "MainComponent.h"
#include "MainWindow.h"

//==============================================================================

//==============================================================================
/** This is the application object that is started up when Juce starts. It handles
    the initialisation and shutdown of the whole application.
 */
class JUCEDBImporterApplication : public JUCEApplication
{
	/* Important! NEVER embed objects directly inside your JUCEApplication class! Use
       ONLY pointers to objects, which you should create during the initialise() method
       (NOT in the constructor!) and delete in the shutdown() method (NOT in the
       destructor!)

       This is because the application object gets created before Juce has been properly
       initialised, so any embedded objects would also get constructed too soon.
	 */
	MainWindow* dbImporterWindow;

public:
	//==============================================================================
	JUCEDBImporterApplication()
	: dbImporterWindow (0)
	{
		// NEVER do anything in here that could involve any Juce function being called
		// - leave all your startup tasks until the initialise() method.
	}

	~JUCEDBImporterApplication()
	{
		// Your shutdown() method should already have done all the things necessary to
		// clean up this app object, so you should never need to put anything in
		// the destructor.

		// Making any Juce calls in here could be very dangerous...
	}

	//==============================================================================
	void initialise (const String& commandLine)
	{
#if UNIT_TESTING
		if(commandLine.contains("--test"))
		{
			UnitTestRunner runner;
			runner.setAssertOnFailure(false);
			runner.runAllTests();

			JUCEApplication::getInstance()->quit();
		}
#endif
		// just create the main window...
		dbImporterWindow = new MainWindow();

		/*  ..and now return, which will fall into to the main event
            dispatch loop, and this will run until something calls
            JUCEAppliction::quit().

            In this case, JUCEAppliction::quit() will be called by the
            hello world window being clicked.
		 */
	}

	void shutdown()
	{
		// clear up..

		if (dbImporterWindow != 0)
			delete dbImporterWindow;
	}

	//==============================================================================
	const String getApplicationName()
	{
		return ProjectInfo::projectName;
	}

	const String getApplicationVersion()
	{
		return ProjectInfo::versionString;
	}

	bool moreThanOneInstanceAllowed()
	{
		return true;
	}

	void anotherInstanceStarted (const String& commandLine)
	{
	}
};


#endif  // __APPLICATION_H_1F4ED1F6__
