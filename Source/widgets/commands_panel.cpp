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

#include "commands_panel.h"


//[MiscUserDefs] You can add your own user definitions and misc code here...
//[/MiscUserDefs]

//==============================================================================
CommandsPanel::CommandsPanel ()
{
    //[Constructor_pre] You can add your own custom stuff here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Constructor_pre]

    addAndMakeVisible (loopCommandCountGroup = new GroupComponent ("loop command count group",
                                                                   TRANS("Loop count")));

    addAndMakeVisible (permToPlayGroup = new GroupComponent ("perm to play group",
                                                             TRANS("Permutation")));

    addAndMakeVisible (loopCommandCountGroup2 = new GroupComponent ("loop command count group",
                                                                    String()));

    addAndMakeVisible (loopCommandCountGroup3 = new GroupComponent ("loop command count group",
                                                                    String()));

    addAndMakeVisible (playEndlessButton = new ToggleButton ("play endless button"));
    playEndlessButton->setTooltip (TRANS("Repeat this command until the track timer is up."));
    playEndlessButton->setButtonText (TRANS("Endless"));
    playEndlessButton->addListener (this);

    addAndMakeVisible (playAnyButton = new ToggleButton ("play any button"));
    playAnyButton->setTooltip (TRANS("Play any of the loop permutations."));
    playAnyButton->setButtonText (TRANS("Any"));
    playAnyButton->addListener (this);

    addAndMakeVisible (playAltButton = new ToggleButton ("play alt button"));
    playAltButton->setTooltip (TRANS("Play alternate loops or end."));
    playAltButton->setButtonText (TRANS("Alt"));
    playAltButton->addListener (this);

    addAndMakeVisible (playOrderedButton = new ToggleButton ("play ordered button"));
    playOrderedButton->setTooltip (TRANS("Play permutations in the same way Halo would; going\n"
    "through permutations in order and using the perms\n"
    "skip value to decide whether to skip the perm."));
    playOrderedButton->setButtonText (TRANS("Normal"));
    playOrderedButton->addListener (this);

    addAndMakeVisible (permutationToPlaySlider = new Slider ("permutation to play slider"));
    permutationToPlaySlider->setRange (1, 1, 1);
    permutationToPlaySlider->setSliderStyle (Slider::IncDecButtons);
    permutationToPlaySlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    permutationToPlaySlider->addListener (this);

    addAndMakeVisible (loopCommandCountSlider = new Slider ("loop command count slider"));
    loopCommandCountSlider->setTooltip (TRANS("Number of times to repeat this command."));
    loopCommandCountSlider->setRange (1, 1000, 1);
    loopCommandCountSlider->setSliderStyle (Slider::IncDecButtons);
    loopCommandCountSlider->setTextBoxStyle (Slider::TextBoxLeft, false, 40, 20);
    loopCommandCountSlider->addListener (this);

    addAndMakeVisible (skipButton = new ToggleButton ("skip button"));
    skipButton->setTooltip (TRANS("Disable this command."));
    skipButton->setButtonText (TRANS("Skip"));
    skipButton->addListener (this);

    addAndMakeVisible (addCommandButton = new TextButton ("add command button"));
    addCommandButton->setButtonText (TRANS("Add"));
    addCommandButton->addListener (this);
    addCommandButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (removeCommandButton = new TextButton ("remove command button"));
    removeCommandButton->setButtonText (TRANS("Remove"));
    removeCommandButton->addListener (this);
    removeCommandButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (shiftCommandUpButton = new TextButton ("shift command up button"));
    shiftCommandUpButton->setButtonText (TRANS("Shift up"));
    shiftCommandUpButton->addListener (this);
    shiftCommandUpButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (shiftCommandDownButton = new TextButton ("shift command down button"));
    shiftCommandDownButton->setButtonText (TRANS("Shift down"));
    shiftCommandDownButton->addListener (this);
    shiftCommandDownButton->setColour (TextButton::buttonColourId, Colour (0xff5ca45c));

    addAndMakeVisible (commandsTree = new TreeView ("commands tree"));
    commandsTree->setRootItemVisible (false);
    commandsTree->setDefaultOpenness (true);
    commandsTree->setColour (TreeView::backgroundColourId, Colour (0xff355535));

    addAndMakeVisible (currentLoopLabel = new Label ("current loop label",
                                                     String()));
    currentLoopLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    currentLoopLabel->setJustificationType (Justification::centredLeft);
    currentLoopLabel->setEditable (false, false, false);
    currentLoopLabel->setColour (TextEditor::textColourId, Colours::black);
    currentLoopLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));

    addAndMakeVisible (currentPermLabel = new Label ("current perm label",
                                                     String()));
    currentPermLabel->setFont (Font (15.00f, Font::plain).withTypefaceStyle ("Regular"));
    currentPermLabel->setJustificationType (Justification::centredLeft);
    currentPermLabel->setEditable (false, false, false);
    currentPermLabel->setColour (TextEditor::textColourId, Colours::black);
    currentPermLabel->setColour (TextEditor::backgroundColourId, Colour (0x00000000));


    //[UserPreSize]
    //[/UserPreSize]

    setSize (400, 400);


    //[Constructor] You can add your own custom stuff here..
    commandsTree->setRootItem(new TextTreeItem(ROOT_ITEM_NAME));
    //[/Constructor]
}

