/*
==============================================================================

BEGIN_JUCE_MODULE_DECLARATION

   ID:            sintetizador_monofonico
   vendor:        WolfSound
   version:       0.1.0
   name:          Audio Plugin
   description:   Plugin core
   dependencies:  juce_audio_utils

   website:       https://thewolfsound.com
   license:       Unlicense

END_JUCE_MODULE_DECLARATION

==============================================================================
*/

#pragma once

#include <juce_graphics/juce_graphics.h>
#include <juce_gui_basics/juce_gui_basics.h>
#include <juce_core/juce_core.h>
#include <juce_audio_processors/juce_audio_processors.h>
#include <juce_audio_basics/juce_audio_basics.h>
#include <juce_events/juce_events.h>
#include <juce_dsp/juce_dsp.h>


#include <vector>
#include <memory>
#include <functional>
#include <array>
#include <cmath>
#include <ranges>
#include <algorithm>




#include "include/Waveforms.h"
#include "include/Parameters.h"
#include "include/Envelope.h"
#include "include/LadderFilter.h"
#include "include/OscMixer.h"
#include "include/ParameterLayoutBuilder.h"


#include "include/Sintetizador.h"

#include "include/MiniMoogSound.h"
#include "include/MiniMoogVoice.h"

#include "include/PluginProcessor.h"
#include "include/PluginEditor.h"




// #include all additional header files below


