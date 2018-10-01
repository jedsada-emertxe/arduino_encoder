
//——code for RPM—————-
int encoder_pin = 2;
// The pin the encoder is connected
unsigned int rpm;
// rpm reading
volatile byte pulses;
// number of pulses
unsigned long timeold;
// The number of pulses per revolution
// depends on your index disc!!
unsigned int pulsesperturn = 1;
void counter()
{
  //Update count
  pulses++;
}
//———————————–
void setup() {
  
  pinMode(6, OUTPUT);   // sets the pin as output
  analogWrite(6, 70);
  
  Serial.begin(9600);
  // by default, we’ll generate the high voltage from the 3.3v line internally! (neat!)
  //———–code for RPM—————
  //Use statusPin to flash along with interrupts
  pinMode(encoder_pin, INPUT);
  //Interrupt 0 is digital pin 2, so that is where the IR detector is connected
  //Triggers on FALLING (change from HIGH to LOW)
  attachInterrupt(0, counter, FALLING);
  // Initialize
  pulses = 0;
  rpm = 0;
  timeold = 0;
}
void loop()
{
  if (millis() - timeold >= 1000) {
    /*Uptade every one second, this will be equal to reading frecuency (Hz).*/
    //Don’t process interrupts during calculations
    detachInterrupt(0);
    //Note that this would be 60*1000/(millis() – timeold)*pulses if the interrupt
    //happened once per revolution
    rpm = (60 * 1000 / pulsesperturn / (millis() - timeold) * ( pulses / 2));
    timeold = millis();
    pulses = 0;
    //Write it out to serial port
    Serial.print("RPM = ");
    Serial.println(rpm, DEC);
    //Restart the interrupt processing
    attachInterrupt(0, counter, FALLING);
  }
}
