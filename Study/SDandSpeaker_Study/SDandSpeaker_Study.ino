  // SD MODULE
    #define SD_CS 4
    #define SD_SCK 13
    #define SD_MOSI 11
    #define SD_MISO 12
  // LM386
    #define LM_IN 9
    

#include "SD.h"
#define SD_ChipSelectPin 4
#include "TMRpcm.h"
//#include "SPI.h"

TMRpcm tmrpcm;

void setup(){
tmrpcm.speakerPin = 9;
Serial.begin(9600);
if (!SD.begin(SD_ChipSelectPin)) {
Serial.println("SD fail");
return;
}

tmrpcm.setVolume(4);
tmrpcm.play("Daybreak.wav");
tmrpcm.quality(2);
}

/*
  TMRpcm audio;
  audio.play("filename");    plays a file
  audio.play("filename",30); plays a file starting at 30 seconds into the track
  audio.speakerPin = 11;     set to 5,6,11 or 46 for Mega, 9 for Uno, Nano, etc.
  audio.disable();           disables the timer on output pin and stops the music
  audio.stopPlayback();      stops the music, but leaves the timer running
  audio.isPlaying();         returns 1 if music playing, 0 if not
  audio.pause();             pauses/unpauses playback
  audio.quality(1);          Set 1 for 2x oversampling
  audio.volume(0);           1(up) or 0(down) to control volume
  audio.setVolume(0);        0 to 7. Set volume level
  audio.loop(1);             0 or 1. Can be changed during playback for full control of looping.
*/

void loop(){ 

//Serial.println("hi");   //I can do stuff while music is playing
//delay(1000);
  
}
