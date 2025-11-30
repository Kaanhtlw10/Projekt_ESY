/*
  * File: Rückwertszähler.cpp
  * Autor: Kaan Akti
  * Datum: 01.12.2025
  * 
  * Beschreibung: Ein Rückwertszähler angezeigt auf einer 7-Segment-Anzeige, Rückwertszählen durch Licht mithifle einer LDR
*/

#include<Arduino.h>
#include<Servo.h>

const int segmente[] = {2, 11, 4, 5, 6, 7, 8, 13};
//                      E  D   C  DP B  A  F  G
//                      0  1   2  3  4  5  6  7
const int ldr = A0;
const int led = 9;
const int buzzer = 12;

unsigned long jetztigeZeit = 0;
unsigned long vorherigeZeit1000 = 0;
unsigned long verzoegerung1000 = 1000; // Verzögerung von Segment 9 bis Segment 0
int segmentSchritte = 0;
Servo servo;

void segment1() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], HIGH);
  digitalWrite(segmente[1], LOW);
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], LOW);
  digitalWrite(segmente[6], LOW);
  digitalWrite(segmente[7], LOW);
  digitalWrite(segmente[0], LOW);
}

void segment2() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], LOW);
  digitalWrite(segmente[1], HIGH);
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH);
  digitalWrite(segmente[6], LOW);
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], HIGH);
}

void segment3() {
  digitalWrite(segmente[4], HIGH); 
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], LOW);
  digitalWrite(segmente[7], HIGH); 
  digitalWrite(segmente[0], LOW);
}

void segment4() {
  digitalWrite(segmente[4], HIGH); 
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], LOW);
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], LOW);
  digitalWrite(segmente[6], HIGH);
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], LOW);
}

void segment5() {
  digitalWrite(segmente[4], LOW);
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], HIGH); 
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], LOW);
}

void segment6() {
  digitalWrite(segmente[4], LOW);
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], HIGH); 
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], HIGH);
}

void segment7() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], HIGH);
  digitalWrite(segmente[1], LOW);
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH);
  digitalWrite(segmente[6], LOW);
  digitalWrite(segmente[7], LOW);
  digitalWrite(segmente[0], LOW); 
}

void segment8() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], HIGH); 
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], HIGH);
}

void segment9() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], HIGH); 
  digitalWrite(segmente[7], HIGH);
  digitalWrite(segmente[0], LOW);
}

void segment0() {
  digitalWrite(segmente[4], HIGH);
  digitalWrite(segmente[2], HIGH); 
  digitalWrite(segmente[1], HIGH); 
  digitalWrite(segmente[3], LOW);
  digitalWrite(segmente[5], HIGH); 
  digitalWrite(segmente[6], HIGH); 
  digitalWrite(segmente[7], LOW);
  digitalWrite(segmente[0], HIGH); 
}

void segmentDP() {
  digitalWrite(segmente[4], LOW);
  digitalWrite(segmente[2], LOW);
  digitalWrite(segmente[1], LOW);
  digitalWrite(segmente[3], HIGH);
  digitalWrite(segmente[5], LOW);
  digitalWrite(segmente[6], LOW);
  digitalWrite(segmente[7], LOW);
  digitalWrite(segmente[0], LOW);
}

void setup() {
  for(int i = 0; i < 8; i++) {
    pinMode(segmente[i], OUTPUT);
  }
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  servo.attach(10);
}

void loop() {
  jetztigeZeit = millis();
  if(jetztigeZeit - vorherigeZeit1000 >= verzoegerung1000) {
    vorherigeZeit1000 = jetztigeZeit;

    int widerstand_ldr = analogRead(ldr);
    int mappedWertLdr = map(widerstand_ldr, 0, 1023, 0, 100);
    Serial.println(mappedWertLdr);

    if(mappedWertLdr >= 10) {
      switch(segmentSchritte) {
        case 0:
        segment9();
        break;

        case 1: 
        segment8();
        break;

        case 2:
        segment7();
        break;

        case 3:
        segment6();
        break;

        case 4:
        segment5();
        break;

        case 5:
        segment4();
        break;

        case 6:
        segment3();
        break;

        case 7:
        segment2();
        break;

        case 8:
        segment1();
        break;

        case 9:
        segment0();
        break;
      }
      if(segmentSchritte > 9) {
        digitalWrite(led, HIGH);
        tone(buzzer, 100); 
        servo.write(180); 
      }
      if(segmentSchritte < 10) {
        segmentSchritte++;
        digitalWrite(led, HIGH);
        tone(buzzer, 3000);
        delay(200);
        digitalWrite(led, LOW);
        noTone(buzzer);
        delay(200);
      }
    } else {
      for(int i = 0; i < 8; i++) {
        digitalWrite(segmente[i], LOW);
        segmentSchritte = 0;
        digitalWrite(led, LOW);
        noTone(buzzer);
        servo.write(0);
      }
    }
  }
}