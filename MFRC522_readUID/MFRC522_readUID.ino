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
  // put your setup code here, to run once:
  Serial.begin(9600);
  SPI.begin();
  cardSensor.PCD_Init();
}

void loop() {
  // put your main code here, to run repeatedly:

  if (cardSensor.PICC_IsNewCardPresent()) {
    //Serial.println("Is near");
    if (cardSensor.PICC_ReadCardSerial()) {
      //Serial.println("Can read it");
      cardSensor.MIFARE_Read(BLOCK_ADDRESS_CARD, 16, 16);
      //Serial.print("cardSensor.uid.size- ");
      //Serial.println(cardSensor.uid.size);
      //Serial.print("cardSensor.uid.uidByte- ");

      for (byte i = 0; i < cardSensor.uid.size; i++) {
        //  Serial.print(cardSensor.uid.uidByte[i] < 0x10 ? " 0" : "");
        //currentCardUID = currentCardUID + String(cardSensor.uid.uidByte[i], HEX);
        //Serial.print();
        //currentCardUID = currentCardUID + (cardSensor.uid.uidByte[i] < 0x10 ? "0" : String(cardSensor.uid.uidByte[i], HEX));
        //Serial.print(cardSensor.uid.uidByte[i] < 0x10 ? " 0" : " ");
        currentCardUID = currentCardUID + (cardSensor.uid.uidByte[i] < 0x10 ? "0" : "");
        //Serial.print(cardSensor.uid.uidByte[i], HEX);
        currentCardUID = currentCardUID + String(cardSensor.uid.uidByte[i], HEX);
        delay(10);
      }
      //Serial.print("currentCardUID is: ");
      Serial.print(currentCardUID);
      delay(500);
      currentCardUID = "";
    }
  } else {
    currentCardUID = "";
  }

}
