/*
  ==============================================================================

    HelpWindow.h
    Created: 25 Dec 2011 9:45:52pm
    Author:  Peter Vasil

  ==============================================================================
*/

#ifndef __HELPWINDOW_H_922B43C6__
#define __HELPWINDOW_H_922B43C6__

#include "HelpComponent.h"

class HelpWindow : public DocumentWindow
{
public:
    //==============================================================================
    HelpWindow()
    : DocumentWindow ("Help",
                      Colours::lightgrey,
                      DocumentWindow::closeButton,
                      true)
    {
        // Create an instance of our main content component, and add it
        // to our window.
        
        HelpComponent* const contentComponent = new HelpComponent();
        
        setContentOwned (contentComponent, true);
        
        centreWithSize (getWidth(), getHeight());
        
        setVisible (false);
    }
    
    ~HelpWindow()
    {
        // (the content component will be deleted automatically, so no need to do it here)
    }
    
    //==============================================================================
    void closeButtonPressed()
    {
        // When the user presses the close button, we'll tell the app to quit. This
        // window will be deleted by our HelloWorldApplication::shutdown() method
        //
        //        JUCEApplication::quit();
    }
};




#endif  // __HELPWINDOW_H_922B43C6__
