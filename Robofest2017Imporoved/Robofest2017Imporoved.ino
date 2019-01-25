int SPEED  = 60;
int pwmconstrain = 255;
#define REVERSESPEED 50
#define TURNSPEED 120

int OVERSHOOT_TICKS = 520;
#define REVERSETICKS 400

#define PADDING 200
#define MAPPED_PADDING 170
#define RETURN_PADDING 160

#define BOXOVERSHOOT 100

#define BOXES 4


#define Kp 0.03
#define Kd 1.2 
#define Ki 0

/*===================================================================

          //QTRC Variables

  =====================================================================*/
#include <QTRSensors.h>
#define NUM_SENSORS   10     // number of sensors used
#define TIMEOUT       2500  // waits for 2500 microseconds for sensor outputs to go low
#define EMITTER_PIN   QTR_NO_EMITTER_PIN

// sensors 0 through 10 are connected to digital pins 3 through 10, respectively
QTRSensorsRC qtrrc((unsigned char[]) {
  38, 40, 22, 24, 26, 28, 30, 32, 34, 36  //38, 40, 22, 24, 26, 28, 30, 32, 34, 36
},
NUM_SENSORS, TIMEOUT, EMITTER_PIN);
unsigned int sensorValues[NUM_SENSORS];
unsigned int sensorRead[NUM_SENSORS];
unsigned int SensorPanelVal = 0;
unsigned int position = 0;
int _lastValue = 0;



/*===================================================================

          //Sonar Variables

  =====================================================================*/
#include <NewPing.h>

#define MAX_DISTANCE_FRONT 20 // Maximum distance we want to ping for (in centimeters). Maximum sensor distance is rated at 400-500cm.

#define SONAR1_ECHO 23
#define SONAR1_TRIG 25

#define SONAR2_ECHO 27
#define SONAR2_TRIG 29

#define SONAR3_ECHO 31
#define SONAR3_TRIG 33

#define SONAR4_ECHO 35
#define SONAR4_TRIG 37

#define SONAR5_ECHO 39
#define SONAR5_TRIG 41

NewPing sonar1(SONAR1_TRIG, SONAR1_ECHO, MAX_DISTANCE_FRONT); 
NewPing sonar2(SONAR2_TRIG, SONAR2_ECHO, MAX_DISTANCE_FRONT);
NewPing sonar3(SONAR3_TRIG, SONAR3_ECHO, MAX_DISTANCE_FRONT);
NewPing sonar4(SONAR4_TRIG, SONAR4_ECHO, MAX_DISTANCE_FRONT);
NewPing sonar5(SONAR5_TRIG, SONAR5_ECHO, MAX_DISTANCE_FRONT);
int i;
int tmp = 0;
int front, right, left,slantleft,slantright = 0;

/*===================================================================

          //Front VLX

  =====================================================================*/

#include <Wire.h>
#include <VL53L0X.h>

VL53L0X sensor;

/*===================================================================

          //Motor Driver Variables

  =====================================================================*/

#define LMOTORSPEED 4 //L PWM Pin
#define RMOTORSPEED 5 // R PWM Pin

#define LMOTOR1 43
#define LMOTOR2 45

#define RMOTOR1 49
#define RMOTOR2 47

#define MOTOREN 17
#define MOTOREN2 16

#define LMOTOR_ENC1 19
#define LMOTOR_ENC2 18

#define RMOTOR_ENC1 3
#define RMOTOR_ENC2 2

/* =============================================

    Encoder Variables

    ============================================
*/
#define ENCODER_OPTIMIZE_INTERRUPTS
#include <Encoder.h>

Encoder MasterENC(LMOTOR_ENC2, LMOTOR_ENC1);
Encoder SlaveENC(RMOTOR_ENC1, RMOTOR_ENC2);
long totalTicks = 0;

#define ticksperrevolutioncheapmotor 768
#define ticksperrevolution 816
#define ticksperinchcheapo 87 //cheap motor encoder pulses per inch (ZGA-31)
#define ticksperinch 94.45 //pololu motor encoder pulses per inch
#define tickspermm 7.42

int i_motord = 0;
boolean startingfromstop = 1;

int MasterPower = 0;
int SlavePower = 0;
int MaxPower = 0;

int error = 0;
int lasterror = 0;
int sumerr = 0;



/*===================================================================

          //Servo Variables

  =====================================================================*/

#include <Servo.h>

#define SERVO1 6
#define SERVO2 7
#define SERVO3 8
#define SERVO4 9
#define SERVO5 10

Servo grabber, lifter1, lifter2;


int servotmp = 0;

/*===================================================================

          //Pretty Lights and Switches

  ===================================================================== */

#define MODESW A13 //
bool startpressed = 0;
#define STARTSWITCH A15
bool modepressed = 0;
#define CALSW A14
bool calpressed = 0;

#define BLUELED A11
#define YELLOWLED A12


/*===================================================================

          //Path Variables

  ===================================================================== */

boolean nodeflag = 0;
int gotboxes = 0;
char doaction = 'S'; //start
char nextmove;
char path[100] = "";
char path_togoback[100] = "";
int path_length = 0;
int path_length_togoback = 0;

/*===================================================================

          //NRF Variables

  ===================================================================== */


#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
RF24 radio(15, 14); // CE, CSN
const byte addresses[][6] = {"00001", "00002"};


/*===================================================================

          //Color Sensor

  ===================================================================== */

#define S0 48
#define S1 46
#define S2 44
#define S3 42
#define sensorOut 12
int frequency = 0;

/*===================================================================

          //Wall Follow

  ===================================================================== */

int lastfound;
