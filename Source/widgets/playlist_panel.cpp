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
#include "text_tree_item.cpp"
//[/Headers]

#include "playlist_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlaylistPanel::PlaylistPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (playtimeGroup = new GroupComponent ("playtime group",
                                                           TRANS("Track playtime(seconds)")));

    addAndMakeVisible (playtimeSlider = new Slider ("playtime slider"));
    playtimeSlider->setTooltip (TRANS("Number of seconds to play this sound_looping file for.\n"
    "360  = 6 minutes\n"
    "3600 = 1 hour"));
    playtimeSlider->setRange (0, 3600, 1);
    playtimeSlider->setSliderStyle (Slider::LinearHorizontal);
    playtimeSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 60, 20);
    playtimeSlider->addListener (this);

    addAndMakeVisible (timePlayedLabel = new Label ("time played label",
                                                    TRANS("0")));
    timePlayedLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    timePlayedLabel->setJustificationType (Justification::centredRight);
    timePlayedLabel->setEditable (false, false, false);
    timePlayedLabel->setColour (TextEditor::textColourId, Colours::black);
    timePlayedLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (divLabel = new Label ("div label",
                                             TRANS("/")));
    divLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    divLabel->setJustificationType (Justification::centredLeft);
    divLabel->setEditable (false, false, false);
    divLabel->setColour (TextEditor::textColourId, Colours::black);
    divLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (addTrackButton = new TextButton ("add track button"));
    addTrackButton->setButtonText (TRANS("Add"));
    addTrackButton->addListener (this);
    addTrackButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playShuffledButton = new ToggleButton ("play shuffled button"));
    playShuffledButton->setTooltip (TRANS("Choose random track in playlist to play.\n"
    "Does not keep track of which tracks have been played already."));
    playShuffledButton->setButtonText (TRANS("Shuffle"));
    playShuffledButton->addListener (this);

    addAndMakeVisible (loopPlaylistButton = new ToggleButton ("loop playlist button"));
    loopPlaylistButton->setTooltip (TRANS("Loop the playlist back to be beginning when the end is reached."));
    loopPlaylistButton->setButtonText (TRANS("Loop"));
    loopPlaylistButton->addListener (this);

    addAndMakeVisible (removeTrackButton = new TextButton ("remove track button"));
    removeTrackButton->setButtonText (TRANS("Remove"));
    removeTrackButton->addListener (this);
    removeTrackButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (shiftCommandUpButton = new TextButton ("shift track up button"));
    shiftCommandUpButton->setButtonText (TRANS("Shift up"));
    shiftCommandUpButton->addListener (this);
    shiftCommandUpButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (shiftCommandDownButton = new TextButton ("shift track down button"));
    shiftCommandDownButton->setButtonText (TRANS("Shift down"));
    shiftCommandDownButton->addListener (this);
    shiftCommandDownButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playlistTree = new TreeView ("playlist tree"));
    playlistTree->setRootItemVisible (false);
    playlistTree->setDefaultOpenness (true);
    playlistTree->setColour (TreeView::backgroundColourId, Colour (0xff355535));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    playlistTree->setRootItem(new TextTreeItem(ROOT_ITEM_NAME));
    playtimeSlider->setSkewFactorFromMidPoint(15*60);
    //[/Constructor]
}

