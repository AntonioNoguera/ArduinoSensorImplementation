#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>
#include <Adafruit_MLX90614.h>

// Definir pines para el sensor ultrasónico
#define TRIG 9
#define ECHO 10

// Definir pines y tipo de sensor DHT
#define DHTPIN 2
#define DHTTYPE DHT11  // Cambia a DHT22 si es necesario

// Inicializar sensores
DHT dht(DHTPIN, DHTTYPE);
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
LiquidCrystal_I2C lcd(0x27, 16, 2); // Dirección I2C 0x27, 16x2 caracteres

void setup() {
    Serial.begin(9600);

    // Configuración del sensor ultrasónico
    pinMode(TRIG, OUTPUT);
    pinMode(ECHO, INPUT);

    // Iniciar sensores
    dht.begin();
    mlx.begin();
    lcd.begin();
    lcd.backlight();
    
    lcd.setCursor(0, 0);
    lcd.print("Sensores OK");
    delay(2000);
}

void loop() {
    // 🔹 Leer distancia del sensor ultrasónico
    digitalWrite(TRIG, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG, LOW);
    long duration = pulseIn(ECHO, HIGH);
    float distance = duration * 0.034 / 2;  // Convertir a cm

    // 🔹 Leer temperatura y humedad del sensor DHT11/DHT22
    float humidity = dht.readHumidity();
    float tempDHT = dht.readTemperature();

    // 🔹 Leer temperatura del sensor infrarrojo MLX90614
    float tempObject = mlx.readObjectTempC();
    float tempAmbient = mlx.readAmbientTempC();

    // 🔹 Mostrar en LCD
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Temp: ");
    lcd.print(tempDHT);
    lcd.print("C");

    lcd.setCursor(0, 1);
    lcd.print("Dist: ");
    lcd.print(distance);
    lcd.print("cm");

    // 🔹 Mostrar en Monitor Serie
    Serial.print("Temp DHT: "); Serial.print(tempDHT); Serial.print(" C, ");
    Serial.print("Humedad: "); Serial.print(humidity); Serial.print(" %, ");
    Serial.print("Temp Obj: "); Serial.print(tempObject); Serial.print(" C, ");
    Serial.print("Temp Amb: "); Serial.print(tempAmbient); Serial.print(" C, ");
    Serial.print("Distancia: "); Serial.print(distance); Serial.println(" cm");

    delay(2000);
}