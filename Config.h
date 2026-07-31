#ifndef CONFIG_H
#define CONFIG_H

// -----------------------------------------------------
// Smart Traffic Management System
// Target Board : Arduino Mega 2560
// -----------------------------------------------------

// -----------------------------
// Lane Configuration
// -----------------------------

constexpr int LANE_COUNT = 4;

// -----------------------------
// IR Sensor Pins
// (2 Sensors Per Lane)
// -----------------------------

const int irPins[LANE_COUNT][2] =
{
    {2, 3},      // Lane 1
    {4, 5},      // Lane 2
    {6, 7},      // Lane 3
    {8, 9}       // Lane 4
};

// -----------------------------
// Traffic Light Pins
// {Red, Yellow, Green}
// -----------------------------

const int trafficLightPins[LANE_COUNT][3] =
{
    {22, 23, 24},    // Lane 1
    {25, 26, 27},    // Lane 2
    {28, 29, 30},    // Lane 3
    {31, 32, 33}     // Lane 4
};

// -----------------------------
// Signal Timing Configuration
// -----------------------------

constexpr unsigned long yellowTime = 2000;             // 2 seconds
constexpr unsigned long minGreenTime = 5000;           // 5 seconds
constexpr unsigned long maxGreenTime = 15000;          // 15 seconds
constexpr unsigned long greenTimePerSensor = 2000;     // 2 seconds per active IR sensor

#endif