PlaylistPanel::~PlaylistPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Destructor_pre]

    playtimeGroup = nullptr;
    playtimeSlider = nullptr;
    timePlayedLabel = nullptr;
    divLabel = nullptr;
    addTrackButton = nullptr;
    playShuffledButton = nullptr;
    loopPlaylistButton = nullptr;
    removeTrackButton = nullptr;
    shiftCommandUpButton = nullptr;
    shiftCommandDownButton = nullptr;
    playlistTree = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlaylistPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlaylistPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    playtimeGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.8549f), proportionOfWidth (1.0000f), proportionOfHeight (0.1451f));
    playtimeSlider->setBounds (proportionOfWidth (0.2630f), proportionOfHeight (0.9039f), proportionOfWidth (0.6948f), proportionOfHeight (0.0569f));
    timePlayedLabel->setBounds (proportionOfWidth (0.0496f), proportionOfHeight (0.9039f), proportionOfWidth (0.1489f), proportionOfHeight (0.0569f));
    divLabel->setBounds (proportionOfWidth (0.2084f), proportionOfHeight (0.8863f), proportionOfWidth (0.0620f), proportionOfHeight (0.0804f));
    addTrackButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.0314f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    playShuffledButton->setBounds (proportionOfWidth (0.0347f), proportionOfHeight (0.7588f), proportionOfWidth (0.2432f), proportionOfHeight (0.0667f));
    loopPlaylistButton->setBounds (proportionOfWidth (0.0347f), proportionOfHeight (0.6863f), proportionOfWidth (0.2432f), proportionOfHeight (0.0667f));
    removeTrackButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.1725f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    shiftCommandUpButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.3922f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    shiftCommandDownButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.5314f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    playlistTree->setBounds (proportionOfWidth (0.3350f), proportionOfHeight (0.0196f), proportionOfWidth (0.6402f), proportionOfHeight (0.8235f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlaylistPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    if (this->slider_listener_override != nullptr) {
        slider_listener_override->sliderValueChanged(sliderThatWasMoved);
        return;
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == playtimeSlider)
    {
        //[UserSliderCode_playtimeSlider] -- add your slider handling code here..
        //[/UserSliderCode_playtimeSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}

void PlaylistPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (this->button_listener_override != nullptr) {
        button_listener_override->buttonClicked(buttonThatWasClicked);
        return;
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == addTrackButton)
    {
        //[UserButtonCode_addTrackButton] -- add your button handler code here..
        //[/UserButtonCode_addTrackButton]
    }
    else if (buttonThatWasClicked == playShuffledButton)
    {
        //[UserButtonCode_playShuffledButton] -- add your button handler code here..
        //[/UserButtonCode_playShuffledButton]
    }
    else if (buttonThatWasClicked == loopPlaylistButton)
    {
        //[UserButtonCode_loopPlaylistButton] -- add your button handler code here..
        //[/UserButtonCode_loopPlaylistButton]
    }
    else if (buttonThatWasClicked == removeTrackButton)
    {
        //[UserButtonCode_removeTrackButton] -- add your button handler code here..
        //[/UserButtonCode_removeTrackButton]
    }
    else if (buttonThatWasClicked == shiftCommandUpButton)
    {
        //[UserButtonCode_shiftCommandUpButton] -- add your button handler code here..
        //[/UserButtonCode_shiftCommandUpButton]
    }
    else if (buttonThatWasClicked == shiftCommandDownButton)
    {
        //[UserButtonCode_shiftCommandDownButton] -- add your button handler code here..
        //[/UserButtonCode_shiftCommandDownButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlaylistPanel::set_slider_listener_override(juce::Slider::Listener *listener_override) {
    this->slider_listener_override = listener_override;
}
void PlaylistPanel::set_button_listener_override(juce::TextButton::Listener *listener_override) {
    this->button_listener_override = listener_override;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlaylistPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="4" snapActive="1" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <GROUPCOMPONENT name="playtime group" id="d5369909835a9c0c" memberName="playtimeGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 85.49% 100% 14.51%"
                  title="Track playtime(seconds)"/>
  <SLIDER name="playtime slider" id="a8f7a96100e92f8b" memberName="playtimeSlider"
          virtualName="" explicitFocusOrder="0" pos="26.303% 90.392% 69.479% 5.686%"
          tooltip="Number of seconds to play this sound_looping file for.&#10;360  = 6 minutes&#10;3600 = 1 hour"
          min="0" max="3600" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="60" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <LABEL name="time played label" id="94fc5986a73ffd97" memberName="timePlayedLabel"
         virtualName="" explicitFocusOrder="0" pos="4.963% 90.392% 14.888% 5.686%"
         edTextCol="ff000000" edBkgCol="0" labelText="0" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="34"/>
  <LABEL name="div label" id="3000737cfb44e213" memberName="divLabel"
         virtualName="" explicitFocusOrder="0" pos="20.844% 88.627% 6.203% 8.039%"
         edTextCol="ff000000" edBkgCol="0" labelText="/" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <TEXTBUTTON name="add track button" id="b2bd91ada8358ed5" memberName="addTrackButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 3.137% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Add" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TOGGLEBUTTON name="play shuffled button" id="d9a925bb58380726" memberName="playShuffledButton"
                virtualName="" explicitFocusOrder="0" pos="3.474% 75.882% 24.318% 6.667%"
                tooltip="Choose random track in playlist to play.&#10;Does not keep track of which tracks have been played already."
                buttonText="Shuffle" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TOGGLEBUTTON name="loop playlist button" id="6f4bb2662f4c0478" memberName="loopPlaylistButton"
                virtualName="" explicitFocusOrder="0" pos="3.474% 68.627% 24.318% 6.667%"
                tooltip="Loop the playlist back to be beginning when the end is reached."
                buttonText="Loop" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <TEXTBUTTON name="remove track button" id="5168ea2970a7936e" memberName="removeTrackButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 17.255% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Remove" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="shift track up button" id="2d0cc6c1e68c41c5" memberName="shiftCommandUpButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 39.216% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Shift up" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="shift track down button" id="6c7416d79b51b7e4" memberName="shiftCommandDownButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 53.137% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Shift down" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TREEVIEW name="playlist tree" id="f2336a51fe6fe161" memberName="playlistTree"
            virtualName="" explicitFocusOrder="0" pos="33.499% 1.961% 64.02% 82.353%"
            backgroundColour="ff355535" rootVisible="0" openByDefault="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
