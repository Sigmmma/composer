/*
   Composer: A Halo specific music player
   Copyright (C) 2017 Devin Bobadilla

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software Foundation,
   Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
*/

#include "../JuceLibraryCode/JuceHeader.h"

// used to let an item know if it as a root node
const char ROOT_ITEM_NAME[] = "<ROOT>";


class TextTreeItem : public TreeViewItem
{
public:

    TextTreeItem(const char *text) {
        this->text = juce::String(text);
        this->active_index    = NULL;
        this->callback_object = NULL;
        this->click_callback  = NULL;
        this->double_click_callback = NULL;
    }

    TextTreeItem(const juce::String text) {
        this->text = text;
    }

    bool mightContainSubItems() override
    {
        if (!this->text.compare(ROOT_ITEM_NAME)) return true;
        if (this->active_index == NULL)          return false;
        return (this->getIndexInParent() == *this->active_index);
    }

    void paintItem(Graphics& g, int width, int height) override
    {
        if (this->isSelected()) {
            g.fillAll(Colours::white);
        }
        g.setColour(Colours::black);
        g.drawText(this->text, 0, 0, width, height, Justification::left);
    }

    void itemOpennessChanged(bool isNowOpen) {
        if (isNowOpen && this->text.compare(ROOT_ITEM_NAME)) this->setOpen(false);
    }

    void itemSelectionChanged(bool isNowSelected) override {
        this->repaintItem();
        if (!isNowSelected) return;
        if (this->callback_object == NULL) return;
        if (this->click_callback  == NULL) return;
        (*this->click_callback)(this->callback_object, this->getIndexInParent());
    }

    void itemClicked(const MouseEvent &e) {
        this->repaintItem();
    }

    void itemDoubleClicked(const MouseEvent &e) {
        if (this->callback_object == NULL) return;
        if (this->click_callback == NULL) return;
        (*this->double_click_callback)(this->callback_object, this->getIndexInParent());
    }

    int          *active_index;
    juce::String  text;
    void         *callback_object;
    void        (*click_callback)(void *object, int index);
    void        (*double_click_callback)(void *object, int index);


    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(TextTreeItem)
};