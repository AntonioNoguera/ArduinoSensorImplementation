#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// Dirección I2C del adaptador (0x27 o 0x3F dependiendo del módulo)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
    lcd.begin(); // Inicializa el LCD con I2C
    lcd.backlight(); // Enciende la luz de fondo

    lcd.setCursor(0, 0);
    lcd.print("Hola, Mundo!");

    lcd.setCursor(0, 1);
    lcd.print("LCD I2C con Arduino");
}

void loop() {
    // No hay lógica en el loop, ya que solo muestra un mensaje estático.
}