CommandsPanel::~CommandsPanel()
{
    //[Destructor_pre]. You can add your own custom destruction code here..
    this->slider_listener_override = nullptr;
    this->button_listener_override = nullptr;
    //[/Destructor_pre]

    loopCommandCountGroup = nullptr;
    permToPlayGroup = nullptr;
    loopCommandCountGroup2 = nullptr;
    loopCommandCountGroup3 = nullptr;
    playEndlessButton = nullptr;
    playAnyButton = nullptr;
    playAltButton = nullptr;
    playOrderedButton = nullptr;
    permutationToPlaySlider = nullptr;
    loopCommandCountSlider = nullptr;
    skipButton = nullptr;
    addCommandButton = nullptr;
    removeCommandButton = nullptr;
    shiftCommandUpButton = nullptr;
    shiftCommandDownButton = nullptr;
    commandsTree = nullptr;
    currentLoopLabel = nullptr;
    currentPermLabel = nullptr;


    //[Destructor]. You can add your own custom destruction code here..
    //[/Destructor]
}

//==============================================================================
void CommandsPanel::paint (Graphics& g)
{
    //[UserPrePaint] Add your own custom painting code here..
    //[/UserPrePaint]

    g.fillAll (Colour (0xff1c2e1c));

    //[UserPaint] Add your own custom painting code here..
    //[/UserPaint]
}

void CommandsPanel::resized()
{
    //[UserPreResize] Add your own custom resize code here..
    //[/UserPreResize]

    loopCommandCountGroup->setBounds (proportionOfWidth (0.5112f), proportionOfHeight (0.6667f), proportionOfWidth (0.4888f), proportionOfHeight (0.3333f));
    permToPlayGroup->setBounds (proportionOfWidth (0.0000f), proportionOfHeight (0.6667f), proportionOfWidth (0.4888f), proportionOfHeight (0.3333f));
    loopCommandCountGroup2->setBounds (proportionOfWidth (0.5310f), proportionOfHeight (0.7745f), proportionOfWidth (0.1687f), proportionOfHeight (0.1177f));
    loopCommandCountGroup3->setBounds (proportionOfWidth (0.0223f), proportionOfHeight (0.7745f), proportionOfWidth (0.1687f), proportionOfHeight (0.1177f));
    playEndlessButton->setBounds (proportionOfWidth (0.7221f), proportionOfHeight (0.8039f), proportionOfWidth (0.2457f), proportionOfHeight (0.0784f));
    playAnyButton->setBounds (proportionOfWidth (0.2109f), proportionOfHeight (0.7157f), proportionOfWidth (0.2457f), proportionOfHeight (0.0784f));
    playAltButton->setBounds (proportionOfWidth (0.0347f), proportionOfHeight (0.7157f), proportionOfWidth (0.1762f), proportionOfHeight (0.0784f));
    playOrderedButton->setBounds (proportionOfWidth (0.2109f), proportionOfHeight (0.8039f), proportionOfWidth (0.2457f), proportionOfHeight (0.0784f));
    permutationToPlaySlider->setBounds (proportionOfWidth (0.0521f), proportionOfHeight (0.8922f), proportionOfWidth (0.3970f), proportionOfHeight (0.0784f));
    loopCommandCountSlider->setBounds (proportionOfWidth (0.5509f), proportionOfHeight (0.8922f), proportionOfWidth (0.3970f), proportionOfHeight (0.0784f));
    skipButton->setBounds (proportionOfWidth (0.7221f), proportionOfHeight (0.7157f), proportionOfWidth (0.2457f), proportionOfHeight (0.0784f));
    addCommandButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.0314f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    removeCommandButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.1725f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    shiftCommandUpButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.3922f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    shiftCommandDownButton->setBounds (proportionOfWidth (0.0199f), proportionOfHeight (0.5314f), proportionOfWidth (0.2978f), proportionOfHeight (0.1216f));
    commandsTree->setBounds (proportionOfWidth (0.3350f), proportionOfHeight (0.0196f), proportionOfWidth (0.6402f), proportionOfHeight (0.6314f));
    currentLoopLabel->setBounds (proportionOfWidth (0.5633f), proportionOfHeight (0.8039f), proportionOfWidth (0.1042f), proportionOfHeight (0.0706f));
    currentPermLabel->setBounds (proportionOfWidth (0.0571f), proportionOfHeight (0.8039f), proportionOfWidth (0.1042f), proportionOfHeight (0.0706f));
    //[UserResized] Add your own custom resize handling here..
    //[/UserResized]
}

