const int trigPin = 9;   // Pin de disparo del sensor
const int echoPin = 10;  // Pin de recepción del eco

void setup() {
    Serial.begin(9600); // Inicializa comunicación serial
    pinMode(trigPin, OUTPUT);
    pinMode(echoPin, INPUT);
}

void loop() {
    long duration;
    float distance;

    // Genera un pulso de 10µs en el pin TRIG
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    // Lee el tiempo que tarda en recibir el eco
    duration = pulseIn(echoPin, HIGH);

    // Calcula la distancia en cm (velocidad del sonido: 343 m/s o 0.0343 cm/µs)
    distance = (duration * 0.0343) / 2;

    Serial.print("Distancia: ");
    Serial.print(distance);
    Serial.println(" cm");

    delay(500); // Pequeño retardo antes de la siguiente lectura
}
