//
//  main.cpp
//  myWAVPlayer
//
//  Created by EdwardHeat on 12/2/18.
//  Copyright © 2018 HeatDev. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>


#define FILE_PATH "/Users/edwardheat/Desktop/funeral_theme.wav"

// audiodata structure

struct AudioData

{
    Uint8* pos;
    Uint32 length;
};

// AudioCallback function

void MyAudioCallback(void* userdata, Uint8* stream, int streamLength)

{
    AudioData* audio = (AudioData*) userdata;
    
    
    
    if (audio->length ==0)
        
    {
        return;
    }
    
    //amount of audiodata needed & copy to memory
    
    Uint32 length = (Uint32)streamLength;
    
    length = (length > audio->length ? audio->length : length);
    
    SDL_memcpy(stream, audio->pos, length);
    
    //update the audio
    
    audio->pos += length;
    audio->length -= length;
}


int main(int argc, char** argv)

{
    
    SDL_Init(SDL_INIT_AUDIO);
    
    SDL_AudioSpec wavSpec;
    Uint8* wavStart;
    Uint32 wavLength;
    
    
    if(SDL_LoadWAV(FILE_PATH, &wavSpec, &wavStart, &wavLength) == NULL)
        
    {
        std::cerr << "Error!"<< FILE_PATH << "COULD NOT BE LOADED!!!" << SDL_GetError()<< std::endl;
        return 1;
    }
    
    //call the audio function
    
    AudioData audio;
    audio.pos = wavStart;
    audio.length = wavLength;
    
    wavSpec.callback = MyAudioCallback;
    wavSpec.userdata = &audio;
    
    SDL_AudioDeviceID device = SDL_OpenAudioDevice(NULL, 0, &wavSpec, NULL, SDL_AUDIO_ALLOW_ANY_CHANGE );
    
    if (device == 0)
        
    {
        
        std::cerr << "Error!"<< SDL_GetError() << std::endl;
        return 1;
    }
    
    // play function
    
    SDL_PauseAudioDevice(device, 0);
    
    while(audio.length > 0)
        
    {
        SDL_Delay(100);
    }
    
    SDL_CloseAudioDevice(device);
    SDL_FreeWAV(wavStart);
    
    
    SDL_Quit();
    
    return 0;
    
    
}
