#include <vector> 
#include <iostream>

typedef unsigned char byte;

class MIDItrack: public std::vector<byte>{
    private:
    uint64_t delay = 0;

    public:

    void AddBytes(byte data){
        push_back(data);
    }

    void Flush()
    {
        
        uint64_t splitBytes;
        uint64_t firstByte;

        if(delay > 127){

            if(delay < 16384){
                firstByte = delay/128;
                splitBytes = firstByte + 128;
            }
            else{
                std::cout << "ERROR: delay can not be greater than 16383" << std::endl;
            }
            AddBytes(splitBytes);
            splitBytes = delay - (128*firstByte);
            AddBytes(splitBytes);
        }
        else{
            splitBytes = delay;
            AddBytes(splitBytes);
        }
    }

    void AddDelay(uint64_t delayAmount){
        delay += delayAmount;
        Flush();
        delay = 0;
    }

    void KeyOn(int note, int pressure = 127, int channel = 0)
    {
        if(note >= 0){
            AddBytes(0x00);
            AddBytes(0x90|channel);
            AddBytes(note);
            AddBytes(pressure);
        }
    }
    
    void KeyOff(int note, int pressure = 127, int channel = 0)
    {
        if(note >= 0){
            AddBytes(0x80|channel);
            AddBytes(note);
            AddBytes(pressure);    
        }
    }

    void changeSynth(int device){
        AddBytes(0xC0);
        AddBytes(device);
    }

};

class MIDIFile: public std::vector<byte>{
private:
    uint64_t tempo;
    MIDItrack* data;
public:

    MIDIFile(MIDItrack* midiData): tempo(1000000), data(midiData)
    {
    }

    void AddBytes(byte data){
        push_back(data);
    }

    void Start(){
        const byte midiPrefix[18] = 
        {
            0x4D, 0x54, 0x68, 0x64, 0x00, 0x00, 0x00, 0x06,
            0x00, 0x01, 0x00, 0x01, 0x03, 0xE8, 0x4D, 0x54,
            0x72, 0x6B,
        };

        for(int i = 0; i < 18; i++){
            AddBytes(midiPrefix[i]);
        }

        uint64_t dataSize = data->size() + 19;
        // Add Track Size
        AddBytes(dataSize >> 24);
        AddBytes(dataSize >> 16);
        AddBytes(dataSize >>  8);
        AddBytes(dataSize >>  0);

        // Add Track end
        AddBytes(0x00);
        AddBytes(0xFF);

        // ADD misc settings
        AddBytes(0x58);
        AddBytes(0x04);
        AddBytes(0x04);
        AddBytes(0x02);
        AddBytes(0x18);
        AddBytes(0x08);
        AddBytes(0x00);
        AddBytes(0xFF);

        // Add Tempo
        AddBytes(0x51);
        AddBytes(0x03);
        AddBytes(tempo >> 16);
        AddBytes(tempo >>  8);
        AddBytes(tempo >>  0);
        AddBytes(0x00);

        insert(end(), data->begin(), data->end());
    }

    void Finish(){
        // Add File end
        AddBytes(0xFF);
        AddBytes(0x2F);
        AddBytes(0x00);

    }

};

int main()
{
    const char x = 99;

    const char notes[64] =
    {
        2,-1,2, 9,x, 7,x,6,4,1,x,x,
    };

    int octave = 0;

    MIDItrack* midiData = new MIDItrack;
    MIDIFile midiFile(midiData);

    midiData->changeSynth(1);

    midiData->KeyOn(40, 111);
    midiData->AddDelay(500);
    midiData->KeyOff(40, 32);

    midiData->KeyOn(70, 111);
    midiData->AddDelay(500);
    midiData->KeyOff(70, 32);

    midiData->KeyOn(40, 111);
    midiData->AddDelay(500);
    midiData->KeyOff(40, 32);

    midiData->KeyOn(70, 111);
    midiData->AddDelay(500);
    midiData->KeyOff(70, 32);

    midiData->KeyOn(40, 111);
    midiData->AddDelay(500);
    midiData->KeyOff(40, 32);

    midiData->KeyOn(59, 130);
    midiData->AddDelay(250);



    midiFile.Start();
    midiFile.Finish();

    FILE* fs = std::fopen("myMidiSound.mid", "wb");
    std::fwrite(&midiFile.at(0), 1, midiFile.size(), fs);
    std::fclose(fs);

    // Am anfang und am ende fehlt noch 00 
    // Außerdem wird die länge falsch ausgegeben
    // sonst sollte das soweit funktionieren

    return 0;
}