#pragma once

#include "DistrhoUI.hpp"
#include "defines.h"

// --------------------------------------------------------------------------------------------------------------------

class CCetoneUI : public DISTRHO::UI
{
    // ----------------------------------------------------------------------------------------------------------------

public:
   /**
      UI class constructor.
      The UI should be initialized to a default state that matches the plugin side.
    */
    CCetoneUI();

protected:
    // ----------------------------------------------------------------------------------------------------------------
    // DSP/Plugin Callbacks

   /**
      A parameter has changed on the plugin side.@n
      This is called by the host to inform the UI about parameter changes.
    */
    void parameterChanged(uint32_t index, float value) override;

    // ----------------------------------------------------------------------------------------------------------------
    // Widget Callbacks

   /**
      ImGui specific onDisplay function.
    */
    void onImGuiDisplay() override;

private:
    float fParams[pNumParameters] { 0.0f };

    DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(CCetoneUI)
};

// --------------------------------------------------------------------------------------------------------------------

