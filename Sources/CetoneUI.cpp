#include "CetoneUI.hpp"

static constexpr const char* kParameterNames[] = {
    "16'",       // pDb0
    "5 1/3'",    // pDb1
    "8'",        // pDb2
    "4'",        // pDb3
    "2 2/3'",    // pDb4
    "2'",        // pDb5
    "1 3/5'",    // pDb6
    "1 1/3'",    // pDb7
    "1'",        // pDb8
    "Tone",      // pTone
    "Keyclick",  // pClick
    "Volume",    // pVolume
    "LfoSpeed",  // pLfoSpeed
    "Vibrato",   // pVibDepth
    "PanPhase",  // pPanPhase
    "PanDepth",  // pPanDepth
    "ChDelayL",  // pChDelayL
    "ChDelayR",  // pChDelayR
    "ChDepth",   // pChDepth
    "ChSpeed",   // pChSpeed
    "ChFeedbk",  // pChFeedback
    "ChMix",     // pChMix
    "RevRoom",   // pRevRoom
    "RevWidth",  // pRevWidth
    "RevDamp",   // pRevDamp
    "RevWet",    // pRevWet
    "RevDry",    // pRevDry
    "OutVol",    // pOutVol
    "ChSwitch",  // pChSwitch
    "RevSwitch", // pRevSwitch
};

// --------------------------------------------------------------------------------------------------------------------

CCetoneUI::CCetoneUI()
    : UI(DISTRHO_UI_DEFAULT_WIDTH, DISTRHO_UI_DEFAULT_HEIGHT, kInternalScalingMatchingHost)
{
}

// --------------------------------------------------------------------------------------------------------------------

void CCetoneUI::parameterChanged(uint32_t index, float value)
{
    DISTRHO_SAFE_ASSERT_RETURN(index < pNumParameters, );

    this->fParams[index] = value;
    repaint();
}

// --------------------------------------------------------------------------------------------------------------------

void CCetoneUI::onImGuiDisplay()
{
    const ImGuiViewport* viewport = ImGui::GetMainViewport();
    ImGui::SetNextWindowPos(viewport->Pos);
    ImGui::SetNextWindowSize(viewport->Size);

    static constexpr auto kWindowFlags =
        ImGuiWindowFlags_NoDecoration |
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoSavedSettings;

    if (ImGui::Begin("##CetoneOrg", nullptr, kWindowFlags))
    {
        ImGui::Text("CetoneOrg Params: ");

        for (uint8_t i = 0; i < pNumParameters; i++)
        {
            if (ImGui::SliderFloat(kParameterNames[i], &fParams[i], 0.0f, 1.0f))
            {
                if (ImGui::IsItemActivated())
                    editParameter(i, true);

                setParameterValue(i, fParams[i]);
            }

            if (ImGui::IsItemDeactivated())
            {
                editParameter(i, false);
            }
        }
    }
    ImGui::End();
}

// --------------------------------------------------------------------------------------------------------------------

START_NAMESPACE_DISTRHO

UI* createUI()
{
    return new CCetoneUI();
}

END_NAMESPACE_DISTRHO

// --------------------------------------------------------------------------------------------------------------------
