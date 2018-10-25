#define TPM_C 48000000            // core clock, for calculation only
#define PWM_FREQ 100000            //  PWM frequency [Hz]
#define MODULO (TPM_C / PWM_FREQ) // calculation the modulo for FTM0

int PWMcounter = 10;
unsigned long prevTime;

void setup() {
  prevTime = millis();
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  pinMode(10,OUTPUT);
  // put your setup code here, to run once:
//      FTM0_POL = 0;                  // Positive Polarity 
    FTM0_OUTMASK = 0xFF;           // Use mask to disable outputs
    FTM0_SC = 0x08 | 0x00;                // set system clock as source for FTM0
    FTM0_MOD = MODULO;             // Period register
    FTM0_CNTIN = 0;                // Counter initial value
    FTM0_COMBINE = 0x00000033;     // COMBINE=1, COMP=1, DTEN=1, SYNCEN=1            // page 796  (COMP1 sets complement)
    
    FTM0_SYNC = 0x02;              // PWM sync @ max loading point enable
    FTM0_DEADTIME = 0b00<<6;       // DeadTimer prescale systemClk/1                 // page 801
    FTM0_DEADTIME |= 0b000000;     // 1uS DeadTime, max of 63 counts of 48Mhz clock  // page 801
//    FTM0_C0V = 0;                  // Combine mode, pulse-width controlled by...
//    FTM0_C1V = MODULO/2;           //   odd channel.
    FTM0_SYNC |= 0x80;             // set PWM value update
    FTM0_C0SC = 0x28;              // PWM output, edge aligned, positive signal
//    FTM0_C1SC = 0x28;              // PWM output, edge aligned, positive signal
    
    CORE_PIN22_CONFIG = PORT_PCR_MUX(1) | PORT_PCR_DSE | PORT_PCR_SRE;    //config teensy output port pins
    CORE_PIN23_CONFIG = PORT_PCR_MUX(2) | PORT_PCR_DSE | PORT_PCR_SRE;   //config teensy output port pins

   FTM0_OUTMASK = 0x0;            // Turns on PWM output
   
//   FTM0_C1V = MODULO*(1); // sets both low and high side
//   FTM0_SYNC |= 0x80;

    FTM0_C0V = MODULO/4 ;
    FTM0_SYNC |= 0x80;
   FTM0_MODE = 0x01;              // Enable FTM0
}

void loop() {
  // put your main code here, to run repeatedly:
//  if ((millis() % 1000) == 0){
//    Serial.println("HI");
  if((millis()-prevTime) > 50){
    prevTime = millis();
    FTM0_C0V = PWMcounter;
    FTM0_SYNC |= 0x80;             // set PWM value update
    PWMcounter++;
    if (PWMcounter > MODULO){
      PWMcounter = 0;
    }
  }
//  }

//  if ((millis()-prevTime) > 1000){
//    prevTime = millis();
//    FTM0_OUTMASK = 0x03 & (~(FTM0_OUTMASK & 3));
//  }
  
  digitalWrite(10, !digitalRead(10));
//  delay(10);
}
