#include <SD.h>
#include <SD_t3.h>
#include <Wire.h>
#include <TimeLib.h>
// A simple data logger for the Teensy analog pins
// how many milliseconds between grabbing data and logging it. 1 ms is 1000 x a second
#define LOG_INTERVAL 50 // millis between entries (reduce to take more/faster data)
// how many Milliseconds before writing the logged data permanently to disk
// set it to the LOG_INTERVAL to write each time (safest)
// set it to 10*LOG_INTERVAL to write all data every 10 datareads, you could lose up to
// the last 10 reads if power is lost but it uses less power and is much faster!
#define SYNC_INTERVAL 100 // millis between calls to flush() - to write data to the card
uint32_t syncTime = 0; // time of last sync()
#define ECHO_TO_SERIAL 1 // echo data to serial port 1 = Turned on
//here is the "go" button
#define WAIT_TO_START 1 // Wait for serial input in setup() 1 = autostart
// The analog pins that connect to the sensors
float Signal0 = A0; // analog 0
float Signal1 = A1; // analog 1
float Signal2 = A2; // analog 2
float Signal3 = A3; // analog 3
float Signal4 = A4; // analog 4
float Signal5 = A5; // analog 5
float Signal6 = A6; // analog 6
float Signal7 = A7; // analog 7
float Signal8 = A8; // analog 8
float Signal9 = A9; // analog 9
String zero = (Signal0);
String one = (Signal1);
String two = (Signal2);
String three = (Signal3);
String four = (Signal4);
String five = (Signal5);
String six = (Signal6);
String seven = (Signal7);
String eight = (Signal8);
String nine = (Signal9);
int ledState = LOW;
unsigned long previousmillis = 0;
long interval = 500;
// for teensy 3.x data logging , set chipSelect = BUILTIN_SDCARD SD
const int chipSelect = BUILTIN_SDCARD;
const int ledPin = 13;
int Trigger = 2;
//State on 2 triggers the logger
int TriggerState = 0;
//Trigger State varies with conditional logging
// the logging file
File logfile;
void error(char *str)
{
Serial.print("SD error: ");
Serial.println(str);
while (10); //Stops if you cannot read the SD
}
void setup(void)
{
setSyncProvider(getTeensy3Time);
Serial.begin(115200);
while (!Serial||(TriggerState = LOW));
// Wait for Arduino Serial or just use the trigger state conditions Monitor to open
delay(500);
if (timeStatus() != timeSet) {
Serial.println("Unable to sync with the RTC");
} else {
Serial.println("RTC has set the system time");
}
pinMode(ledPin, OUTPUT);
pinMode(TriggerState, INPUT);
// initialize the SD card
Serial.print("Initializing SD card…");
// see if the card is present and can be initialized:
if (!SD.begin(chipSelect)) {
Serial.println("Card failed, or not present");
}
else Serial.println("Card initialized.");
// create a new file
char filename[] = "LOGGER00.CSV";
for (uint8_t i = 0; i < 100; i++) {
filename[6] = i / 10 + '0';
filename[7] = i % 10 + '0';
if (! SD.exists(filename)) {
// only open a new file if it doesn't exist
logfile = SD.open(filename, FILE_WRITE);
break; // leave the loop!
}
}
if (! logfile) {
Serial.println("couldnt create file");
}
Serial.print("Logging to: ");
Serial.println(filename);
// connect to RTC how to invoke the Teensy3.6 RTC?
Wire.begin();
logfile.println("Year/Month/Day hh:mm:ss Signal0 ,Signal1 ,Signal2 ,Signal3 ,Signal4 ,Signal5 ,Signal6 ,Signal7 ,Signal8 ,Signal9 ");
#if ECHO_TO_SERIAL
Serial.println("Year/Month/Day hh:mm:ss Signal0 ,Signal1 ,Signal2 ,Signal3 ,Signal4 ,Signal5 ,Signal6 ,Signal7 ,Signal8 ,Signal9 ");
#endif //ECHO_TO_SERIAL
delay(3000);
}
void loop(void)
{
//uses the teensy time library TimeTeensy3
TriggerState = digitalRead(Trigger);
if (Serial.available()) {
time_t t = processSyncMessage();
if (t != 0) {
Teensy3Clock.set(t); // set the RTC
setTime(t);
}
}
digitalClockDisplay();
String Year = year();
String Mon = month();
String Day = day();
String Hour = hour();
String Min = minute();
String Sec = second();
//concatenate hour:minute string
delay(1);
delay((LOG_INTERVAL - 1) - (micros() % LOG_INTERVAL));
analogRead(Signal0);
delay(3);
int Sig0 = map((analogRead(Signal0)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal1);
delay(3);
int Sig1 = map((analogRead(Signal1)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal2);
delay(3);
int Sig2 = map((analogRead(Signal2)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal3);
delay(3);
int Sig3 = map((analogRead(Signal3)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal4);
delay(3);
int Sig4 = map((analogRead(Signal4)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal5);
delay(3);
int Sig5 = map((analogRead(Signal5)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal6);
delay(3);
int Sig6 = map((analogRead(Signal6)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal7);
delay(3);
int Sig7 = map((analogRead(Signal7)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal7);
delay(3);
int Sig8 = map((analogRead(Signal8)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
analogRead(Signal7);
delay(3);
int Sig9 = map((analogRead(Signal9)), 0, 921, 0, 255); //0-29 VDC channel scaled to 0-4.5 VDC
String zero = (Sig0 * 1.0);
String one = (Sig1 * 1.0);
String two = (Sig2 * 1.0);
String three = (Sig3 * 1.0);
String four = (Sig4 * 1.0);
String five = (Sig5 * 1.0);
String six = (Sig6 * 1.0);
String seven = (Sig7 * 1.0);
String eight = (Sig8 * 1.0);
String nine = (Sig9 * 1.0);
int h = Hour.toInt();
int m = Min.toInt();
int s = Sec.toInt();
String ymd = (Year + "," + Mon + "," + Day + " ");
String data = (" ," + zero + "," + one + "," + two + "," + three + "," + four + "," + five + "," + six + "," + seven + "," + eight + "," + nine);
if(TriggerState == HIGH){
//Here you set the conditions for logging to start or stop
logfile.print(ymd);
logfile.printf("%02d", h);
logfile.print(",");
logfile.printf("%02d", m);
logfile.print(",");
logfile.printf("%02d", s);
logfile.print(data);
logfile.println();
}
#if ECHO_TO_SERIAL
if(TriggerState == HIGH){
Serial.print(ymd);
Serial.print(TriggerState);
Serial.printf(" %02d", h);
Serial.print(":");
Serial.printf("%02d", m);
Serial.print(":");
Serial.printf("%02d", s);
Serial.print(data);
Serial.println();
}
#endif //ECHO_TO_SERIAL
// Now we write data to disk! Don't sync too often - requires 2048 bytes of I/O to SD card
// which uses a bunch of power and takes time
if ((micros() - syncTime) < SYNC_INTERVAL) return;
syncTime = micros();
// blink LED to show we are syncing data to the card & updating FAT!
logfile.flush();//physically save any bytes written to the file to the SD card
{
unsigned long currentmillis = micros();
if ((currentmillis - previousmillis) * 10 > interval) {
  // save the last time you blinked the LED
  previousmillis = currentmillis;

  // if the LED is off turn it on and vice-versa:
  if (ledState == LOW)
    ledState = HIGH;
  else
    ledState = LOW;

  // set the LED with the ledState of the variable:
  digitalWrite(ledPin, ledState);
}// wait for a second
}
}
void digitalClockDisplay() {
// digital clock display of the time
}
time_t getTeensy3Time()
{
return Teensy3Clock.get();
}
/* code to process time sync messages from the serial port */
#define TIME_HEADER "T" // Header tag for serial time sync message
unsigned long processSyncMessage() {
unsigned long pctime = 0L;
const unsigned long DEFAULT_TIME = 1357041600; // Jan 1 2020
if (Serial.find(TIME_HEADER)) {
pctime = Serial.parseInt();
return pctime;
if ( pctime < DEFAULT_TIME) { // check the value is a valid time (greater than Jan 1 2013)
pctime = 0L; // return 0 to indicate that the time is not valid
}
}
return pctime;
}
void printDigits(int digits) {
// utility function for digital clock display: prints preceding colon and leading 0
Serial.print(": ");
if (digits < 10)
Serial.print('0');
Serial.print(digits);
}
