#include <DHT.h>

// Definir el pin donde está conectado el sensor
#define DHTPIN 2       // Cambia este número si usas otro pin
#define DHTTYPE DHT11  // Cambia a DHT22 si usas ese modelo

// Crear objeto DHT
DHT dht(DHTPIN, DHTTYPE);

void setup() {
    Serial.begin(9600);
    Serial.println("Iniciando sensor DHT...");
    dht.begin();  // Iniciar el sensor
}

void loop() {
    // Esperar 2 segundos entre lecturas
    delay(2000);

    // Leer la humedad y temperatura
    float humedad = dht.readHumidity();
    float temperatura = dht.readTemperature(); // Celsius
    float tempF = dht.readTemperature(true);  // Fahrenheit

    // Verificar si la lectura fue correcta
    if (isnan(humedad) || isnan(temperatura)) {
        Serial.println("Error al leer del sensor DHT!");
        return;
    }

    // Mostrar datos en el Monitor Serial
    Serial.print("Humedad: ");
    Serial.print(humedad);
    Serial.print("%  Temperatura: ");
    Serial.print(temperatura);
    Serial.print("°C / ");
    Serial.print(tempF);
    Serial.println("°F");
}