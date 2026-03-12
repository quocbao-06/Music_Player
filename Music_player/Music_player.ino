#include <LiquidCrystal.h>

// ================= LCD =================
LiquidCrystal lcd(12, 11, 2, 3, 4, 5);

// ================= PIN =================
const int PIN_SWITCH = 8;
const int PIN_PLAY   = 9;
const int PIN_SPEAKER = 13;

// ================= SYSTEM STATE =================
int currentSong = 1;

int prevSwitchState = HIGH;
int prevPlayState   = HIGH;

const int TEMPO = 300;

// ================= SONG DATA =================

// Twinkle Twinkle Little Star
const int SONG1_LENGTH = 14;

int song1_freq[] = {
262,262,392,392,440,440,392,
349,349,329,329,294,294,262
};

int song1_beats[] = {
1,1,1,1,1,1,2,
1,1,1,1,1,1,2
};

// Happy Birthday
const int SONG2_LENGTH = 12;

int song2_freq[] = {
262,262,294,262,349,330,
262,262,294,262,392,349
};

int song2_beats[] = {
1,1,2,2,2,4,
1,1,2,2,2,4
};

// ================= LCD FUNCTION =================
void displaySong()
{
  lcd.clear();
  lcd.setCursor(0,0);

  if(currentSong == 1)
    lcd.print("Twinkle Twinkle");
  else
    lcd.print("Happy Birthday");
}

// ================= PLAY MUSIC FUNCTION =================
void playSong(int freq[], int beats[], int length)
{
  for(int i = 0; i < length; i++)
  {
    int duration = TEMPO * beats[i];

    tone(PIN_SPEAKER, freq[i], duration);
    delay(duration + 10);
  }
}

// ================= SETUP =================
void setup()
{
  pinMode(PIN_SWITCH, INPUT_PULLUP);
  pinMode(PIN_PLAY, INPUT_PULLUP);
  pinMode(PIN_SPEAKER, OUTPUT);

  lcd.begin(16,2);
  displaySong();
}

// ================= LOOP =================
void loop()
{
  // --------- Switch Song ----------
  int switchReading = digitalRead(PIN_SWITCH);

  if(prevSwitchState == HIGH && switchReading == LOW)
  {
    currentSong = (currentSong == 1) ? 2 : 1;
    displaySong();
  }

  prevSwitchState = switchReading;


  // --------- Play Song ----------
  int playReading = digitalRead(PIN_PLAY);

  if(prevPlayState == HIGH && playReading == LOW)
  {
    if(currentSong == 1)
      playSong(song1_freq, song1_beats, SONG1_LENGTH);
    else
      playSong(song2_freq, song2_beats, SONG2_LENGTH);
  }

  prevPlayState = playReading;
}