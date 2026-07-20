#include <Wire.h>
uint16_t channel = 187;
#define RDA5807M_ADDRESS 0b0010000 // 0x10
#define BOOT_CONFIG_LEN 12
#define TUNE_CONFIG_LEN 4
uint8_t boot_config[] = {
    0b11000001,
    0b00000011,
    0b00000000,
    0b00000000,
    0b00001010,
    0b00000000,
    0b10001000,
    0b00001111,
    0b00000000,
    0b00000000,
    0b01000010,
    0b00000010,
};
uint8_t tune_config[] = {
    0b11000000,
    0b00000001,
    (channel >> 2),
    ((channel & 0b11) << 6) | 0b00010000};
void setup()
{
  Serial.begin(9600);
  pinMode(A0, INPUT);
  Wire.begin();
  Wire.beginTransmission(RDA5807M_ADDRESS);
  Wire.write(boot_config, BOOT_CONFIG_LEN);
  Wire.endTransmission();
  Wire.beginTransmission(RDA5807M_ADDRESS);
  Wire.write(tune_config, TUNE_CONFIG_LEN);
  Wire.endTransmission();
} // setup end
void loop()
{
  int channel1 = 90, newA;
  static int oldA = 0; // set the oldA as HIGH
  int result = 0;
  newA = digitalRead(A0);
  if (newA != oldA)
  {
    Serial.println(newA);
    if (newA != oldA)
    {
      channel = channel1 + newA;
      myChangeChannel(channel);
      oldA = newA;
    }
  }
  uint16_t frequency = channel + 870;
  uint16_t num1 = (frequency / 1000) % 10;
  uint16_t num2 = (frequency / 100) % 10;
  uint16_t num3 = (frequency / 10) % 10;
  uint16_t num4 = frequency % 10;
  Serial.print(num1);
  Serial.print(num2);
  Serial.print(num3);
  Serial.print(num4);
  Serial.print("--");
  Serial.println(channel + 870);
} // loop end
/*
 * Function to change channel on radio RDA5807
 * Example: channel = 191
 */
void myChangeChannel(int channel)
{ /* void if nothing is returned else int */
  /*
   * first write new channel to tune_config massive
   */
  tune_config[2] = (channel >> 2);
  tune_config[3] = ((channel & 0b11) << 6) | 0b00010000;
  Wire.begin();
  Wire.beginTransmission(RDA5807M_ADDRESS);
  Wire.write(tune_config, TUNE_CONFIG_LEN);
  Wire.endTransmission();
}