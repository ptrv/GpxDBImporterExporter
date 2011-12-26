/*
  ==============================================================================

  This is an automatically generated file created by the Jucer!

  Creation date:  26 Dec 2011 1:51:36am

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
//[/Headers]

#include "HelpComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
HelpComponent::HelpComponent ()
    : label (0)
{
    addAndMakeVisible (label = new Label (L"new label",
                                          L"Export:\n\ncolumns:\n- name\n- latitude\n- longitude\n- time"));
    label->setFont (Font (39.8000f, Font::plain));
    label->setJustificationType (Justification::topLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x0));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

HelpComponent::~HelpComponent()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    deleteAndZero (label);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void HelpComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void HelpComponent::resized()
{
    label->setBounds (16, 8, 312, 384);
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Jucer information section --

    This is where the Jucer puts all of its metadata, so don't change anything in here!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="HelpComponent" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330000013"
                 fixedSize="1" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ffffffff"/>
  <LABEL name="new label" id="e51c35a7616e3536" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="16 8 312 384" edTextCol="ff000000"
         edBkgCol="0" labelText="Export:&#10;&#10;columns:&#10;- name&#10;- latitude&#10;- longitude&#10;- time"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="39.8" bold="0" italic="0" justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
