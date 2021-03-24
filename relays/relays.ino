#include <Wire.h>

// MCP23017_I2CR16G5LE I2C address is 0x20(32)
int n_modules = 2;
int port[] = {0x12, 0x13, 0x18, 0x19};
int address[] = {0x20, 0x21};

void setup()
{
  // Start I2C transmission as MASTER
  Wire.begin();
  Serial.begin(9600);

  startModules();
}

void loop()
{
  while (Serial.available() == 0) {

  }

  String binary = Serial.readString();
  String msg = "";

  for (int i = 0, count = 1, port_count = 0, addr_count = 0; i < binary.length(); i ++, count++) {

    msg += binary[i];

    if (count == 8) {
      Serial.println("Binary:");
      Serial.println(msg);

      sendModuleCommand(address[addr_count], port[port_count], convertBinToDecimal(msg));

      msg = "";
      count = 0;
      port_count++;

      //2,4,6,8

      if (port_count % 2 == 0) {
        addr_count++;
      }
    }
  }
}

void sendModuleCommand(int address, int port, int number) {

  Serial.println("Address: ");
  Serial.println(address);
  Serial.println("Port: ");
  Serial.println(port);
  Serial.println("Decimal: ");
  Serial.println(number);

  // Start I2C Transmission
  Wire.beginTransmission(address);
  // Select GPIOB register
  Wire.write(port);
  // All pins of ports are set to logic HIGH or LOW
  Wire.write(number);
  // Stop I2C transmission
  Wire.endTransmission();
}

void startModules() {
  delay(2000);
  int sizePort = sizeof(port) / sizeof(port[0]);

  Serial.println("Modules ON");
  for (int count = 0; count < n_modules; count++) {

    for (int countPort = 0; countPort < sizePort; countPort++) {

      // Start I2C Transmission
      Wire.beginTransmission(address[count]);
      // Select IODIRA register
      Wire.write(0x00);
      // Set Port A as OUTPUT
      Wire.write(0x00);
      // Stop I2C Transmission
      Wire.endTransmission();

      // Start I2C Transmission
      Wire.beginTransmission(address[count]);
      // Select GPIOB register
      Wire.write(port[countPort]);
      // All pins of port are set to logic HIGH
      Wire.write(0b00000000);
      // Stop I2C transmission
      Wire.endTransmission();


      delay(2000);

      // Start I2C Transmission
      Wire.beginTransmission(address[count]);
      // Select IODIRB register
      Wire.write(0x01);
      // Set Port B as OUTPUT
      Wire.write(0x00);
      // Stop I2C Transmission
      Wire.endTransmission();

      
      // Start I2C Transmission
      Wire.beginTransmission(address[count]);
      // Select GPIOB register
      Wire.write(port[countPort]);
      // All pins of port are set to logic HIGH
      Wire.write(0b00000000);
      // Stop I2C transmission
      Wire.endTransmission();
    }

    delay(2000);
  }
}

int convertBinToDecimal(String bin) {

  int binaryLength = bin.length();
  int decimal = 0;
  int base = 1;

  for (int i = binaryLength - 1; i >= 0; i--) {
    if (bin[i] == '1') {
      decimal += base;
    }

    base *= 2;
  }
  return decimal;
}
