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

#pragma once

//[Headers]     -- You can add your own extra header files here --
#include "../JuceLibraryCode/JuceHeader.h"
//[/Headers]



//==============================================================================
/**
                                                                    //[Comments]
    An auto-generated component, created by the Projucer.

    Describe your class and how it works here!
                                                                    //[/Comments]
*/
class PlaylistPanel  : public Component,
                       public SliderListener,
                       public ButtonListener
{
public:
    //==============================================================================
    PlaylistPanel ();
    ~PlaylistPanel();

    //==============================================================================
    //[UserMethods]     -- You can add your own custom methods in this section.
    void set_slider_listener_override(juce::Slider::Listener *listener_override);
    void set_button_listener_override(juce::TextButton::Listener *listener_override);
    //[/UserMethods]

    void paint (Graphics& g) override;
    void resized() override;
    void sliderValueChanged (Slider* sliderThatWasMoved) override;
    void buttonClicked (Button* buttonThatWasClicked) override;



private:
    //[UserVariables]   -- You can add your own custom variables in this section.
public:  // screw having to deal with private access on such a simple program gui.
    juce::Slider::Listener     *slider_listener_override;
    juce::TextButton::Listener *button_listener_override;
    //[/UserVariables]

    //==============================================================================
    ScopedPointer<GroupComponent> playtimeGroup;
    ScopedPointer<Slider> playtimeSlider;
    ScopedPointer<Label> timePlayedLabel;
    ScopedPointer<Label> divLabel;
    ScopedPointer<TextButton> addTrackButton;
    ScopedPointer<ToggleButton> playShuffledButton;
    ScopedPointer<ToggleButton> loopPlaylistButton;
    ScopedPointer<TextButton> removeTrackButton;
    ScopedPointer<TextButton> shiftCommandUpButton;
    ScopedPointer<TextButton> shiftCommandDownButton;
    ScopedPointer<TreeView> playlistTree;


    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (PlaylistPanel)
};

//[EndFile] You can add extra defines here...
//[/EndFile]
