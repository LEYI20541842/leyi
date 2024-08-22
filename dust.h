
#ifndef GP2Y1010AU0F_h
#define GP2Y1010AU0F_h
#include "Arduino.h" 
#define Excellent 0 
#define GOOD 1 
#define Fair 2 
#define Moderate 3 
#define POOR 4 
#define Hazardous 5 

class GP2Y1010AU0F{
	public:
		GP2Y1010AU0F(int ledPin, int outputPin);
		double getOutputV();
		double getDustDensity(double outputV);
		double getAQI(double ugm3);
		int getGradeInfo(double aqi);
	private:
		int _ledPin;
		int _outputPin;
};

#endif
