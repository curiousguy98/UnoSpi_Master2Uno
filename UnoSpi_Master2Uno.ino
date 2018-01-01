/* SPI Master Demo
 * SPI pin numbers:
 * SCK   13  // Serial Clock.
 * MISO  12  // Master In Slave Out.
 * MOSI  11  // Master Out Slave In.
 * SS    10  // Slave Select
 */
// Include SPI (Serial Peripheral Interface) library.
#include <SPI.h>

unsigned long nextMillis = 0;    // Next millis() for master LED update.
// The setup() function runs after reset.
void setup() {
  // Initialize serial for DEBUG.
  Serial.begin(115200);

  // Initialize nextMillis.
  nextMillis = millis();
  
  // Initialize SPI.
  // SCK, MOSI, SS pins into output mode
  // also put SCK, MOSI into LOW state, and SS into HIGH state.
  // Then put SPI hardware into Master mode and turn SPI on
  SPI.begin();
  
  // Slow down the master a bit
  SPI.setClockDivider(SPI_CLOCK_DIV8);
  // Master initialized.
  Serial.println("Master Initialized");
}

void sendData(uint8_t * data, size_t len)
{
    // Select and wait for slave.
    digitalWrite(SS, LOW);

    // 发送字串
    char index;
          
    //SPI.transfer(0x02);
    while(len-- && index < 32) {
      SPI.transfer(data[index++]);
    }
    
    // Disable slave.
    digitalWrite(SS, HIGH);
}
    
// The loop() function runs continuously after setup().
void loop() {

  // Time to update master LED?
  if (millis() >= nextMillis) {
    // Yes, update nextMillis.
    nextMillis = millis() + 5000;
    Serial.println("nextMillis Updated.");
    
    const char * data = "Hello, My World!\n";
    int str_len = strlen(data);

    sendData(data, str_len);
    Serial.print(str_len);
    Serial.print(data);
  } 
}

