//https : //github.com/Stan-Reifel/SpeedyStepper

#include <SpeedyStepper.h>

const int LED_PIN = 13;
const int ENABLE = 6;
const int MOTOR_STEP_PIN = 4;
const int MOTOR_DIRECTION_PIN = 5;

//Chave seletora de modo de operação
int opModeButton = 8;

//Pulsador para iniciar operação
int startCycle = 7;

//True = Modo Atomático, False = Operação Manual
bool opModeStatus = false;

//Variável para guardar status do pulsador, se foi pressionado ou não
bool isCycleRunning = false;

//Cria objeto do SpeedyStepper para o motor
SpeedyStepper stepper;

void setup()
{
    pinMode(LED_PIN, OUTPUT);
    pinMode(ENABLE, OUTPUT);
    digitalWrite(ENABLE, LOW);

    pinMode(opModeButton, INPUT_PULLUP);
    pinMode(startCycle, INPUT_PULLUP);

    digitalWrite(startCycle, LOW);

    Serial.begin(9600);

    stepper.connectToPins(MOTOR_STEP_PIN, MOTOR_DIRECTION_PIN);

    //stepper.setStepsPerRevolution(3428.571429);
    stepper.setStepsPerRevolution(3429.15);

    stepper.setSpeedInRevolutionsPerSecond(1.0);
    stepper.setAccelerationInRevolutionsPerSecondPerSecond(10.0);
}

void loop()
{
    opModeStatus = digitalRead(opModeButton);
    isCycleRunning = digitalRead(startCycle);

    //Modo de operação automática
    if (opModeStatus == true && isCycleRunning == true)
    {
        do
        {
            quarterTurn();
            opModeStatus = digitalRead(opModeButton);
       
        } while (opModeStatus == true);
        isCycleRunning = false;
    }


    //Modo de operação manual
    if (opModeStatus == false && isCycleRunning == true)
    {
        quarterTurn();
        isCycleRunning = false;
    }
    
}

void quarterTurn()
{
    stepper.moveRelativeInRevolutions(0.25);
    delay(750);
}
