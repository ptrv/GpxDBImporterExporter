/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Feb 2012 3:11:40pm

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Jucer version: 1.12

  ------------------------------------------------------------------------------

  The Jucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright 2004-6 by Raw Material Software ltd.

  ==============================================================================
*/

#ifndef __JUCER_HEADER_DBSTATSCOMPONENT_DBSTATSCOMPONENT_AA5E24B7__
#define __JUCER_HEADER_DBSTATSCOMPONENT_DBSTATSCOMPONENT_AA5E24B7__

//[Headers]     -- You can add your own extra header files here --
#include "includes.h"
class TextConsole;
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Jucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class DBStatsComponent  : public Component
{
public:
    //==============================================================================
    DBStatsComponent ();
    ~DBStatsComponent();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void setStats(const StringArray& stats);
    //[/UserMethods]

    void paint (Graphics& g);
    void resized();



    //==============================================================================
    juce_UseDebuggingNewOperator

private:
    //[UserVariables]   -- You can add your own custom variables in this section.
    //[/UserVariables]

    //==============================================================================
    TextConsole* console;


    //==============================================================================
    // (prevent copy constructor and operator= being generated..)
    DBStatsComponent (const DBStatsComponent&);
    const DBStatsComponent& operator= (const DBStatsComponent&);
};


#endif   // __JUCER_HEADER_DBSTATSCOMPONENT_DBSTATSCOMPONENT_AA5E24B7__
