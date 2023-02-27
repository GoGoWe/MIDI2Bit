//
// Created by philip on 26.02.23.
//

#include <iostream>
#include "MidiStringParser.h"

int main(){
    MidiStringParser parser;
    const std::vector<int8_t> *noteVector = parser.generateMidiInts("C-2 C#-2 D-2 D#-2 E-2 F-2 F#-2 G-2 G#-2 A-2 A#-2 B-2");
    for (const auto &item: *noteVector){
        std::cout << std::to_string(item) << std::endl;
    }
}