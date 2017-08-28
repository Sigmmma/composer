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

#include "playback_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlaybackPanel::PlaybackPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (playbackGroup = new GroupComponent ("playback group",
                                                           TRANS("Playback")));

    addAndMakeVisible (nextTrackButon = new TextButton ("next track button"));
    nextTrackButon->setButtonText (TRANS("Next track"));
    nextTrackButon->addListener (this);
    nextTrackButon->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (playButton = new TextButton ("play button"));
    playButton->setButtonText (TRANS("Play"));
    playButton->addListener (this);
    playButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (stopButton = new TextButton ("stop button"));
    stopButton->setButtonText (TRANS("Stop"));
    stopButton->addListener (this);
    stopButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (label = new Label ("volume label",
                                          TRANS("Volume")));
    label->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::centredLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (volume = new Slider ("volume slider"));
    volume->setRange (0, 100, 1);
    volume->setSliderStyle (Slider::LinearHorizontal);
    volume->setTextBoxStyle (Slider::TextBoxLeft, true, 40, 20);
    volume->addListener (this);


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PlaybackPanel::~PlaybackPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Destructor_pre]

    playbackGroup = nullptr;
    nextTrackButon = nullptr;
    playButton = nullptr;
    stopButton = nullptr;
    label = nullptr;
    volume = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlaybackPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    {
        float x = static_cast<float> (proportionOfWidth (0.0075f)), y = static_cast<float> (proportionOfHeight (0.0900f)), width = static_cast<float> (proportionOfWidth (0.9850f)), height = static_cast<float> (proportionOfHeight (0.8800f));
        Colour fillColour = Colour (0xff1c2e1c);
        //[UserPaintCustomArguments] Customize the painting arguments here..
        //[/UserPaintCustomArguments]
        g.setColour (fillColour);
        g.fillRoundedRectangle (x, y, width, height, 8.000f);
    }

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlaybackPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    playbackGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (1.0000f));
    nextTrackButon->setBounds (proportionOfWidth (0.6725f), proportionOfHeight (0.1569f), proportionOfWidth (0.2705f), proportionOfHeight (0.4412f));
    playButton->setBounds (proportionOfWidth (0.3598f), proportionOfHeight (0.1569f), proportionOfWidth (0.2705f), proportionOfHeight (0.4412f));
    stopButton->setBounds (proportionOfWidth (0.0372f), proportionOfHeight (0.1569f), proportionOfWidth (0.2705f), proportionOfHeight (0.4412f));
    label->setBounds (proportionOfWidth (0.0149f), proportionOfHeight (0.6078f), proportionOfWidth (0.2184f), proportionOfHeight (0.3431f));
    volume->setBounds (proportionOfWidth (0.1936f), proportionOfHeight (0.6078f), proportionOfWidth (0.7767f), proportionOfHeight (0.3431f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void PlaybackPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (this->button_listener_override != nullptr) {
        button_listener_override->buttonClicked(buttonThatWasClicked);
        return;
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == nextTrackButon)
    {
        //[UserButtonCode_nextTrackButon] -- add your button handler code here..
        //[/UserButtonCode_nextTrackButon]
    }
    else if (buttonThatWasClicked == playButton)
    {
        //[UserButtonCode_playButton] -- add your button handler code here..
        //[/UserButtonCode_playButton]
    }
    else if (buttonThatWasClicked == stopButton)
    {
        //[UserButtonCode_stopButton] -- add your button handler code here..
        //[/UserButtonCode_stopButton]
    }

    //[UserbuttonClicked_Post]
    //[/UserbuttonClicked_Post]
}

void PlaybackPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    if (this->slider_listener_override != nullptr) {
        slider_listener_override->sliderValueChanged(sliderThatWasMoved);
        return;
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == volume)
    {
        //[UserSliderCode_volume] -- add your slider handling code here..
        //[/UserSliderCode_volume]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void PlaybackPanel::set_slider_listener_override(juce::Slider::Listener *listener_override) {
    this->slider_listener_override = listener_override;
}
void PlaybackPanel::set_button_listener_override(juce::TextButton::Listener *listener_override) {
    this->button_listener_override = listener_override;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="PlaybackPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="0" snapShown="0" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="400" initialHeight="100">
  <BACKGROUND backgroundColour="1c2e1c">
    <ROUNDRECT pos="0.75% 9% 98.5% 88%" cornerSize="8" fill="solid: ff1c2e1c"
               hasStroke="0"/>
  </BACKGROUND>
  <GROUPCOMPONENT name="playback group" id="f43fd03720d1ecf3" memberName="playbackGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 0% 100% 100%" title="Playback"/>
  <TEXTBUTTON name="next track button" id="9cd535914e35c2d6" memberName="nextTrackButon"
              virtualName="" explicitFocusOrder="0" pos="67.25% 16% 27% 44%"
              bgColOff="ff5ca45c" buttonText="Next track" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="play button" id="86c2605c4b73e043" memberName="playButton"
              virtualName="" explicitFocusOrder="0" pos="36% 16% 27% 44%" bgColOff="ff5ca45c"
              buttonText="Play" connectedEdges="0" needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="stop button" id="d0295b1adc41d116" memberName="stopButton"
              virtualName="" explicitFocusOrder="0" pos="3.75% 16% 27% 44%"
              bgColOff="ff5ca45c" buttonText="Stop" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <LABEL name="volume label" id="ce13aa236c61f86" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="1.5% 61% 21.75% 34%" edTextCol="ff000000"
         edBkgCol="0" labelText="Volume" editableSingleClick="0" editableDoubleClick="0"
         focusDiscardsChanges="0" fontname="Default font" fontsize="15"
         kerning="0" bold="0" italic="0" justification="33"/>
  <SLIDER name="volume slider" id="6b2a0c206fa576e6" memberName="volume"
          virtualName="" explicitFocusOrder="0" pos="19.25% 61% 77.75% 34%"
          min="0" max="100" int="1" style="LinearHorizontal" textBoxPos="TextBoxLeft"
          textBoxEditable="0" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
