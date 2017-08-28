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

#include "settings_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
SettingsPanel::SettingsPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (fileGroup3 = new GroupComponent ("file group",
                                                        TRANS("Playlists directory")));

    addAndMakeVisible (playlistSettingsGroup = new GroupComponent ("playlist settings group",
                                                                   TRANS("Current playlist settings")));

    addAndMakeVisible (fileGroup2 = new GroupComponent ("file group",
                                                        TRANS("Tags directory")));

    addAndMakeVisible (infoLabel1 = new Label ("info label 1",
                                               TRANS("All sound_looping files in this playlist must be inside this folder.\n"
                                               "Any sound files they reference must also be inside it.")));
    infoLabel1->setFont (Font ("Calibri", 14.00f, Font::plain).withTypefaceStyle ("Bold"));
    infoLabel1->setJustificationType (Justification::topLeft);
    infoLabel1->setEditable (false, false, false);
    infoLabel1->setColour (TextEditor::textColourId, Colours::black);
    infoLabel1->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (loadPlaylistButton = new TextButton ("load playlist button"));
    loadPlaylistButton->setButtonText (TRANS("Load playlist"));
    loadPlaylistButton->addListener (this);
    loadPlaylistButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playlistPath = new TextEditor ("playlist path"));
    playlistPath->setMultiLine (false);
    playlistPath->setReturnKeyStartsNewLine (false);
    playlistPath->setReadOnly (true);
    playlistPath->setScrollbarsShown (false);
    playlistPath->setCaretVisible (false);
    playlistPath->setPopupMenuEnabled (false);
    playlistPath->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    playlistPath->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    playlistPath->setText (String());

    addAndMakeVisible (savePlaylistButton = new TextButton ("save playlist button"));
    savePlaylistButton->setButtonText (TRANS("Save playlist"));
    savePlaylistButton->addListener (this);
    savePlaylistButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playlistTagsDir = new TextEditor ("playlist tags dir"));
    playlistTagsDir->setMultiLine (false);
    playlistTagsDir->setReturnKeyStartsNewLine (false);
    playlistTagsDir->setReadOnly (true);
    playlistTagsDir->setScrollbarsShown (false);
    playlistTagsDir->setCaretVisible (false);
    playlistTagsDir->setPopupMenuEnabled (false);
    playlistTagsDir->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    playlistTagsDir->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    playlistTagsDir->setText (String());

    addAndMakeVisible (playlistsDir = new TextEditor ("playlists dir"));
    playlistsDir->setMultiLine (false);
    playlistsDir->setReturnKeyStartsNewLine (false);
    playlistsDir->setReadOnly (false);
    playlistsDir->setScrollbarsShown (false);
    playlistsDir->setCaretVisible (true);
    playlistsDir->setPopupMenuEnabled (false);
    playlistsDir->setColour (TextEditor::outlineColourId, Colour (0x00000000));
    playlistsDir->setColour (TextEditor::shadowColourId, Colour (0x00000000));
    playlistsDir->setText (String());

    addAndMakeVisible (tagsdirButton = new TextButton ("tagsdir button"));
    tagsdirButton->setButtonText (TRANS("Change tags directory"));
    tagsdirButton->addListener (this);
    tagsdirButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (newPlaylistButton = new TextButton ("new playlist button"));
    newPlaylistButton->setButtonText (TRANS("New playlist"));
    newPlaylistButton->addListener (this);
    newPlaylistButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playlistsDirButton = new TextButton ("playlists dir button"));
    playlistsDirButton->setButtonText (TRANS("Change playlists directory"));
    playlistsDirButton->addListener (this);
    playlistsDirButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (350, 400);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

