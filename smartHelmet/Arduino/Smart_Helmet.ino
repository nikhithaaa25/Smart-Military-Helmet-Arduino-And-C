#include <LiquidCrystal.h>

// LCD pins (non-I2C)
#define RS 12
#define EN 11
#define D4 5
#define D5 4
#define D6 3
#define D7 2
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Pins
#define TEMP_PIN A0 // LM35
#define GAS_PIN A1
#define HEART_PIN A2
#define BTN_PIN 7
#define BUZZER 8

// Thresholds
const float TEMP_HIGH_ALERT = 40.0;
const float TEMP_LOW_ALERT  = 10.0;
const int GAS_ALERT = 150;
const int HEART_LOW = 50;
const int HEART_HIGH = 125;

// GPS locations
const char* gpsLocations[] = {
    "19.0760N,72.8777E",
    "28.6139N,77.2090E",
    "13.0827N,80.2707E",
    "26.9124N,75.7873E",
    "22.5726N,88.3639E"
};
int gpsIndex = 0;
int gpsCount = sizeof(gpsLocations) / sizeof(gpsLocations[0]);
unsigned long lastGpsChange = 0;
const unsigned long debounce = 200;

float readTemperature() {
    int raw = analogRead(TEMP_PIN);
    float voltage = (raw * 5.0) / 1023.0;
    return voltage * 100.0;
}

int readHeartRate() {
    int raw = analogRead(HEART_PIN);
    return map(raw, 0, 1023, 40, 180);
}

int readGas() {
    return analogRead(GAS_PIN);
}

void setup() {
    Serial.begin(9600);
    lcd.begin(16, 2);
    pinMode(BTN_PIN, INPUT_PULLUP);
    pinMode(BUZZER, OUTPUT);

    lcd.setCursor(0,0);
    lcd.print("Helmet Monitor");
    delay(1500);
    lcd.clear();
}

void loop() {
    float tempC = readTemperature();
    int gasVal = readGas();
    int bpm = readHeartRate();

    if (digitalRead(BTN_PIN) == LOW) {
        if (millis() - lastGpsChange > debounce) {
            gpsIndex = (gpsIndex + 1) % gpsCount;
            lastGpsChange = millis();
        }
    } else {
        if (millis() - lastGpsChange > 10000) {
            gpsIndex = (gpsIndex + 1) % gpsCount;
            lastGpsChange = millis();
        }
    }
    const char* gpsNow = gpsLocations[gpsIndex];

    bool tempHighAlert = (tempC >= TEMP_HIGH_ALERT);
    bool tempLowAlert  = (tempC <= TEMP_LOW_ALERT);
    bool gasAlert      = (gasVal >= GAS_ALERT);
    bool heartAlert    = (bpm < HEART_LOW || bpm > HEART_HIGH);

    bool alert = tempHighAlert || tempLowAlert || gasAlert || heartAlert;
    if (alert) {
        tone(BUZZER, 1200);
    } else {
        noTone(BUZZER);
    }

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("T:"); lcd.print(tempC,1); lcd.print("C ");
    lcd.print("G:"); lcd.print(gasVal);
    lcd.setCursor(0,1);
    lcd.print("H:"); lcd.print(bpm);
    lcd.print(" GPS:");
    lcd.print(String(gpsNow).substring(0,5));

    unsigned long t = millis() / 1000;
    unsigned int sec = t % 60;
    unsigned int min = (t / 60) % 60;
    unsigned int hr = t / 3600;

    Serial.println("==================================================");
    Serial.print("[");
    if (hr < 10) Serial.print("0"); Serial.print(hr); Serial.print(":");
    if (min < 10) Serial.print("0"); Serial.print(min); Serial.print(":");
    if (sec < 10) Serial.print("0"); Serial.print(sec);
    Serial.print("]  Location: "); Serial.println(gpsNow);
    Serial.println("--------------------------------------------------");
    Serial.print("Temp  : "); Serial.print(tempC,1); Serial.println(" °C");
    Serial.print("Gas   : "); Serial.println(gasVal);
    Serial.print("Heart : "); Serial.print(bpm); Serial.println(" bpm");
    Serial.println("--------------------------------------------------");
    if (tempHighAlert) Serial.println("ALERT: High Temperature!");
    if (tempLowAlert) Serial.println("ALERT: Low Temperature!");
    if (gasAlert) Serial.println("ALERT: Dangerous Gas Level!");
    if (heartAlert && bpm < HEART_LOW) Serial.println("ALERT: Heart Rate Too Low!");
    if (heartAlert && bpm > HEART_HIGH) Serial.println("ALERT: Heart Rate Too High!");
    if (!alert) Serial.println("All conditions normal.");
    Serial.println("==================================================\n");

    delay(5000);
}
