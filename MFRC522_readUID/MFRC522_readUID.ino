#include <deprecated.h>
#include <MFRC522.h>
#include <MFRC522Extended.h>
#include <require_cpp11.h>

#include <SPI.h>

const int RST_PIN = 9;
const int SS_PIN = 10;

/*------- Going to use Sector 0 - block 1 --------------------*/
const byte SECTOR_CARD = 0;
const byte BLOCK_ADDRESS_CARD = 1;

String currentCardUID = "";
/*---------------------------------------*/


MFRC522 cardSensor(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  SPI.begin();
  cardSensor.PCD_Init();
  pinMode(6, OUTPUT);
}


void loop() {
  if (cardSensor.PICC_IsNewCardPresent()) {
    if (cardSensor.PICC_ReadCardSerial()) {
      digitalWrite(6, HIGH);

      cardSensor.MIFARE_Read(BLOCK_ADDRESS_CARD, 16, 16);

      for (byte i = 0; i < cardSensor.uid.size; i++) {

        currentCardUID = currentCardUID + (cardSensor.uid.uidByte[i] < 0x10 ? "0" : "");
        currentCardUID = currentCardUID + String(cardSensor.uid.uidByte[i], HEX);

      }
      Serial.print(currentCardUID);
      delay(10);
      currentCardUID = "";
    } else {
      digitalWrite(6, LOW);
    }
  } else {
    digitalWrite(6, LOW);
  }

}