SettingsPanel::~SettingsPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Destructor_pre]

    fileGroup3 = nullptr;
    playlistSettingsGroup = nullptr;
    fileGroup2 = nullptr;
    infoLabel1 = nullptr;
    loadPlaylistButton = nullptr;
    playlistPath = nullptr;
    savePlaylistButton = nullptr;
    playlistTagsDir = nullptr;
    playlistsDir = nullptr;
    tagsdirButton = nullptr;
    newPlaylistButton = nullptr;
    playlistsDirButton = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void SettingsPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void SettingsPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    fileGroup3->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.7000f), proportionOfWidth (1.0000f), proportionOfHeight (0.2941f));
    playlistSettingsGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.7000f));
    fileGroup2->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2941f), proportionOfWidth (1.0000f), proportionOfHeight (0.4059f));
    infoLabel1->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.4118f), proportionOfWidth (0.9677f), proportionOfHeight (0.1412f));
    loadPlaylistButton->setBounds (proportionOfWidth (0.3623f), proportionOfHeight (0.0628f), proportionOfWidth (0.2481f), proportionOfHeight (0.1235f));
    playlistPath->setBounds (proportionOfWidth (0.0347f), proportionOfHeight (0.2196f), proportionOfWidth (0.9181f), proportionOfHeight (0.0628f));
    savePlaylistButton->setBounds (proportionOfWidth (0.6923f), proportionOfHeight (0.0628f), proportionOfWidth (0.2481f), proportionOfHeight (0.1235f));
    playlistTagsDir->setBounds (proportionOfWidth (0.0347f), proportionOfHeight (0.3549f), proportionOfWidth (0.9181f), proportionOfHeight (0.0628f));
    playlistsDir->setBounds (proportionOfWidth (0.0397f), proportionOfHeight (0.7549f), proportionOfWidth (0.9181f), proportionOfHeight (0.0628f));
    tagsdirButton->setBounds (proportionOfWidth (0.0397f), proportionOfHeight (0.5529f), proportionOfWidth (0.9181f), proportionOfHeight (0.1196f));
    newPlaylistButton->setBounds (proportionOfWidth (0.0397f), proportionOfHeight (0.0628f), proportionOfWidth (0.2481f), proportionOfHeight (0.1235f));
    playlistsDirButton->setBounds (proportionOfWidth (0.0397f), proportionOfHeight (0.8451f), proportionOfWidth (0.9181f), proportionOfHeight (0.1196f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void SettingsPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (this->button_listener_override != nullptr) {
        button_listener_override->buttonClicked(buttonThatWasClicked);
        return;
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == loadPlaylistButton)
    {
        //[UserButtonCode_loadPlaylistButton] -- add your button handler code here..
        //[/UserButtonCode_loadPlaylistButton]
    }
    else if (buttonThatWasClicked == savePlaylistButton)
    {
        //[UserButtonCode_savePlaylistButton] -- add your button handler code here..
        //[/UserButtonCode_savePlaylistButton]
    }
    else if (buttonThatWasClicked == tagsdirButton)
    {
        //[UserButtonCode_tagsdirButton] -- add your button handler code here..
        //[/UserButtonCode_tagsdirButton]
    }
    else if (buttonThatWasClicked == newPlaylistButton)
    {
        //[UserButtonCode_newPlaylistButton] -- add your button handler code here..
        //[/UserButtonCode_newPlaylistButton]
    }
    else if (buttonThatWasClicked == playlistsDirButton)
    {
        //[UserButtonCode_playlistsDirButton] -- add your button handler code here..
        //[/UserButtonCode_playlistsDirButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void SettingsPanel::set_slider_listener_override(juce::Slider::Listener *listener_override) {
    this->slider_listener_override = listener_override;
}
void SettingsPanel::set_button_listener_override(juce::TextButton::Listener *listener_override) {
    this->button_listener_override = listener_override;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="SettingsPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="350" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <GROUPCOMPONENT name="file group" id="7faae2bf6fe0dc25" memberName="fileGroup3"
                  virtualName="" explicitFocusOrder="0" pos="0% 70% 100% 29.412%"
                  title="Playlists directory"/>
  <GROUPCOMPONENT name="playlist settings group" id="9e32b2b4d0603d61" memberName="playlistSettingsGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 70%" title="Current playlist settings"/>
  <GROUPCOMPONENT name="file group" id="94a185cce45b6fc" memberName="fileGroup2"
                  virtualName="" explicitFocusOrder="0" pos="0% 29.412% 100% 40.588%"
                  title="Tags directory"/>
  <LABEL name="info label 1" id="94fc9d596b8f2814" memberName="infoLabel1"
         virtualName="" explicitFocusOrder="0" pos="1.985% 41.176% 96.774% 14.118%"
         edTextCol="ff000000" edBkgCol="0" labelText="All sound_looping files in this playlist must be inside this folder.&#10;Any sound files they reference must also be inside it."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Calibri" fontsize="14" kerning="0" bold="1" italic="0"
         justification="9" typefaceStyle="Bold"/>
  <TEXTBUTTON name="load playlist button" id="af7814a07fa26dd8" memberName="loadPlaylistButton"
              virtualName="" explicitFocusOrder="0" pos="36.228% 6.275% 24.814% 12.353%"
              bgColOff="ff5ca45c" buttonText="Load playlist" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="playlist path" id="8c1ab737065ccdd9" memberName="playlistPath"
              virtualName="" explicitFocusOrder="0" pos="3.474% 21.961% 91.811% 6.275%"
              outlinecol="0" shadowcol="0" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="1" scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTBUTTON name="save playlist button" id="43aa8e49ba34c64e" memberName="savePlaylistButton"
              virtualName="" explicitFocusOrder="0" pos="69.231% 6.275% 24.814% 12.353%"
              bgColOff="ff5ca45c" buttonText="Save playlist" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTEDITOR name="playlist tags dir" id="1d94811597726cc5" memberName="playlistTagsDir"
              virtualName="" explicitFocusOrder="0" pos="3.474% 35.49% 91.811% 6.275%"
              outlinecol="0" shadowcol="0" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="1" scrollbars="0" caret="0" popupmenu="0"/>
  <TEXTEDITOR name="playlists dir" id="e2ecf35e35203d6b" memberName="playlistsDir"
              virtualName="" explicitFocusOrder="0" pos="3.97% 75.49% 91.811% 6.275%"
              outlinecol="0" shadowcol="0" initialText="" multiline="0" retKeyStartsLine="0"
              readonly="0" scrollbars="0" caret="1" popupmenu="0"/>
  <TEXTBUTTON name="tagsdir button" id="cf61e7ae7442e78f" memberName="tagsdirButton"
              virtualName="" explicitFocusOrder="0" pos="3.97% 55.294% 91.811% 11.961%"
              bgColOff="ff5ca45c" buttonText="Change tags directory" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="new playlist button" id="7d701b90f27cd87a" memberName="newPlaylistButton"
              virtualName="" explicitFocusOrder="0" pos="3.97% 6.275% 24.814% 12.353%"
              bgColOff="ff5ca45c" buttonText="New playlist" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="playlists dir button" id="1a070de37d3e6572" memberName="playlistsDirButton"
              virtualName="" explicitFocusOrder="0" pos="3.97% 84.51% 91.811% 11.961%"
              bgColOff="ff5ca45c" buttonText="Change playlists directory" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
