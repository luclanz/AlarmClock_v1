void sdAndSpeaker_setup() {

    music.speakerPin = LM_IN;
    if (!SD.begin(SD_CS)) {
    Serial.println("SD fail");
    Serial.flush();
    abort();
    //return;
    }
    
}

void sdAndSpeaker_startMusicAlarm() {
  music.setVolume(4);
  music.loop(1);
  music.play("Daybreak.wav");
  music.quality(2);
}

void sdAndSpeaker_startMusicTimer() {
  music.setVolume(4);
  music.loop(1);
  music.play("Timer.wav");
  music.quality(2);
}

void sdAndSpeaker_stopMusic() {
  music.disable();
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
