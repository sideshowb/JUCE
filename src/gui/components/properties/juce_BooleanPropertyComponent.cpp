/*
  ==============================================================================

   This file is part of the JUCE library - "Jules' Utility Class Extensions"
   Copyright 2004-10 by Raw Material Software Ltd.

  ------------------------------------------------------------------------------

   JUCE can be redistributed and/or modified under the terms of the GNU General
   Public License (Version 2), as published by the Free Software Foundation.
   A copy of the license is included in the JUCE distribution, or can be found
   online at www.gnu.org/licenses.

   JUCE is distributed in the hope that it will be useful, but WITHOUT ANY
   WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
   A PARTICULAR PURPOSE.  See the GNU General Public License for more details.

  ------------------------------------------------------------------------------

   To release a closed-source product which uses JUCE, commercial licenses are
   available: visit www.rawmaterialsoftware.com/juce for more information.

  ==============================================================================
*/

#include "../../../core/juce_StandardHeader.h"

BEGIN_JUCE_NAMESPACE

#include "juce_BooleanPropertyComponent.h"
#include "../controls/juce_ComboBox.h"


//==============================================================================
BooleanPropertyComponent::BooleanPropertyComponent (const String& name,
                                                    const String& buttonTextWhenTrue,
                                                    const String& buttonTextWhenFalse)
    : PropertyComponent (name),
      onText (buttonTextWhenTrue),
      offText (buttonTextWhenFalse)
{
    addAndMakeVisible (&button);
    button.setClickingTogglesState (false);
    button.addButtonListener (this);
}

BooleanPropertyComponent::BooleanPropertyComponent (const Value& valueToControl,
                                                    const String& name,
                                                    const String& buttonText)
    : PropertyComponent (name),
      onText (buttonText),
      offText (buttonText)
{
    addAndMakeVisible (&button);
    button.setClickingTogglesState (false);
    button.setButtonText (buttonText);
    button.getToggleStateValue().referTo (valueToControl);
    button.setClickingTogglesState (true);
}

BooleanPropertyComponent::~BooleanPropertyComponent()
{
}

void BooleanPropertyComponent::setState (const bool newState)
{
    button.setToggleState (newState, true);
}

bool BooleanPropertyComponent::getState() const
{
    return button.getToggleState();
}

void BooleanPropertyComponent::paint (Graphics& g)
{
    PropertyComponent::paint (g);

    g.setColour (Colours::white);
    g.fillRect (button.getBounds());

    g.setColour (findColour (ComboBox::outlineColourId));
    g.drawRect (button.getBounds());
}

void BooleanPropertyComponent::refresh()
{
    button.setToggleState (getState(), false);
    button.setButtonText (button.getToggleState() ? onText : offText);
}

void BooleanPropertyComponent::buttonClicked (Button*)
{
    setState (! getState());
}

END_JUCE_NAMESPACE
