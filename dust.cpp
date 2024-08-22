#include "GP2Y1010AU0F.h"
#include "Arduino.h" 

const int DELAY_BEFORE_SAMPLING = 280; 
const int DELAY_AFTER_SAMPLING = 40; 
const int DELAY_LED_OFF = 9680; 

int _ledPin;
int _outputPin;
GP2Y1010AU0F::GP2Y1010AU0F(int ledPin, int outputPin){
	pinMode(ledPin, OUTPUT);
	pinMode(outputPin, INPUT);
	_ledPin = ledPin;
	_outputPin = outputPin;
}

double GP2Y1010AU0F::getOutputV() {
  digitalWrite(_ledPin, LOW);
  delayMicroseconds(DELAY_BEFORE_SAMPLING);
  double analogOutput = analogRead(_outputPin);
  delayMicroseconds(DELAY_AFTER_SAMPLING);
  digitalWrite(_ledPin, HIGH);
  delayMicroseconds(DELAY_LED_OFF);
  double outputV = analogOutput / 4095 * 3.3;
  return outputV;
}


double GP2Y1010AU0F::getDustDensity(double outputV) {
  if(outputV < 0.6){
  	outputV = 0.6;
  }else if(outputV > 3.5){
  	outputV = 3.5;
  }
double ugm3 = (outputV - 0.6) / 3.3 * 1000;
    
  if (ugm3 < 0) {
    ugm3 = 0;
  }
  return ugm3;
}

double GP2Y1010AU0F::getAQI(double ugm3) {
  double aqiL = 0;
  double aqiH = 0;
  double bpL = 0;
  double bpH = 0;
  double aqi = 0;
  if (ugm3 >= 0 && ugm3 <= 35) {
    aqiL = 0;
    aqiH = 50;
    bpL = 0;
    bpH = 35;
  } else if (ugm3 > 35 && ugm3 <= 75) {
    aqiL = 50;
    aqiH = 100;
    bpL = 35;
    bpH = 75;
  } else if (ugm3 > 75 && ugm3 <= 115) {
    aqiL = 100;
    aqiH = 150;
    bpL = 75;
    bpH = 115;
  } else if (ugm3 > 115 && ugm3 <= 150) {
    aqiL = 150;
    aqiH = 200;
    bpL = 115;
    bpH = 150;
  } else if (ugm3 > 150 && ugm3 <= 250) {
    aqiL = 200;
    aqiH = 300;
    bpL = 150;
    bpH = 250;
  } else if (ugm3 > 250 && ugm3 <= 350) {
    aqiL = 300;
    aqiH = 400;
    bpL = 250;
    bpH = 350;
  } else if (ugm3 > 350) {
    aqiL = 400;
    aqiH = 500;
    bpL = 350;
    bpH = 500;
  }
  aqi = (aqiH - aqiL) / (bpH - bpL) * (ugm3 - bpL) + aqiL;
  return aqi;
}

int GP2Y1010AU0F::getGradeInfo(double aqi) {
  int gradeInfo;
  if (aqi >= 0 && aqi <= 50) {
    gradeInfo = Excellent;
  } else if (aqi > 50 && aqi <= 100) {
    gradeInfo = GOOD;
  } else if (aqi > 100 && aqi <= 150) {
    gradeInfo = Fair;
  } else if (aqi > 150 && aqi <= 200) {
    gradeInfo = Moderate;
  } else if (aqi > 200 && aqi <= 300) {
    gradeInfo = POOR;
  } else if (aqi > 300 ) {
    gradeInfo = Hazardous;
  }
  return gradeInfo;
}
