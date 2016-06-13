/*
sensor test
sensors used:
  Infrared Proximity sensor Long Range - Sharp (SEN-08958)
  SparkFun ToF Range Finder Sensor (SEN-12785)
  Ultrasonic Range Finder - HRXL MaxSonar WR (SEN-11724)
  Ultrasonic Range Finder - HRLV-MaxSonar-EZ4 (SEN-11309)
*/
//inclusions
#include <Wire.h> //include the I2C header
#include <SparkFun_VL6180X.h> //include the ToF library header

//contsants. These do not change. Pin Locations.
#define IRPIN 0 //the analog pin with the Sharp Infrared sensor 
#define EZPIN 1 //the analog pin with the MaxSonar EZ4
#define WRPIN 2 //the analog pin with the MaxSonar WR

#define VL6180X_ADDRESS 0x29 //set the I2C address for the ToF sensor

VL6180xIdentification identification; //initiate the sensor ID for the sensor object
VL6180x sensor(VL6180X_ADDRESS); //initiate the sensor object

void setup() 
{  //launch the serial port for data reporting to the terminal monitor window.
  Serial.begin(115200); //begin serial instance at 115200 baud
  Wire.begin(); // begin I2C instance
  delay(100); //pause 0.1 second

  sensor.getIdentification(&identification); // Retrieve manufacture info from device memory
  printIdentification(&identification); // Helper function to print all the Module information

    if(sensor.VL6180xInit() != 0){
    Serial.println("FAILED TO INITALIZE"); //Initialize device and check for errors
  }; 

  sensor.VL6180xDefautSettings(); //Load default settings to get started.
  
    delay(1000); // delay 1s


}

void loop() 
{
  Serial.print("Sharp = "); // verbose text
  Serial.print(1023-analogRead(IRPIN));//display IR sensor value
  Serial.print("/1023, EZ4 = "); // verbose text
  Serial.print(analogRead(EZPIN));//display EZ4 ultrasonic sensor value
  Serial.print("/1023, WR = "); // verbose text
  Serial.print(analogRead(WRPIN)); //display WR ultrasonic sensor value
  Serial.print("/1023, ToF = "); // verbose text
  Serial.print(sensor.getDistance()); //display ToF sensor value
  Serial.println(" [mm]"); // verbose text - end of line
  delay(100); //pause for another tenth of a second
}

void printIdentification(struct VL6180xIdentification *temp)
{
  Serial.print("Model ID = ");
  Serial.println(temp->idModel);

  Serial.print("Model Rev = ");
  Serial.print(temp->idModelRevMajor);
  Serial.print(".");
  Serial.println(temp->idModelRevMinor);

  Serial.print("Module Rev = ");
  Serial.print(temp->idModuleRevMajor);
  Serial.print(".");
  Serial.println(temp->idModuleRevMinor);  

  Serial.print("Manufacture Date = ");
  Serial.print((temp->idDate >> 3) & 0x001F);
  Serial.print("/");
  Serial.print((temp->idDate >> 8) & 0x000F);
  Serial.print("/1");
  Serial.print((temp->idDate >> 12) & 0x000F);
  Serial.print(" Phase: ");
  Serial.println(temp->idDate & 0x0007);

  Serial.print("Manufacture Time (s)= ");
  Serial.println(temp->idTime * 2);
  Serial.println();
  Serial.println();
}
