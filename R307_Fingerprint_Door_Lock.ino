#include <Adafruit_Fingerprint.h>
#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

SoftwareSerial mySerial(2, 3);
Adafruit_Fingerprint finger = Adafruit_Fingerprint(&mySerial);

LiquidCrystal_I2C lcd(0x27, 16, 2);

#define LOCK_PIN 12
#define BUZZER 8
#define green_led 9
#define red_led 10

// MODE SELECTION
// 0 = Any fingerprint allowed
// 1 = Only specific fingerprints
#define ACCESS_MODE 1

int allowedIDs[] = {1,3,5};
int totalIDs = 3;

void setup()
{
  pinMode(LOCK_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);
  pinMode(green_led, OUTPUT);
  pinMode(red_led, OUTPUT);

  digitalWrite(LOCK_PIN, LOW);
  digitalWrite(BUZZER, LOW);
  digitalWrite(green_led, LOW);
  digitalWrite(red_led, LOW);

  Serial.begin(9600);
  finger.begin(57600);

  lcd.begin();
  lcd.backlight();

  lcd.print("Fingerprint Lock");
  lcd.setCursor(0,1);
  lcd.print("Initializing...");
  Serial.println("Initializing...");
  delay(2000);

  if (finger.verifyPassword())
  {
    Serial.println("Sensor Ready");
    lcd.clear();
    lcd.print("Sensor Ready");
    delay(1500);
  }
  else
  {
    Serial.println("Sensor Error");
    lcd.clear();
    lcd.print("Sensor Error");
    while (1);
  }
  digitalWrite(red_led, HIGH);
  lcd.clear();
  lcd.print("Place Finger");
}

void loop()
{
  int id = getFingerprintID();

  if (id > 0)
  {
    Serial.print("Finger ID: ");
    Serial.println(id);

    lcd.clear();
    lcd.print("Finger ID:");
    lcd.setCursor(0,1);
    lcd.print(id);

    if (checkAccess(id))
    {
      Serial.println("Access Granted");
      digitalWrite(green_led, HIGH);
      digitalWrite(red_led, LOW);
      lcd.clear();
      lcd.print("Access Granted");
      lcd.setCursor(0,1);
      lcd.print("Door Opening");

      grantedBeep();

      digitalWrite(LOCK_PIN, HIGH);
      delay(3000);
      digitalWrite(LOCK_PIN, LOW);
      digitalWrite(green_led, LOW);
      digitalWrite(red_led, HIGH);
    }
    else
    {
      Serial.println("Access Denied");

      lcd.clear();
      lcd.print("Access Denied");

      deniedBeep();
      delay(2000);
    }

    lcd.clear();
    lcd.print("Place Finger");
  }

  delay(50);
}

bool checkAccess(int id)
{
  if (ACCESS_MODE == 0)
  return true;

  for (int i = 0; i < totalIDs; i++)
  {
    if (id == allowedIDs[i])
    return true;
  }

  return false;
}

int getFingerprintID()
{
  uint8_t p = finger.getImage();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.image2Tz();
  if (p != FINGERPRINT_OK) return -1;

  p = finger.fingerSearch();
  if (p != FINGERPRINT_OK) return -1;

  return finger.fingerID;
}

// -------- BUZZER FUNCTIONS --------

void grantedBeep()
{
  for(int i=0;i<2;i++)
  {
    digitalWrite(BUZZER,HIGH);
    delay(150);
    digitalWrite(BUZZER,LOW);
    delay(150);
  }
}

void deniedBeep()
{
  digitalWrite(BUZZER,HIGH);
  delay(800);
  digitalWrite(BUZZER,LOW);
}
