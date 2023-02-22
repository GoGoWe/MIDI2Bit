# MIDI2Bit
Research project about MIDI Files and 8 Bit Music


# Additions 
The projects should additionally convert midi files in 8 Bit Music in the future. 
This could be achived with following technologies (more research is needed):
- 8 Bit VST Plugins: https://www.mattmontag.com/projects-page/nintendo-vst
- https://integraudio.com/best-tools-to-develop-vst-plugins/
- https://steinbergmedia.github.io/vst3_dev_portal/pages/Technical+Documentation/Change+History/3.0.1/IMidiMapping.html
- https://steinbergmedia.github.io/vst3_doc/vstinterfaces/classSteinberg_1_1Vst_1_1IMidiMapping.html
- https://steinbergmedia.github.io/vst3_doc/vstsdk/index.html
- Response from ChatGPT:
Yes, you can use a VST (Virtual Studio Technology) DLL to create music using C++. VST is a software interface standard that allows you to use plugins to create sound in a digital audio workstation (DAW) or any other host application. To use a VST DLL in C++, you'll need to write code to interact with the VST API, which provides functions for loading the plugin, initializing and manipulating its parameters, and processing audio data.

You can use any C++ development environment, such as Visual Studio or Xcode, to write the code for your VST plugin. However, there are also several open-source C++ frameworks, such as JUCE or wdl-ol, that can simplify the process of creating VST plugins. These frameworks provide a set of classes and functions that handle the low-level details of the VST API, so you can focus on implementing the sound processing and control logic for your plugin.

If you're new to creating VST plugins, you might want to start by reading some introductory tutorials and examples online, and then experiment with creating simple plugins before moving on to more complex projects.
- 