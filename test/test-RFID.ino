#include <SPI.h>
#include <RFID.h>

#define SPI_MOSI 11
#define SPI_MISO 12
#define SPI_SCLK 13
#define SPI_SS   10
#define MFRC522_RSTPD 9

RFID rfid(SPI_SS, MFRC522_RSTPD);

void setup()
{
	SPI.begin();
	SPI.beginTransaction(SPISettings(10000000L, MSBFIRST, SPI_MODE3));

	rfid.begin();

	Serial.begin(9600);
	while (!Serial)
		;
}

static uint8_t status;
static uint16_t card_type;
static uint8_t sn[MAXRLEN], snBytes;

void loop()
{
	delay(500);
	if ((status = rfid.findTag(&card_type)) == STATUS_OK) {
		Serial.print("OK! ");
		Serial.println(card_type);
		if ((status = rfid.readTagSN(sn, &snBytes)) == STATUS_OK) {
			for (int i = 0; i < snBytes; ++i)
				Serial.print(sn[i], HEX);
			Serial.println();
		}
	} else {
		Serial.print("Sad... Error ID: ");
		Serial.println(status);
	}
}
