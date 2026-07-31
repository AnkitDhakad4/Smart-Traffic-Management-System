#include "Config.h"
#include "TrafficController.h"

void setup()
{
    Serial.begin(9600);

    initializeTrafficSystem();

    Serial.println("--------------------------------");
    Serial.println(" Smart Traffic Management System ");
    Serial.println("--------------------------------");
}

void loop()
{
    processTraffic();

    Serial.print("Lane 1 Density : ");
    Serial.println(laneDensity[0]);

    Serial.print("Lane 2 Density : ");
    Serial.println(laneDensity[1]);

    Serial.print("Lane 3 Density : ");
    Serial.println(laneDensity[2]);

    Serial.print("Lane 4 Density : ");
    Serial.println(laneDensity[3]);

    Serial.println("-------------------------------");

    delay(500);
}