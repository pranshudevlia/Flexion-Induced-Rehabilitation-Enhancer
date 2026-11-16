/*
 * Dual SMA Actuator Control with Flex Sensor + Dynamic Threshold Update
 * ---------------------------------------------------------------------
 * - SMA1 activates when flex increases (bend forward)
 * - SMA2 activates when flex decreases (relax backward)
 * - After each full bend → relax cycle, bending threshold reduces by 10
 * - Cooling timer ensures SMA safety
 */

const int FLEX_PIN = A0;     
const int MOSFET1_PIN = 9;
const int MOSFET2_PIN = 8;

// --- Calibration ---
int BEND_THRESHOLD1 = 50;    // dynamic threshold
const int MAX_BEND1 = 160;

// --- Variables ---
int sensorValue = 0;
int prevSensorValue = 0;
int initial = 0;
int t = 0;

bool sma1Active = false;
bool sma2Active = false;

bool coolingRequired = false;
unsigned long coolingStart = 0;

bool relaxCompleted = false;   // used to detect end of the relaxing phase

void setup() {
  pinMode(MOSFET1_PIN, OUTPUT);
  pinMode(MOSFET2_PIN, OUTPUT);
  digitalWrite(MOSFET1_PIN, LOW);
  digitalWrite(MOSFET2_PIN, LOW);

  Serial.begin(9600);
}

void loop() {

  sensorValue = analogRead(FLEX_PIN);

  if (t == 0) {
    initial = sensorValue;
    prevSensorValue = sensorValue;
    t++;
  }

  int deviation = sensorValue - initial;
  Serial.print("Sensor Value: ");
  Serial.print(deviation);
  Serial.print(" | Threshold: ");
  Serial.println(BEND_THRESHOLD1);

  // -----------------------------------------------------------
  // 1. MAX BEND → turn SMA1 off + start cooling
  // -----------------------------------------------------------
  if (deviation >= MAX_BEND1) {
    digitalWrite(MOSFET1_PIN, LOW);
    sma1Active = false;

    if (!coolingRequired) {
      coolingRequired = true;
      coolingStart = millis();
      Serial.println("Max bend reached — cooling for 2 seconds...");
    }
  }

  // -----------------------------------------------------------
  // 2. Cooling: block SMA2
  // -----------------------------------------------------------
  if (coolingRequired) {
    if (millis() - coolingStart < 2000) {
      digitalWrite(MOSFET2_PIN, LOW);
      sma2Active = false;
      delay(200);
      return;
    } else {
      coolingRequired = false;
      Serial.println("Cooling done — SMA2 allowed.");
    }
  }

  // -----------------------------------------------------------
  // 3. NORMAL OPERATION (not cooling)
  // -----------------------------------------------------------
  if (deviation > BEND_THRESHOLD1 && deviation < MAX_BEND1) {

    // bending forward
    if (sensorValue > prevSensorValue) {
      digitalWrite(MOSFET1_PIN, HIGH);
      digitalWrite(MOSFET2_PIN, LOW);
      sma1Active = true;
      sma2Active = false;
      relaxCompleted = false;  // new bend cycle starting
      Serial.println("SMA1 ACTIVATED (bending forward)");
    }

    // relaxing backward
    else if (sensorValue < prevSensorValue) {
      digitalWrite(MOSFET1_PIN, LOW);
      digitalWrite(MOSFET2_PIN, HIGH);
      sma1Active = false;
      sma2Active = true;

      Serial.println("SMA2 ACTIVATED (relaxing backward)");
    }
  }

  // -----------------------------------------------------------
  // 4. Fully relaxed region → threshold update happens here
  // -----------------------------------------------------------
  if (deviation <= BEND_THRESHOLD1) {

    if (!relaxCompleted && sma2Active) {
      // SMA2 has just finished relaxing → update threshold
      BEND_THRESHOLD1 -= 10;
      if (BEND_THRESHOLD1 < 5) BEND_THRESHOLD1 = 5; // safety clamp

      Serial.print("Relax complete → New Threshold = ");
      Serial.println(BEND_THRESHOLD1);

      relaxCompleted = true;
    }

    digitalWrite(MOSFET2_PIN, LOW);
    sma2Active = false;
    Serial.println("SMA2 OFF (fully relaxed)");
  }

  // -----------------------------------------------------------
  // 5. Update previous sensor value
  // -----------------------------------------------------------
  if (abs(prevSensorValue - sensorValue) > 5) {
    prevSensorValue = sensorValue;
  }

  delay(1000);
}


code with each loop threshold reduced by 10 units
