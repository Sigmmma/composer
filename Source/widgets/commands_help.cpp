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

#include "commands_help.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CommandsHelp::CommandsHelp ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    //[/Constructor_pre]

    addAndMakeVisible (label2 = new Label ("new label",
                                           TRANS("* Add\n"
                                           "Adds a new command to the end of the command list.\n"
                                           "\n"
                                           "\n"
                                           "* Remove\n"
                                           "Removes the currently selected command from the command list.\n"
                                           "\n"
                                           "\n"
                                           "* Shift up\n"
                                           "Shifts the currently selected command up.\n"
                                           "\n"
                                           "\n"
                                           "* Shift down\n"
                                           "Shifts the currently selected command down.\n"
                                           "\n"
                                           "\n"
                                           "* Permutation\n"
                                           "Allows you to tweak how the currently SELECTED command specifies a permutation should be chosen. Also displays the permutation currently being played in the section\'s left central box.\n"
                                           "\n"
                                           "- Alt\n"
                                           "Play the alternate loops(if available).\n"
                                           "\n"
                                           "- Any\n"
                                           "Randomly choose a permutation from the available ones.\n"
                                           "\n"
                                           "- Normal\n"
                                           "Play permutations in the way Halo normally would.\n"
                                           "\n"
                                           "- Permutation to play\n"
                                           "If \"Any\" and \"Normal\" are not selected, you can specify which permutation to play with the plus and minus buttons.\n"
                                           "\n"
                                           "\n"
                                           "* Loop count\n"
                                           "Allows you to tweak how many times the currently SELECTED command should be repeated. Also displays the current loop iteration in the section\'s left central box.\n"
                                           "\n"
                                           "- Skip\n"
                                           "Skip over executing this command.\n"
                                           "\n"
                                           "- Endless\n"
                                           "Execute this command endlessly until the track ends.\n"
                                           "\n"
                                           "- Number of loops\n"
                                           "If Endless is not selected, you can specify how many times to execute this command before going on to the next one.")));
    label2->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label2->setJustificationType (Justification::topLeft);
    label2->setEditable (false, false, false);
    label2->setColour (TextEditor::textColourId, Colours::black);
    label2->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (label = new Label ("new label",
                                          TRANS("The Commands tab allows you to carefully tweak how the currently PLAYING track will play. Double click a track in the playlist and then click \"Pause\". The Commands tab will now be populated.\n")));
    label->setFont (Font (16.00f, Font::plain).withTypefaceStyle ("Regular"));
    label->setJustificationType (Justification::topLeft);
    label->setEditable (false, false, false);
    label->setColour (TextEditor::textColourId, Colours::black);
    label->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (330, 1100);


    //[Constructor] You can add your own custom stuff here..
    //[/Constructor]
}

CommandsHelp::~CommandsHelp()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    //[/Destructor_pre]

    label2 = nullptr;
    label = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CommandsHelp::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CommandsHelp::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    label2->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.1100f), proportionOfWidth (1.0000f), proportionOfHeight (0.8900f));
    label->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.0000f), proportionOfWidth (1.0000f), proportionOfHeight (0.1000f));
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

<JUCER_COMPONENT documentType="Component" className="CommandsHelp" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="8" snapActive="1" snapShown="1" overlayOpacity="0.330"
                 fixedSize="1" initialWidth="330" initialHeight="1100">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <LABEL name="new label" id="9a5afc8996a91e8b" memberName="label2" virtualName=""
         explicitFocusOrder="0" pos="0% 11% 100% 89%" edTextCol="ff000000"
         edBkgCol="0" labelText="* Add&#10;Adds a new command to the end of the command list.&#10;&#10;&#10;* Remove&#10;Removes the currently selected command from the command list.&#10;&#10;&#10;* Shift up&#10;Shifts the currently selected command up.&#10;&#10;&#10;* Shift down&#10;Shifts the currently selected command down.&#10;&#10;&#10;* Permutation&#10;Allows you to tweak how the currently SELECTED command specifies a permutation should be chosen. Also displays the permutation currently being played in the section's left central box.&#10;&#10;- Alt&#10;Play the alternate loops(if available).&#10;&#10;- Any&#10;Randomly choose a permutation from the available ones.&#10;&#10;- Normal&#10;Play permutations in the way Halo normally would.&#10;&#10;- Permutation to play&#10;If &quot;Any&quot; and &quot;Normal&quot; are not selected, you can specify which permutation to play with the plus and minus buttons.&#10;&#10;&#10;* Loop count&#10;Allows you to tweak how many times the currently SELECTED command should be repeated. Also displays the current loop iteration in the section's left central box.&#10;&#10;- Skip&#10;Skip over executing this command.&#10;&#10;- Endless&#10;Execute this command endlessly until the track ends.&#10;&#10;- Number of loops&#10;If Endless is not selected, you can specify how many times to execute this command before going on to the next one."
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" kerning="0" bold="0" italic="0"
         justification="9"/>
  <LABEL name="new label" id="9f19921d8c09cd94" memberName="label" virtualName=""
         explicitFocusOrder="0" pos="0% 0% 100% 10%" edTextCol="ff000000"
         edBkgCol="0" labelText="The Commands tab allows you to carefully tweak how the currently PLAYING track will play. Double click a track in the playlist and then click &quot;Pause&quot;. The Commands tab will now be populated.&#10;"
         editableSingleClick="0" editableDoubleClick="0" focusDiscardsChanges="0"
         fontname="Default font" fontsize="16" kerning="0" bold="0" italic="0"
         justification="9"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
