/*
 * Dragonfly Reverb, copyright (c) 2019 Michael Willis, Rob van den Berg
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 3 of
 * the License, or any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * For a full copy of the GNU General Public License see the LICENSE file.
 */

#ifndef DRAGONFLY_REVERB_UI_HPP_INCLUDED
#define DRAGONFLY_REVERB_UI_HPP_INCLUDED

#include "AbstractUI.hpp"
#include "ImageWidgets.hpp"
#include "NanoVG.hpp"
#include "DistrhoPlugin.hpp"
#include "Spectrogram.hpp"
#include "LabelledKnob.hpp"
#include "Selection.hpp"

START_NAMESPACE_DISTRHO

// -----------------------------------------------------------------------

class DragonflyReverbUI :
    public DragonflyReverbAbstractUI,
    public ImageSlider::Callback,
    public Selection::Callback
{
public:
    DragonflyReverbUI();

protected:
    // -------------------------------------------------------------------
    // DSP Callbacks

    void parameterChanged ( uint32_t index, float value ) override;
    void stateChanged(const char* key, const char* value) override;

    void programLoaded (uint32_t index);

    // -------------------------------------------------------------------
    // Widget Callbacks
    void imageKnobDragStarted ( ImageKnob* knob ) override;
    void imageKnobDragFinished ( ImageKnob* knob ) override;
    void imageKnobValueChanged ( ImageKnob* knob, float value ) override;
    void imageSliderDragStarted(ImageSlider* slider) override;
    void imageSliderDragFinished(ImageSlider* slider) override;
    void imageSliderValueChanged(ImageSlider* slider, float value) override;
    void selectionClicked(Selection* selection, int option) override;

    void onDisplay() override;
    void uiIdle() override;

private:
    Image imgBackground,imgTabOff,imgTabOn;

    ScopedPointer<ImageSlider> sliderDry, sliderWet;
    ScopedPointer<Spectrogram> spectrogram;
    ScopedPointer<LabelledKnob>
      knobWidth, knobPredelay, knobDecay,
      knobLowCut, knobHighCut, knobDamp;

    ScopedPointer<Selection> algorithmSelection;
    ScopedPointer<Selection> presetSelection1;
    ScopedPointer<Selection> presetSelection2;

    int currentAlg;
    int currentPreset;

    DGL::Rectangle<int> rectSliders[2];
    DGL::Rectangle<int> rectDisplay;

    void updatePresetDefaults();

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR ( DragonflyReverbUI )
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif //
