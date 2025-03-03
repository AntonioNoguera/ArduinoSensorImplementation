#include <Wire.h>
#include <Adafruit_MLX90614.h>

#define TRIG 9
#define ECHO 10


Adafruit_MLX90614 mlx = Adafruit_MLX90614();


void setup() {
    Serial.begin(9600);
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    mlx.begin();
}

void loop() {
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);

    long duration = pulseIn(ECHO, HIGH);
    float distance = duration * 0.034 / 2; // Conversión a cm
    
    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    Serial.print("Temperatura del objeto: ");
    Serial.print(mlx.readObjectTempC());
    Serial.println(" °C");

    Serial.print("Temperatura ambiente: ");
    Serial.print(mlx.readAmbientTempC());
    Serial.println(" °C");
    delay(500);
}