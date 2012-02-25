/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  25 Feb 2012 3:11:41pm

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
#include "TextConsole.h"
//[/Headers]

#include "DBStatsComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
DBStatsComponent::DBStatsComponent ()
    : console (0)
{
    addAndMakeVisible (console = new TextConsole());
    console->setName (L"console");


    //[UserPreSize]
    //[/UserPreSize]

    setSize (250, 200);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

DBStatsComponent::~DBStatsComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (console);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void DBStatsComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void DBStatsComponent::resized()
{
    console->setBounds (8, 8, 232, 184);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void DBStatsComponent::setStats(const StringArray& stats)
{
	console->clear();
	for (int i = 0; i < stats.size(); ++i) {
		console->addLine(stats[i]);
	}
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="DBStatsComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="250" initialHeight="200">
  <BACKGROUND backgroundColour="ffffffff"/>
  <GENERICCOMPONENT name="console" id="1217da7e6da2affd" memberName="console" virtualName=""
                    explicitFocusOrder="0" pos="8 8 232 184" class="TextConsole"
                    params=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
