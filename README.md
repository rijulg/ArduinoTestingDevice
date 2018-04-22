# ArduinoTestingDevice
This program was developed for testing the Labs in ELEC3607 of The University of Sydney in 2018.

It's based on the existing work done for the SEEED Studio Bluetooth Shield v2 by Steve Chang and an improvement of Processing graphing program made by Sofian Audry by Farzad Noorian.

# Components
1. Arduino DUE
   ![Arduino DUE](https://http2.mlstatic.com/arduino-due-D_NQ_NP_698547-MLM25572697538_052017-F.jpg)
2. SEEED Studio Bluetooth Shield v2
   ![Bluetooth Shield](http://img.dxcdn.com/productimages/sku_336740_1_270X270.jpg)
3. Jumpers
4. Computer with Arduino IDE and Processing

# Supported modes
1. Bluetooth Master
2. Bluetooth Slave
3. Manchester Decoder
4. Manchester Sender

# How to Use this
1. Upload the Arduino program into an Arduino DUE
2. Mount a SEEED Studio Bluetooth Shield on the Arduino and connect the RX/TX with Serial 2 (pin 16, 17)
3. Use another jumper to select the mode to run the device in, you will need to connect Ground with pins defined in the base class (MasterDevice)
   With the original code the following mapping works:
   
   | Pin | Mode |
   | --- | --- |
   | 10 | Bluetooth Master |
   | 11 | Bluetooth Slave |
   | 12 | Manchester Decoder |
   | 13 | Manchester Sender |
   
 Note: You need to select the mode before powering up the device, that is jump the pin before powering up the device. Alternatively you can jump the respective pin and hit reset.
   
# Mode specific Instructions

### Bluetooth Master & Slave
The program does not set up a pin, and therefore works without it.

### Bluetooth Master
After running the program open the Serial Monitor and enter the name of the slave you want to connect with.

### Manchester Decoder
1. Take the input from pin 19 i.e. The RX of Serial 1
2. Once you have the input coming in you can check it on the Serial Monitor
3. Make sure you close the Serial Monitor and then run the Processing program
4. If the output is correct you will see a graph like this
   ![Processing Graph](https://raw.githubusercontent.com/rijulg/ArduinoTestingDevice/master/ProcessingOutput.PNG)
   This graph corresponds to 0 -> 0xFF values being sent


### Manchester Sender
Provide the output from pin 22

# What it looks like
The setup of 2 devices talking with each other (Manchester Sender and Manchester Decoder)
![Setup](https://raw.githubusercontent.com/rijulg/ArduinoTestingDevice/master/setup.jpg)
