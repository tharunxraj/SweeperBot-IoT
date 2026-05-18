/*
 * ============================================================
 *  SweeperBot-IoT — Autonomous Floor Cleaning Robot
 * ============================================================
 *  Hardware:
 *    - Arduino Nano (Main Controller)
 *    - NodeMCU ESP8266 (WiFi Module)
 *    - L298D Motor Driver
 *    - Ultrasonic Sensor HC-SR04 (Obstacle Detection)
 *    - Two Channel Relay Module (Clean Motor + Pump Motor)
 *    - DC Gear Motors 100rpm x6 (Wheel Drive)
 *    - Cleaning Motor 10rpm x2
 *    - Pump Motor (Water Pump)
 *    - LM2596 Step-Down Converter (12V to 5V)
 *    - 12V 1.3A Battery
 *
 *  Modes:
 *    - AUTO MODE  : MainSW = HIGH → Robot navigates autonomously
 *    - MANUAL MODE: MainSW = LOW  → WiFi control via MIT App Inventor
 *
 *  WiFi Commands (Manual Mode):
 *    f   = Forward
 *    b   = Backward
 *    l   = Left
 *    r   = Right
 *    s   = Stop
 *    con = Clean Motor ON
 *    coff= Clean Motor OFF
 *    pon = Pump Motor ON
 *    poff= Pump Motor OFF
 *
 *  Obstacle Detection:
 *    Stops robot if obstacle detected within 10 cm
 * ============================================================
 */

#include <SoftwareSerial.h>

SoftwareSerial ESP8266(0, 1); // TX, RX respectively
String readvoice;

// ── MOTOR 1 PINS ──────────────────────────────────────────
int motor1Pin1 = 6;
int motor1Pin2 = 7;

// ── MOTOR 2 PINS ──────────────────────────────────────────
int motor2Pin1 = 8;
int motor2Pin2 = 9;

int ENA = 5;
int ENB = 10;

int speedval = 220; // Motor speed (0-255)

// ── ULTRASONIC SENSOR PINS ────────────────────────────────
int trig = A4;
int echo = A5;
long duration, inches, cm;

// ── RELAY CONTROLLED MOTORS ───────────────────────────────
#define cleanmotor A0
#define pumpmotor  A1

// ── MODE SWITCH ───────────────────────────────────────────
#define MainSW 3  // LOW = Manual (WiFi), HIGH = Auto

// ═════════════════════════════════════════════════════════
void setup()
{
  Serial.begin(9600);
  ESP8266.begin(9600);

  // Mode switch with internal pull-up
  pinMode(MainSW, INPUT_PULLUP);

  // Motor pins
  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(motor2Pin1, OUTPUT);
  pinMode(motor2Pin2, OUTPUT);

  // Enable pins with speed
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  analogWrite(ENA, speedval);
  analogWrite(ENB, speedval);

  // Ultrasonic sensor
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);

  // Relay-controlled motors (HIGH = OFF for active-low relay)
  pinMode(cleanmotor, OUTPUT);
  pinMode(pumpmotor,  OUTPUT);
  digitalWrite(cleanmotor, HIGH);
  digitalWrite(pumpmotor,  HIGH);
}

