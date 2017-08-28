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

#include "playlist_help.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
PlaylistHelp::PlaylistHelp ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("* Add\n"
                                           "Adds a new track to the end of the playlist.\n"
                                           "\n"
                                           "\n"
                                           "* Remove\n"
                                           "Removes the currently selected track from the playlist.\n"
                                           "\n"
                                           "\n"
                                           "* Shift up\n"
                                           "Shifts the currently selected track up.\n"
                                           "\n"
                                           "\n"
                                           "* Shift down\n"
                                           "Shifts the currently selected track down.\n"
                                           "\n"
                                           "\n"
                                           "* Loop\n"
                                           "Loops back to the beginning when the last track is played.\n"
                                           "\n"
                                           "\n"
                                           "* Shuffle\n"
                                           "Plays the tracks in a randomized order. Clicking this will force \"Loop\" to be on as the playlist wont be read linearly.\n"
                                           "\n"
                                           "\n"
                                           "* Track playtime\n"
                                           "Number of seconds to play the currently selected track. If set to zero, the track will play forever. When a track is added to the playlist, this will default to 180 seconds(3 minutes). Max time is 1 hour(3600 seconds).\n"
                                           "\n"
                                           "NOTE: To the left of the playtime slider is the number of seconds the currently PLAYING track has played.")));
    label2->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::topLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("The Playlist tab is where you manage the tracks(sound_looping files) in the playlist. The currently playing track will have an arrow off to the left pointing to it. The currently SELECTED track will be highlighted in white.\n"
                                          "\n"
                                          "Aside from the \"Add\' button, all controls on the playlist tab will affect the currently SELECTED track, not the track that is playing.")));
    label->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::topLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (330, 800);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

PlaylistHelp::~PlaylistHelp()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label2 = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void PlaylistHelp::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void PlaylistHelp::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label2->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.2300f), proportionOfWidth (1.0000f), proportionOfHeight (0.7600f));
    label->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.2000f));
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

<JUCER_COMPONENT documentType="Component" className="PlaylistHelp" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="330" initialHeight="800">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <LABEL name="new label" id="9a5afc8996a91e8b" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0% 23% 100% 76%" edTextCol="ff000000"
         edBkgCol="0" labelText="* Add&#10;Adds a new track to the end of the playlist.&#10;&#10;&#10;* Remove&#10;Removes the currently selected track from the playlist.&#10;&#10;&#10;* Shift up&#10;Shifts the currently selected track up.&#10;&#10;&#10;* Shift down&#10;Shifts the currently selected track down.&#10;&#10;&#10;* Loop&#10;Loops back to the beginning when the last track is played.&#10;&#10;&#10;* Shuffle&#10;Plays the tracks in a randomized order. Clicking this will force &quot;Loop&quot; to be on as the playlist wont be read linearly.&#10;&#10;&#10;* Track playtime&#10;Number of seconds to play the currently selected track. If set to zero, the track will play forever. When a track is added to the playlist, this will default to 180 seconds(3 minutes). Max time is 1 hour(3600 seconds).&#10;&#10;NOTE: To the left of the playtime slider is the number of seconds the currently PLAYING track has played."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" kerning="0" bold="0" italic="0"
         justification="9"/>
  <LABEL name="new label" id="9f19921d8c09cd94" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0% 0% 100% 20%" edTextCol="ff000000"
         edBkgCol="0" labelText="The Playlist tab is where you manage the tracks(sound_looping files) in the playlist. The currently playing track will have an arrow off to the left pointing to it. The currently SELECTED track will be highlighted in white.&#10;&#10;Aside from the &quot;Add' button, all controls on the playlist tab will affect the currently SELECTED track, not the track that is playing."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" kerning="0" bold="0" italic="0"
         justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
