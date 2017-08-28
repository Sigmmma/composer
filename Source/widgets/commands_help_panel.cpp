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

#include "commands_help_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
// projucer is being stupid, so i have to import this manually
#include "commands_help.h"
//[/MiscUserDefs]

//==============================================================================
CommandsHelpPanel::CommandsHelpPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (viewport = new Viewport ("new viewport"));
    viewport->setScrollBarThickness (10);
    viewport->setViewedComponent (new CommandsHelp());


    //[UserPreSize]
    //[/UserPreSize]

    setSize (350, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CommandsHelpPanel::~CommandsHelpPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    viewport = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CommandsHelpPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CommandsHelpPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    viewport->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="CommandsHelpPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="350" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <VIEWPORT name="new viewport" id="8c5aa08971381218" memberName="viewport"
            virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 100%" vscroll="1"
            hscroll="1" scrollbarThickness="10" contentType="1" jucerFile="commands_help.cpp"
            contentClass="" constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
