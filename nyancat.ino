#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
#define OLED_RESET     4 // Reset pin # (or -1 if sharing Arduino reset pin)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);
void setup() {

  // put your setup code here, to run once:
  Serial.begin(9600);
  // SSD1306_SWITCHCAPVCC = generate display voltage from 3.3V internally
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  pinMode(8, OUTPUT);
}


static const unsigned char PROGMEM nyan_cat1 [] = {
  

 
};

static const unsigned char PROGMEM nyan_cat2 [] = {
 
};

static const unsigned char PROGMEM nyan_cat3 [] = {
  
};
#include "pitches.h"

// notes in the melody:
static const PROGMEM uint16_t melody[] = {
 
};

// note durations: 4 = quarter note, 8 = eighth note, etc.:
static const PROGMEM uint16_t noteDurations[] = {
 


};
int frame = 1;
int thisNote = 0;
void loop() {
  // iterate over the notes of the melody:
  if (frame == 1) {
    display.clearDisplay();
    display.drawBitmap(0, 0, nyan_cat1, 128, 64, WHITE);
    display.display();
  }
  if (frame == 2) {
    display.clearDisplay();
    display.drawBitmap(0, 0, nyan_cat2, 128, 64, WHITE);
    display.display();
  }
  if (frame == 3) {
    display.clearDisplay();
    display.drawBitmap(0, 0, nyan_cat3, 128, 64, WHITE);
    display.display();
  }
  /*
    to calculate the note duration, take one second divided by the note type.
    e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
  */
  if (thisNote < 459) {
    int note = pgm_read_word_near(melody + thisNote);
    int noteDuration = 1000 / pgm_read_word_near(noteDurations + thisNote);
    tone(8, note , noteDuration);
    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.30;
    delay(pauseBetweenNotes);
    // stop the tone playing:
    noTone(8);
    thisNote++;
  }
  else {
    thisNote = 0;
  }
  if (frame < 3) {
    frame++;
  }
  else {
    frame = 1;
  }
  digitalWrite(8, LOW);
}
