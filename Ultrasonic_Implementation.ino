#define TRIG_PIN 9  // Pin de trigger del sensor
#define ECHO_PIN 10 // Pin de echo del sensor
#define LED_PIN 7   // LED indicador
#define BUZZER_PIN 6 // Buzzer de alerta
#define DISTANCE_THRESHOLD 30 // Distancia mínima en cm para activar la alerta

void setup() {
    pinMode(TRIG_PIN, OUTPUT);
    pinMode(ECHO_PIN, INPUT);
    pinMode(LED_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    Serial.begin(9600);
}

void loop() {
    long duration;
    int distance;

    // Enviar pulso ultrasónico
    digitalWrite(TRIG_PIN, LOW);
    delayMicroseconds(2);
    digitalWrite(TRIG_PIN, HIGH);
    delayMicroseconds(10);
    digitalWrite(TRIG_PIN, LOW);

    // Leer el tiempo de respuesta del eco
    duration = pulseIn(ECHO_PIN, HIGH);
    distance = duration * 0.034 / 2; // Convertir el tiempo en distancia (cm)

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    if (distance > 0 && distance < DISTANCE_THRESHOLD) {
        digitalWrite(LED_PIN, HIGH);
        tone(BUZZER_PIN, 1000); // Emitir sonido de alerta
    } else {
        digitalWrite(LED_PIN, LOW);
        noTone(BUZZER_PIN);
    }

    delay(500); // Pequeño retraso para estabilidad
}
