/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Dec 2011 12:59:08pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_HELPCOMPONENT_HELPCOMPONENT_1B735544__
#define __JUCER_HEADER_HELPCOMPONENT_HELPCOMPONENT_1B735544__

//[Headers]     -- You can add your own extra header files here --
#include "includes.h"

//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class HelpComponent  : public Component
{
public:
    //==============================================================================
    HelpComponent ();
    ~HelpComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    Label* m_exportExample;
    Label* m_exportHelp;
    Label* m_exportTitle;
    Label* m_importHelp;
    Label* m_importTitle;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    HelpComponent (const HelpComponent&);
    const HelpComponent& operator= (const HelpComponent&);
};


#endif   // __JUCER_HEADER_HELPCOMPONENT_HELPCOMPONENT_1B735544__
