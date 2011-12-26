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

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "HelpComponent.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...

//[/MiscUserDefs]

//==============================================================================
HelpComponent::HelpComponent ()
    : m_exportExample (0),
      m_exportHelp (0),
      m_exportTitle (0),
      m_importHelp (0),
      m_importTitle (0)
{
    addAndMakeVisible (m_exportExample = new Label (L"exportExample",
                                                    L"examples:\n\n- WHERE strftime(\'%Y\', time) > 2010\n\n- WHERE name = \'Peter\'\n\n- WHERE city = \'Berlin\'"));
    m_exportExample->setFont (Font (15.0000f, Font::plain));
    m_exportExample->setJustificationType (Justification::topLeft);
    m_exportExample->setEditable (false, false, false);
    m_exportExample->setColour (TextEditor::textColourId, Colours::black);
    m_exportExample->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_exportHelp = new Label (L"exportHelp",
                                                 L"columns:\n- gpsdataid\n- name\n- latitude\n- longitude\n- elevation\n- segment\n- city\n- time\n- file"));
    m_exportHelp->setFont (Font (15.0000f, Font::plain));
    m_exportHelp->setJustificationType (Justification::topLeft);
    m_exportHelp->setEditable (false, false, false);
    m_exportHelp->setColour (TextEditor::textColourId, Colours::black);
    m_exportHelp->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_exportTitle = new Label (L"exportTitle",
                                                  L"Export:\n"));
    m_exportTitle->setFont (Font (32.0000f, Font::bold));
    m_exportTitle->setJustificationType (Justification::centredLeft);
    m_exportTitle->setEditable (false, false, false);
    m_exportTitle->setColour (TextEditor::textColourId, Colours::black);
    m_exportTitle->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_importHelp = new Label (L"importHelp",
                                                 L"name: user name\n\ncheck md5: checks md5 checksum of gpx file to avoid duplicates\n\nrecursive import: if checked input is a folder\n\nselect: selects file/folder for import\n\nimport: runs import\n\nupdate locations: assigns locations to db entries\n\nexecute sql script: executes a sql script on the current database\n\ncreate new db: creates an empty database"));
    m_importHelp->setFont (Font (15.0000f, Font::plain));
    m_importHelp->setJustificationType (Justification::topLeft);
    m_importHelp->setEditable (false, false, false);
    m_importHelp->setColour (TextEditor::textColourId, Colours::black);
    m_importHelp->setColour (TextEditor::backgroundColourId, Colour (0x0));

    addAndMakeVisible (m_importTitle = new Label (L"importTitle",
                                                  L"Import:\n"));
    m_importTitle->setFont (Font (32.0000f, Font::bold));
    m_importTitle->setJustificationType (Justification::centredLeft);
    m_importTitle->setEditable (false, false, false);
    m_importTitle->setColour (TextEditor::textColourId, Colours::black);
    m_importTitle->setColour (TextEditor::backgroundColourId, Colour (0x0));


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

    deleteAndZero (m_exportExample);
    deleteAndZero (m_exportHelp);
    deleteAndZero (m_exportTitle);
    deleteAndZero (m_importHelp);
    deleteAndZero (m_importTitle);


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void HelpComponent::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colours::white);

    g.setColour (Colours::black);
    g.fillRect (304, 12, 1, 372);

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void HelpComponent::resized()
{
    m_exportExample->setBounds (312, 216, 280, 136);
    m_exportHelp->setBounds (312, 48, 280, 168);
    m_exportTitle->setBounds (312, 8, 150, 32);
    m_importHelp->setBounds (16, 48, 280, 336);
    m_importTitle->setBounds (16, 8, 150, 32);
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
  <BACKGROUND backgroundColour="ffffffff">
    <RECT pos="304 12 1 372" fill="solid: ff000000" hasStroke="0"/>
  </BACKGROUND>
  <LABEL name="exportExample" id="f1ca796f3b441543" memberName="m_exportExample"
         virtualName="" explicitFocusOrder="0" pos="312 216 280 136" edTextCol="ff000000"
         edBkgCol="0" labelText="examples:&#10;&#10;- WHERE strftime('%Y', time) &gt; 2010&#10;&#10;- WHERE name = 'Peter'&#10;&#10;- WHERE city = 'Berlin'"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="9"/>
  <LABEL name="exportHelp" id="e51c35a7616e3536" memberName="m_exportHelp"
         virtualName="" explicitFocusOrder="0" pos="312 48 280 168" edTextCol="ff000000"
         edBkgCol="0" labelText="columns:&#10;- gpsdataid&#10;- name&#10;- latitude&#10;- longitude&#10;- elevation&#10;- segment&#10;- city&#10;- time&#10;- file"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="9"/>
  <LABEL name="exportTitle" id="1ccf918250a2dfb" memberName="m_exportTitle"
         virtualName="" explicitFocusOrder="0" pos="312 8 150 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Export:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="32" bold="1" italic="0" justification="33"/>
  <LABEL name="importHelp" id="811f27fdcae42287" memberName="m_importHelp"
         virtualName="" explicitFocusOrder="0" pos="16 48 280 336" edTextCol="ff000000"
         edBkgCol="0" labelText="name: user name&#10;&#10;check md5: checks md5 checksum of gpx file to avoid duplicates&#10;&#10;recursive import: if checked input is a folder&#10;&#10;select: selects file/folder for import&#10;&#10;import: runs import&#10;&#10;update locations: assigns locations to db entries&#10;&#10;execute sql script: executes a sql script on the current database&#10;&#10;create new db: creates an empty database"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="15" bold="0" italic="0" justification="9"/>
  <LABEL name="importTitle" id="2c1527895ea81794" memberName="m_importTitle"
         virtualName="" explicitFocusOrder="0" pos="16 8 150 32" edTextCol="ff000000"
         edBkgCol="0" labelText="Import:&#10;" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="32" bold="1" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif
