#include <Wire.h>
#include <Adafruit_MLX90614.h>

Adafruit_MLX90614 mlx = Adafruit_MLX90614();

void setup() {
    Serial.begin(9600); // Inicia la comunicación serial
    Serial.println("Inicializando sensor MLX90614...");
    
    if (!mlx.begin()) {
        Serial.println("Error al detectar MLX90614. Verifica las conexiones.");
        while (1);
    }
    
    Serial.println("Sensor listo.");
}

void loop() {
    float ambientTemp = mlx.readAmbientTempC(); // Temperatura ambiente
    float objectTemp = mlx.readObjectTempC();   // Temperatura del objeto
    
    Serial.print("Temperatura Ambiente: ");
    Serial.print(ambientTemp);
    Serial.println(" °C");

    Serial.print("Temperatura del Objeto: ");
    Serial.print(objectTemp);
    Serial.println(" °C");
    
    Serial.println("----------------------------");
    delay(1000); // Espera 1 segundo antes de la siguiente lectura
}