// ═════════════════════════════════════════════════════════
void loop()
{
  // ── MANUAL MODE (WiFi Control via ESP8266) ─────────────
  if (digitalRead(MainSW) == LOW)
  {
    // Read incoming WiFi command from NodeMCU
    while (ESP8266.available()) {
      delay(10);
      char c = ESP8266.read();
      readvoice += c;
    }

    if (readvoice.length() > 0) {
      Serial.print(readvoice);

      // ── FORWARD ────────────────────────────────────────
      if (readvoice == "f")
      {
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        delay(1000);

        // Check for obstacle after moving
        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        duration = pulseIn(echo, HIGH);
        inches = duration / 74 / 2;
        cm     = duration / 29 / 2;

        if (cm <= 10)
        {
          Serial.println("Obstacle Detected - Stop Robot");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          delay(300);
        }
      }

      // ── BACKWARD ───────────────────────────────────────
      else if (readvoice == "b")
      {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        delay(1000);

        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        duration = pulseIn(echo, HIGH);
        inches = duration / 74 / 2;
        cm     = duration / 29 / 2;

        if (cm <= 10)
        {
          Serial.println("Obstacle Detected - Stop Robot");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          delay(300);
        }
      }

      // ── LEFT ───────────────────────────────────────────
      else if (readvoice == "l")
      {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, HIGH);
        digitalWrite(motor2Pin1, HIGH);
        digitalWrite(motor2Pin2, LOW);
        delay(1000);

        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        duration = pulseIn(echo, HIGH);
        inches = duration / 74 / 2;
        cm     = duration / 29 / 2;

        if (cm <= 10)
        {
          Serial.println("Obstacle Detected - Stop Robot");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          delay(300);
        }
      }

      // ── RIGHT ──────────────────────────────────────────
      else if (readvoice == "r")
      {
        digitalWrite(motor1Pin1, HIGH);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, HIGH);
        delay(1000);

        digitalWrite(trig, LOW);
        delayMicroseconds(2);
        digitalWrite(trig, HIGH);
        delayMicroseconds(5);
        digitalWrite(trig, LOW);

        duration = pulseIn(echo, HIGH);
        inches = duration / 74 / 2;
        cm     = duration / 29 / 2;

        if (cm <= 10)
        {
          Serial.println("Obstacle Detected - Stop Robot");
          digitalWrite(motor1Pin1, LOW);
          digitalWrite(motor1Pin2, LOW);
          digitalWrite(motor2Pin1, LOW);
          digitalWrite(motor2Pin2, LOW);
          delay(300);
        }
      }

      // ── STOP ───────────────────────────────────────────
      else if (readvoice == "s")
      {
        digitalWrite(motor1Pin1, LOW);
        digitalWrite(motor1Pin2, LOW);
        digitalWrite(motor2Pin1, LOW);
        digitalWrite(motor2Pin2, LOW);
        delay(300);
      }

      // ── CLEAN MOTOR ON ─────────────────────────────────
      else if (readvoice == "con")
      {
        digitalWrite(cleanmotor, LOW);
        delay(100);
      }

      // ── CLEAN MOTOR OFF ────────────────────────────────
      else if (readvoice == "coff")
      {
        digitalWrite(cleanmotor, HIGH);
        delay(100);
      }

      // ── PUMP MOTOR ON ──────────────────────────────────
      else if (readvoice == "pon")
      {
        digitalWrite(pumpmotor, LOW);
        delay(100);
      }

      // ── PUMP MOTOR OFF ─────────────────────────────────
      else if (readvoice == "poff")
      {
        digitalWrite(pumpmotor, HIGH);
        delay(100);
      }

      else
      {
        Serial.println("Wrong Input");
      }

      readvoice = ""; // Reset command string
    }
  }

  // ── AUTO MODE (Autonomous Navigation) ──────────────────
  else if (digitalRead(MainSW) == HIGH)
  {
    delay(200);

    // Measure distance with ultrasonic sensor
    digitalWrite(trig, LOW);
    delayMicroseconds(2);
    digitalWrite(trig, HIGH);
    delayMicroseconds(5);
    digitalWrite(trig, LOW);

    duration = pulseIn(echo, HIGH);
    inches = duration / 74 / 2;
    cm     = duration / 29 / 2;
    delay(100);

    // Obstacle within 10cm → Turn left to avoid
    if (cm <= 10)
    {
      digitalWrite(motor1Pin1, LOW);
      digitalWrite(motor1Pin2, HIGH);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(300);
    }
    // Path clear → Move forward
    else
    {
      digitalWrite(motor1Pin1, HIGH);
      digitalWrite(motor1Pin2, LOW);
      digitalWrite(motor2Pin1, HIGH);
      digitalWrite(motor2Pin2, LOW);
      delay(300);
    }

    delay(200);
  }
}
