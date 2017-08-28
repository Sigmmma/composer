/*
  ==============================================================================

  This is an automatically generated GUI class created by the Projucer!

  Be careful when adding custom code to these files, as only the code within
  the "//[xyz]" and "//[/xyz]" sections will be retained when the file is loaded
  and re-saved.

  Created with Projucer version: 5.1.1

  ------------------------------------------------------------------------------

  The Projucer is part of the JUCE library - "Jules' Utility Class Extensions"
  Copyright (c) 2015 - ROLI Ltd.

  ==============================================================================
*/

//[Headers] You can add your own extra header files here...
//[/Headers]

#include "about_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
AboutPanel::AboutPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (groupComponent = new GroupComponent ("new group",
                                                            TRANS("Author")));

    addAndMakeVisible (groupComponent2 = new GroupComponent ("new group",
                                                             TRANS("Licensing")));

    addAndMakeVisible (aboutLabel = new Label ("about label",
                                               TRANS("Designed and programmed by Devin Bobadilla.")));
    aboutLabel->setFont (Font ("Calibri", 20.00f, Font::plain).withTypefaceStyle ("Regular"));
    aboutLabel->setJustificationType (Justification::topLeft);
    aboutLabel->setEditable (false, false, false);
    aboutLabel->setColour (Label::textColourId, Colours::white);
    aboutLabel->setColour (TextEditor::textColourId, Colours::black);
    aboutLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (aboutLabel2 = new Label ("about label",
                                                TRANS("Composer is licensed under the GPL v3 license.\n"
                                                "A copy of Composer\'s source code may be obtained from the composer repository located on my Bitbucket account here:\n"
                                                "\n"
                                                " bitbucket.org/Moses_of_Egypt/")));
    aboutLabel2->setFont (Font ("Calibri", 20.00f, Font::plain).withTypefaceStyle ("Regular"));
    aboutLabel2->setJustificationType (Justification::topLeft);
    aboutLabel2->setEditable (false, false, false);
    aboutLabel2->setColour (Label::textColourId, Colours::white);
    aboutLabel2->setColour (TextEditor::textColourId, Colours::black);
    aboutLabel2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

AboutPanel::~AboutPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    groupComponent = nullptr;
    groupComponent2 = nullptr;
    aboutLabel = nullptr;
    aboutLabel2 = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void AboutPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void AboutPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    groupComponent->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    groupComponent2->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2510f), proportionOfWidth (1.0000f), proportionOfHeight (0.7490f));
    aboutLabel->setBounds (proportionOfWidth (0.0223f), proportionOfHeight (0.0510f), proportionOfWidth (0.9578f), proportionOfHeight (0.1725f));
    aboutLabel2->setBounds (proportionOfWidth (0.0223f), proportionOfHeight (0.3078f), proportionOfWidth (0.9578f), proportionOfHeight (0.5353f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="AboutPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <GROUPCOMPONENT name="new group" id="48a22180547a5190" memberName="groupComponent"
                  virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 100%" title="Author"/>
  <GROUPCOMPONENT name="new group" id="62e40e2263847e80" memberName="groupComponent2"
                  virtualName="" explicitFocusOrder="0" pos="0% 25.098% 100% 74.902%"
                  title="Licensing"/>
  <LABEL name="about label" id="499dc40a69f91f08" memberName="aboutLabel"
         virtualName="" explicitFocusOrder="0" pos="2.233% 5.098% 95.782% 17.255%"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Designed and programmed by Devin Bobadilla."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Calibri" fontsize="20" kerning="0" bold="0" italic="0"
         justification="9"/>
  <LABEL name="about label" id="b2a6a9d8651dd9f1" memberName="aboutLabel2"
         virtualName="" explicitFocusOrder="0" pos="2.233% 30.784% 95.782% 53.529%"
         textCol="ffffffff" edTextCol="ff000000" edBkgCol="0" labelText="Composer is licensed under the GPL v3 license.&#10;A copy of Composer's source code may be obtained from the composer repository located on my Bitbucket account here:&#10;&#10; bitbucket.org/Moses_of_Egypt/"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Calibri" fontsize="20" kerning="0" bold="0" italic="0"
         justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
