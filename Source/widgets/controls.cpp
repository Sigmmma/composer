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

#include "controls.h"
#include "playlist_panel.h"
#include "commands_panel.h"
#include "settings_panel.h"
#include "help_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
ControlsPanel::ControlsPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (tabbedWindows = new TabbedComponent (TabbedButtonBar::TabsAtTop));
    tabbedWindows->setTabBarDepth (35);
    tabbedWindows->addTab (TRANS("Playlist"), Colour (0xffb0b040), new PlaylistPanel(), true);
    tabbedWindows->addTab (TRANS("Commands"), Colour (0xffb0b040), new CommandsPanel(), true);
    tabbedWindows->addTab (TRANS("Settings"), Colour (0xffb0b040), new SettingsPanel(), true);
    tabbedWindows->addTab (TRANS("Help"), Colour (0xffb0b040), new HelpPanel(), true);
    tabbedWindows->setCurrentTabIndex (0);

    addAndMakeVisible (playbackPanel = new PlaybackPanel());

    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 500);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

ControlsPanel::~ControlsPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Destructor_pre]

    tabbedWindows = nullptr;
    playbackPanel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void ControlsPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff355535));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void ControlsPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    tabbedWindows->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.8000f));
    playbackPanel->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.8000f), proportionOfWidth (1.0000f), proportionOfHeight (0.2000f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void ControlsPanel::set_slider_listener_override(juce::Slider::Listener *listener_override) {
    this->slider_listener_override = listener_override;

    ((PlaylistPanel *)(tabbedWindows->getTabContentComponent(0)))->set_slider_listener_override(listener_override);
    ((CommandsPanel *)(tabbedWindows->getTabContentComponent(1)))->set_slider_listener_override(listener_override);
    ((SettingsPanel *)(tabbedWindows->getTabContentComponent(2)))->set_slider_listener_override(listener_override);

    this->playbackPanel->set_slider_listener_override(this->slider_listener_override);
}
void ControlsPanel::set_button_listener_override(juce::TextButton::Listener *listener_override) {
    this->button_listener_override = listener_override;

    ((PlaylistPanel *)(tabbedWindows->getTabContentComponent(0)))->set_button_listener_override(listener_override);
    ((CommandsPanel *)(tabbedWindows->getTabContentComponent(1)))->set_button_listener_override(listener_override);
    ((SettingsPanel *)(tabbedWindows->getTabContentComponent(2)))->set_button_listener_override(listener_override);

    this->playbackPanel->set_button_listener_override(this->button_listener_override);
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="ControlsPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="4" snapActive="1" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="400" initialHeight="500">
  <BACKGROUND backgroundColour="ff355535"/>
  <TABBEDCOMPONENT name="tabbed windows" id="e4e1a529f9184acd" memberName="tabbedWindows"
                   virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 80%" orientation="top"
                   tabBarDepth="35" initialTab="0">
    <TAB name="Playlist" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="playlist_panel.cpp"/>
    <TAB name="Commands" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="commands_panel.cpp"/>
    <TAB name="Settings" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="settings_panel.cpp"/>
    <TAB name="Help" colour="ffb0b040" useJucerComp="1" contentClassName=""
         constructorParams="" jucerComponentFile="help_panel.cpp"/>
  </TABBEDCOMPONENT>
  <JUCERCOMP name="playback panel" id="766c7d08eabd6926" memberName="playbackPanel"
             virtualName="" explicitFocusOrder="0" pos="0% 80% 100% 20%" sourceFile="playback_panel.cpp"
             constructorParams=""/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
