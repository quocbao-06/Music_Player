#include <LiquidCrystal.h>

// LCD object
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

// Pins
const int conver_pin = 8;
const int play_pin = 9;

const int speaker_pin = 13;

// State
int pre_song = 1;  // 1 -> Twinkle Twinkle Little Star
				   // 2 -> Happy birthday

int pre_conver = HIGH;
int pre_play = HIGH;

// Twinkle Twinkle Little Star
const int song_length1 = 14;
int song_freqs1[] = {262, 262, 392, 392, 440, 440, 392, 
                      349, 349, 329, 329, 294, 294, 262};
int song_beats1[] = {1,   1,   1,   1,   1,   1,   2,
                      1,   1,   1,   1,   1,   1,   2};

// Happy Birthday
const int song_length2 = 12;
int song_freqs2[] = {
    262, 262, 294, 262, 349, 330,   
    262, 262, 294, 262, 392, 349    
};
int song_beats2[] = {
    1, 1, 2, 2, 2, 4,   
    1, 1, 2, 2, 2, 4  
};

int song_tempo = 300;

void setup()
{
  pinMode(conver_pin, INPUT_PULLUP);
  pinMode(play_pin, INPUT_PULLUP);
  pinMode(speaker_pin, OUTPUT);
  
  // Initialize and clear LCD 
  lcd.begin(16, 2);
  lcd.clear();
  
  lcd.setCursor(0, 0);
  lcd.print("Twinkle Twinkle");
}

void loop()
{
  // Thực hiện chức năng chuyển đổi bài hát trên màn hình LCD
  int reading_conver = digitalRead(conver_pin);
  if(pre_conver == HIGH && reading_conver == LOW)
  {
    if(pre_song == 1)
    {
      pre_song = 2;
      lcd.clear();
      lcd.setCursor(0, 0);
  	  lcd.print("Happy Birthday");
    }
    else {
      pre_song = 1;
      lcd.clear();
      lcd.setCursor(0, 0);
  	  lcd.print("Twinkle Twinkle");
    }
  }
  pre_conver = reading_conver;
  
  // Thực hiện chức năng phát đoạn đầu của bài hát
  int reading_play = digitalRead(play_pin);
  if(pre_play == HIGH && reading_play == LOW)
  {
    play_music();
  }
  pre_play = reading_play;
}

void play_music()
{
  if(pre_song == 1) // CHoi bai Twinkle Twinkle
  {
    for(int i=0; i < song_length1; i++)
    {
      int duration = song_tempo * song_beats1[i];
      tone(speaker_pin, song_freqs1[i], duration);
      delay(duration + 10);
    }
  }
  else { // Choi bai Happy Birthday
    for(int i=0; i < song_length2; i++)
    {
      int duration = song_tempo * song_beats2[i];
      tone(speaker_pin, song_freqs2[i], duration);
      delay(duration);
    }
  }
}









