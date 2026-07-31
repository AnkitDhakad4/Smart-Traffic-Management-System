#ifndef TRAFFIC_CONTROLLER_H
#define TRAFFIC_CONTROLLER_H

#include <Arduino.h>
#include "Config.h"
Thanks thanks
int laneDensity[LANE_COUNT];

// -----------------------------------------------------
// Turn every signal RED
// -----------------------------------------------------
void setAllRed()
{
    for (int lane = 0; lane < LANE_COUNT; lane++)
    {
        digitalWrite(trafficLightPins[lane][0], HIGH);
        digitalWrite(trafficLightPins[lane][1], LOW);
        digitalWrite(trafficLightPins[lane][2], LOW);
    }
}

// -----------------------------------------------------
// Initialize all sensors and traffic light pins
// -----------------------------------------------------
void initializeTrafficSystem()
{
    for (int lane = 0; lane < LANE_COUNT; lane++)
    {
        pinMode(irPins[lane][0], INPUT);
        pinMode(irPins[lane][1], INPUT);

        pinMode(trafficLightPins[lane][0], OUTPUT);
        pinMode(trafficLightPins[lane][1], OUTPUT);
        pinMode(trafficLightPins[lane][2], OUTPUT);
    }

    setAllRed();
}

// -----------------------------------------------------
// Read density of one lane
// -----------------------------------------------------
int getLaneDensity(int lane)
{
    int density = 0;

    if (digitalRead(irPins[lane][0]) == LOW)
        density++;

    if (digitalRead(irPins[lane][1]) == LOW)
        density++;

    return density;
}

// -----------------------------------------------------
// Read all lanes
// -----------------------------------------------------
void updateDensity()
{
    for (int lane = 0; lane < LANE_COUNT; lane++)
    {
        laneDensity[lane] = getLaneDensity(lane);
    }
}

// -----------------------------------------------------
// Select lane with highest density
// -----------------------------------------------------
int getHighestPriorityLane()
{
    int selectedLane = 0;

    for (int lane = 1; lane < LANE_COUNT; lane++)
    {
        if (laneDensity[lane] > laneDensity[selectedLane])
        {
            selectedLane = lane;
        }
    }

    return selectedLane;
}

// -----------------------------------------------------
// Green Time Calculation
// -----------------------------------------------------
unsigned long calculateGreenTime(int density)
{
    unsigned long greenTime = minGreenTime + (density * greenTimePerSensor);

    if (greenTime > maxGreenTime)
        greenTime = maxGreenTime;

    return greenTime;
}

// -----------------------------------------------------
// Turn one lane GREEN
// -----------------------------------------------------
void activateGreen(int lane)
{
    setAllRed();

    digitalWrite(trafficLightPins[lane][0], LOW);
    digitalWrite(trafficLightPins[lane][2], HIGH);
}

// -----------------------------------------------------
// Turn GREEN -> YELLOW
// -----------------------------------------------------
void activateYellow(int lane)
{
    digitalWrite(trafficLightPins[lane][2], LOW);
    digitalWrite(trafficLightPins[lane][1], HIGH);
}

// -----------------------------------------------------
// Turn YELLOW -> RED
// -----------------------------------------------------
void activateRed(int lane)
{
    digitalWrite(trafficLightPins[lane][1], LOW);
    digitalWrite(trafficLightPins[lane][0], HIGH);
}

// -----------------------------------------------------
// Run one complete signal cycle
// -----------------------------------------------------
void processTraffic()
{
    updateDensity();

    int selectedLane = getHighestPriorityLane();

    unsigned long greenTime = calculateGreenTime(laneDensity[selectedLane]);

    activateGreen(selectedLane);
    delay(greenTime);

    activateYellow(selectedLane);
    delay(yellowTime);

    activateRed(selectedLane);
}

#endif