void CommandsPanel::buttonClicked (Button* buttonThatWasClicked)
{
    //[UserbuttonClicked_Pre]
    if (this->button_listener_override != nullptr) {
        button_listener_override->buttonClicked(buttonThatWasClicked);
        return;
    }
    //[/UserbuttonClicked_Pre]

    if (buttonThatWasClicked == playEndlessButton)
    {
        //[UserButtonCode_playEndlessButton] -- add your button handler code here..
        //[/UserButtonCode_playEndlessButton]
    }
    else if (buttonThatWasClicked == playAnyButton)
    {
        //[UserButtonCode_playAnyButton] -- add your button handler code here..
        //[/UserButtonCode_playAnyButton]
    }
    else if (buttonThatWasClicked == playAltButton)
    {
        //[UserButtonCode_playAltButton] -- add your button handler code here..
        //[/UserButtonCode_playAltButton]
    }
    else if (buttonThatWasClicked == playOrderedButton)
    {
        //[UserButtonCode_playOrderedButton] -- add your button handler code here..
        //[/UserButtonCode_playOrderedButton]
    }
    else if (buttonThatWasClicked == skipButton)
    {
        //[UserButtonCode_skipButton] -- add your button handler code here..
        //[/UserButtonCode_skipButton]
    }
    else if (buttonThatWasClicked == addCommandButton)
    {
        //[UserButtonCode_addCommandButton] -- add your button handler code here..
        //[/UserButtonCode_addCommandButton]
    }
    else if (buttonThatWasClicked == removeCommandButton)
    {
        //[UserButtonCode_removeCommandButton] -- add your button handler code here..
        //[/UserButtonCode_removeCommandButton]
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

void CommandsPanel::sliderValueChanged (Slider* sliderThatWasMoved)
{
    //[UsersliderValueChanged_Pre]
    if (this->slider_listener_override != nullptr) {
        slider_listener_override->sliderValueChanged(sliderThatWasMoved);
        return;
    }
    //[/UsersliderValueChanged_Pre]

    if (sliderThatWasMoved == permutationToPlaySlider)
    {
        //[UserSliderCode_permutationToPlaySlider] -- add your slider handling code here..
        //[/UserSliderCode_permutationToPlaySlider]
    }
    else if (sliderThatWasMoved == loopCommandCountSlider)
    {
        //[UserSliderCode_loopCommandCountSlider] -- add your slider handling code here..
        //[/UserSliderCode_loopCommandCountSlider]
    }

    //[UsersliderValueChanged_Post]
    //[/UsersliderValueChanged_Post]
}



//[MiscUserCode] You can add your own definitions of your custom methods or any other code here...
void CommandsPanel::set_slider_listener_override(juce::Slider::Listener *listener_override) {
    this->slider_listener_override = listener_override;
}
void CommandsPanel::set_button_listener_override(juce::TextButton::Listener *listener_override) {
    this->button_listener_override = listener_override;
}
//[/MiscUserCode]


//==============================================================================
#if 0
/*  -- Projucer information section --

    This is where the Projucer stores the metadata that describe this GUI layout, so
    make changes in here at your peril!

BEGIN_JUCER_METADATA

<JUCER_COMPONENT documentType="Component" className="CommandsPanel" componentName=""
                 parentClasses="public Component" constructorParams="" variableInitialisers=""
                 snapPixels="4" snapActive="1" snapShown="0" overlayOpacity="0.330"
                 fixedSize="0" initialWidth="400" initialHeight="400">
  <BACKGROUND backgroundColour="ff1c2e1c"/>
  <GROUPCOMPONENT name="loop command count group" id="a08347763fa099b6" memberName="loopCommandCountGroup"
                  virtualName="" explicitFocusOrder="0" pos="51.117% 66.667% 48.883% 33.333%"
                  title="Loop count"/>
  <GROUPCOMPONENT name="perm to play group" id="b41270919bdf338d" memberName="permToPlayGroup"
                  virtualName="" explicitFocusOrder="0" pos="0% 66.667% 48.883% 33.333%"
                  title="Permutation"/>
  <GROUPCOMPONENT name="loop command count group" id="300b8fe137de5934" memberName="loopCommandCountGroup2"
                  virtualName="" explicitFocusOrder="0" pos="53.102% 77.451% 16.873% 11.765%"
                  title=""/>
  <GROUPCOMPONENT name="loop command count group" id="81a2d865a1df78b2" memberName="loopCommandCountGroup3"
                  virtualName="" explicitFocusOrder="0" pos="2.233% 77.451% 16.873% 11.765%"
                  title=""/>
  <TOGGLEBUTTON name="play endless button" id="341d24807f91e886" memberName="playEndlessButton"
                virtualName="" explicitFocusOrder="0" pos="72.208% 80.392% 24.566% 7.843%"
                tooltip="Repeat this command until the track timer is up." buttonText="Endless"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="play any button" id="e089b1fcedfd8f44" memberName="playAnyButton"
                virtualName="" explicitFocusOrder="0" pos="21.092% 71.569% 24.566% 7.843%"
                tooltip="Play any of the loop permutations." buttonText="Any"
                connectedEdges="0" needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="play alt button" id="4cb55af78393c915" memberName="playAltButton"
                virtualName="" explicitFocusOrder="0" pos="3.474% 71.569% 17.618% 7.843%"
                tooltip="Play alternate loops or end." buttonText="Alt" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TOGGLEBUTTON name="play ordered button" id="f9b190eec6e18228" memberName="playOrderedButton"
                virtualName="" explicitFocusOrder="0" pos="21.092% 80.392% 24.566% 7.843%"
                tooltip="Play permutations in the same way Halo would; going&#10;through permutations in order and using the perms&#10;skip value to decide whether to skip the perm."
                buttonText="Normal" connectedEdges="0" needsCallback="1" radioGroupId="0"
                state="0"/>
  <SLIDER name="permutation to play slider" id="52d2fd1e73ecabe6" memberName="permutationToPlaySlider"
          virtualName="" explicitFocusOrder="0" pos="5.211% 89.216% 39.702% 7.843%"
          min="1" max="1" int="1" style="IncDecButtons" textBoxPos="TextBoxLeft"
          textBoxEditable="1" textBoxWidth="40" textBoxHeight="20" skewFactor="1"
          needsCallback="1"/>
  <SLIDER name="loop command count slider" id="2e31fbd76cb47a6" memberName="loopCommandCountSlider"
          virtualName="" explicitFocusOrder="0" pos="55.087% 89.216% 39.702% 7.843%"
          tooltip="Number of times to repeat this command." min="1" max="1000"
          int="1" style="IncDecButtons" textBoxPos="TextBoxLeft" textBoxEditable="1"
          textBoxWidth="40" textBoxHeight="20" skewFactor="1" needsCallback="1"/>
  <TOGGLEBUTTON name="skip button" id="c750cc213e5fe1b8" memberName="skipButton"
                virtualName="" explicitFocusOrder="0" pos="72.208% 71.569% 24.566% 7.843%"
                tooltip="Disable this command." buttonText="Skip" connectedEdges="0"
                needsCallback="1" radioGroupId="0" state="0"/>
  <TEXTBUTTON name="add command button" id="b2bd91ada8358ed5" memberName="addCommandButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 3.137% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Add" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="remove command button" id="8a4a1c87f5200c0a" memberName="removeCommandButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 17.255% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Remove" connectedEdges="0" needsCallback="1"
              radioGroupId="0"/>
  <TEXTBUTTON name="shift command up button" id="2d0cc6c1e68c41c5" memberName="shiftCommandUpButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 39.216% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Shift up" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TEXTBUTTON name="shift command down button" id="6c7416d79b51b7e4" memberName="shiftCommandDownButton"
              virtualName="" explicitFocusOrder="0" pos="1.985% 53.137% 29.777% 12.157%"
              bgColOff="ff5ca45c" buttonText="Shift down" connectedEdges="0"
              needsCallback="1" radioGroupId="0"/>
  <TREEVIEW name="commands tree" id="f2336a51fe6fe161" memberName="commandsTree"
            virtualName="" explicitFocusOrder="0" pos="33.499% 1.961% 64.02% 63.137%"
            backgroundColour="ff355535" rootVisible="0" openByDefault="1"/>
  <LABEL name="current loop label" id="a8f4d370f5373a97" memberName="currentLoopLabel"
         virtualName="" explicitFocusOrder="0" pos="56.328% 80.392% 10.422% 7.059%"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
  <LABEL name="current perm label" id="abd86d5780331aa3" memberName="currentPermLabel"
         virtualName="" explicitFocusOrder="0" pos="5.707% 80.392% 10.422% 7.059%"
         edTextCol="ff000000" edBkgCol="0" labelText="" editableSingleClick="0"
         editableDoubleClick="0" focusDiscardsChanges="0" fontname="Default font"
         fontsize="15" kerning="0" bold="0" italic="0" justification="33"/>
</JUCER_COMPONENT>

END_JUCER_METADATA
*/
#endif


//[EndFile] You can add extra defines here...
//[/EndFile]
