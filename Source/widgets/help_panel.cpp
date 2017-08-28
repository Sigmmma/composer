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

#include "help_panel.h"
#include "playlist_help_panel.h"
#include "commands_help_panel.h"
#include "about_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
HelpPanel::HelpPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (tabbedWindows = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedWindows->setTabBarDepth (35);
    tabbedWindows->addTab (TRANS("Playlist help"), Colour (0xffb0b040), new PlaylistHelpPanel(), true);
    tabbedWindows->addTab (TRANS("Commands help"), Colour (0xffb0b040), new CommandsHelpPanel(), true);
    tabbedWindows->addTab (TRANS("About"), Colour (0xffb0b040), new AboutPanel(), true);
    tabbedWindows->setCurrentTabIndex (0);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (600, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

HelpPanel::~HelpPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    tabbedWindows = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void HelpPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void HelpPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tabbedWindows->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
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

<JUCER_COMPONENT documentType="Component" className="HelpPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="600" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <TABBEDCOMPONENT name="tabbed windows" id="e4e1a529f9184acd" memberName="tabbedWindows"
                   virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 100%" orientation="top"
                   tabBarDepth="35" initialTab="0">
    <TAB name="Playlist help" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="playlist_help_panel.cpp"/>
    <TAB name="Commands help" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="commands_help_panel.cpp"/>
    <TAB name="About" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="about_panel.cpp"/>
  </TABBEDCOMPONENT>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
