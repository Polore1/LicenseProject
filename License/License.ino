/***************** defines *****************/
#define CONTROL_DISTANCE 12 //cm
#define CONSECUTIVE_RIGHT_ROTATION 2
#define OUTSIDEDISTANCE 1000
#define MATRIXLEN 20
#define echoPinLeft 10
#define trigPinLeft 9
#define echoPinFront 12
#define trigPinFront 11
#define SET 1
#define UNSET 0
#define ledFront A3
//#define ledFrontL 2
#define ledBackR A1
#define ledBackL A2
/***************** variables *****************/
int distanceLEFT=100, distanceFRONT=100;
bool mat[MATRIXLEN][MATRIXLEN];
enum direction {north = 1, west, south, east};
int xMove = 19, yMove = 9, wrong_road = 0, Step = north;
int xMoveAux = 0, yMoveAux = 0;
//motor A connections
int motorLeft1 = 6;    //inF1
int motorLeft2 = 7;    //inF2
// Motor B connections
int motorRight1 = 4;  //inL1
int motorRight2 = 5;  //inL2


/***************** prototype *****************/
void moveing(int xMove, int yMove, int xMoveAux, int yMoveAux);
void showMatrix(bool a[MATRIXLEN][MATRIXLEN]);
int readSensorDist(int echoPin, int trigPin);
void printDistance(int distance, char nameSensor);
void turnLeft(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void turnRight(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void goForword(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void goForword2(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void stopMotors(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void stopGoing(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);
void goBackword(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2);

/***************** setup *****************/
void setup()
{
  /* Set all the motor control pins to outputs*/
  Serial.begin(9600);
  pinMode(motorLeft1, OUTPUT);
  pinMode(motorLeft2, OUTPUT);
  pinMode(motorRight1, OUTPUT);
  pinMode(motorRight2, OUTPUT);

  pinMode(echoPinLeft, INPUT);
  pinMode(trigPinLeft, OUTPUT);

  pinMode(echoPinFront, INPUT);
  pinMode(trigPinFront, OUTPUT);

  /* Turn off motors - Initial state 
     LOW = 0
     HIGH = 1
  */
  //digitalWrite(motorLeft1, LOW);    
//  digitalWrite(motorLeft2, LOW);    
//  digitalWrite(motorRight1, LOW);
//  digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, LOW);    
    analogWrite(motorLeft2, LOW);    
    analogWrite(motorRight1, LOW);
    analogWrite(motorRight2, LOW);


  
  /* Leds are set on off because they are used when a turn is made*/
  analogWrite(ledBackR,LOW);
  analogWrite(ledBackL,LOW);
}
/***************** loop *****************/
void loop()
  {
    /* Set 1 in matrix in the poz that is the robot */
     mat[xMove][yMove] = SET;
   
 /* - conditions delete  but they can be added. Are correct.
    distanceLEFT = readSensorDist(echoPinLeft, trigPinLeft);
    distanceFRONT = readSensorDist(echoPinFront, trigPinFront);

    Serial.print("*FRONT: ");
    Serial.println(distanceFRONT);
    Serial.print("*LEFT: ");
    Serial.println(distanceLEFT);
    
     //distanceFRONT = readSensorDist(echoPinFront, trigPinFront);
     goForword(motorLeft1, motorLeft2, motorRight1, motorRight2);
     if (distanceFRONT < CONTROL_DISTANCE)
     {
      turnLeft(motorLeft1, motorLeft2, motorRight1, motorRight2);
     }
     
    goForword(motorLeft1, motorLeft2, motorRight1, motorRight2);
*/

    distanceLEFT = readSensorDist(echoPinLeft, trigPinLeft);
    distanceFRONT = readSensorDist(echoPinFront, trigPinFront);
    
//    analogWrite(ledFront,0);
//    delay(1000);
//    analogWrite(ledFront,500);
//    delay(1000);
    //verify if you are still in the maze
    //while (distanceLEFT < OUTSIDEDISTANCE && distanceFRONT < OUTSIDEDISTANCE)
    if ((distanceLEFT < OUTSIDEDISTANCE) && (distanceFRONT < OUTSIDEDISTANCE))
    {

        /* The front LEDs are connected in series and will be switched on from the beginning to the end of the route*/
        analogWrite(ledFront,500);
    /* The two ultrasonic sensors on the front and on the left detect the new information about the route */
        //distanceLEFT = readSensorDist(echoPinLeft, trigPinLeft);
        //distanceFRONT = readSensorDist(echoPinFront, trigPinFront);
    
        //Serial.print("FRONT: ");
        //Serial.println(distanceFRONT);
        //Serial.print("LEFT: ");
        //Serial.println(distanceLEFT);
        //index++;
    
        //show the matrix on the display
        //showMatrix(mat);

        //read distances form sensors
        //distanceLEFT = readSensorDist(echoPinLeft, trigPinLeft);
        //distanceFRONT = readSensorDist(echoPinFront, trigPinFront);

        /* Verify that you can go in left and modity 'Step' value */
        if(distanceLEFT > CONTROL_DISTANCE)   //distLeft>50
        {
            Step++;
            /* If Step reaches the last value in the enum, the first value is set */
            if(Step>east)
            {
                Step=north;
            }
        }
        else
        {
            /* Verity that bouth of the sensors detects wall and modity 'Step' value */
            if(distanceLEFT <= CONTROL_DISTANCE && distanceFRONT <= CONTROL_DISTANCE)
            {
                Step--;
                /* If Step reaches the first value in the enum, the last value is set */
                if(Step<north)
                {
                    Step = east;
                }
            }
        }

        /* Verity that bouth of the sensors detects wall and do nothing */
        if((distanceLEFT <= CONTROL_DISTANCE) && (distanceFRONT <= CONTROL_DISTANCE))
        {
            
            /* Do nothing */
        }
        else
        {
            /* Create beckup for actual position of the robot. 
        - xMoveAux and yMoveAux are the values of the position that the robot has now
        - xMove and yMove are the values of a position that the robot will take in the next step
      */
            xMoveAux = xMove;
            yMoveAux = yMove;

            /* Set x and y positions will take in mat[][] depending on the next 'Step' */
            switch(Step)
            {
            case north:
                xMove--;
                break;
            case south:
                xMove++;
                break;
            case west:
                yMove--;
                break;
            case east:
                yMove++;
                break;
            default:
                break;
            }
        }

        /* The robot is moveing depending on current and future x and y positions */
        moving(xMove, yMove, xMoveAux, yMoveAux);
        

    /* The motors are stoped and is waiting for the following values detected by the sensors */
        stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
    
    /* The two LEDs behind the robot are off */
        analogWrite(ledBackL,LOW);
        analogWrite(ledBackR,LOW);
    
    /* A delay is added to the code for the robot. It should go step by step, not run continuously */
        //delay(800);
    }else{
      //nothing
          analogWrite(ledFront,0);
    }
    

    
    /* A delay is added to the code for the robot. It should go step by step, not run continuously */
    delay(800);
}


/***************** functions *****************/
void moving(int xMove, int yMove, int xMoveAux, int yMoveAux)
{

  /* Conditions if you can go LEFT */
  if (distanceLEFT > CONTROL_DISTANCE)
  {
    Serial.println("Turn LEFT");
    //index = 0;
    turnLeft(motorLeft1, motorLeft2, motorRight1, motorRight2);   //turn LEFT

    /* Depending on the Step, the robot take next turn */
    switch (Step)
    {
      case north:
        if (mat[xMoveAux + 1][yMoveAux] == SET)
        {
          mat[xMoveAux][yMoveAux] = SET;
        }
        else
        {
          if ((distanceFRONT > CONTROL_DISTANCE) && (mat[xMoveAux][yMoveAux + 1] == SET))
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
        }
        break;

      case west:
        if (mat[xMoveAux][yMoveAux + 1] == SET)
        {
          mat[xMoveAux][yMoveAux] = SET;
        }
        else
        {
          if ((distanceFRONT > CONTROL_DISTANCE) && (mat[xMoveAux - 1][yMoveAux] == SET))
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
        }
        break;

      case south:
        if (mat[xMoveAux - 1][yMoveAux] == SET)
        {
          mat[xMoveAux][yMoveAux] = SET;
        }
        else
        {
          if ((distanceFRONT > CONTROL_DISTANCE) && (mat[xMoveAux][yMoveAux - 1] == SET))
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
        }
        break;

      case east:
        if (mat[xMoveAux][yMoveAux - 1] == SET)
        {
          mat[xMoveAux][yMoveAux] = SET;
        }
        else
        {
          if ((distanceFRONT > CONTROL_DISTANCE) && (mat[xMoveAux + 1][yMoveAux] == SET))
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
        }
        break;

      default:
        break;
    }//end switch(Step)

    if (mat[xMove][yMove] == SET)
    {
      mat[xMove][yMove] = UNSET;
    }
    else
    {
      mat[xMove][yMove] = SET;
    }
  
  /* The robot could turn right or left, so it is not a wrong road */
    wrong_road = 0;
  
  /* Afthe that the robot turn left, he goes one step forword becaouse there is free*/
    goForword(motorLeft1, motorLeft2, motorRight1, motorRight2);   
    goForword2(motorLeft1, motorLeft2, motorRight1, motorRight2);    

  }
  else
  {
    /* Conditions if you can go FORWORD */
    if (distanceFRONT > CONTROL_DISTANCE)
    {   
    //Serial.println("go FORWORD");
    /* The robot goes foeword one step beause is a free place */
    goForword(motorLeft1, motorLeft2, motorRight1, motorRight2);   
    //goForword(motorLeft1, motorLeft2, motorRight1, motorRight2); 
    
    /* Depending on the Step, the robot take next turn */
    switch (Step)
      {
        case north:
          if (mat[xMoveAux][yMoveAux + 1] == SET)
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
          break;

        case west:
          if (mat[xMoveAux - 1][yMoveAux] == SET)
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
          break;

        case south:
          if (mat[xMoveAux][yMoveAux - 1] == SET)
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
          break;

        case east:
          if (mat[xMoveAux + 1][yMoveAux] == SET)
          {
            mat[xMoveAux][yMoveAux] = SET;
          }
          break;
        default:
          break;
      }
      if (mat[xMove][yMove] == SET)
      {
        mat[xMove][yMove] = UNSET;
      }
      else
      {
        mat[xMove][yMove] = SET;
      }
    /* The robot could turn right or left, so it is not a wrong road */
      wrong_road = 0;
    
    }
  /* Conditions if you can go RIGHT and bouth and the two sensors on the right and front detect wall */
    else
    {
      /* Turn Right becouse there is a way in the maze */
      //Serial.println("Turn RIGHT");
      turnRight(motorLeft1, motorLeft2, motorRight1, motorRight2);   

    /* If turnes right it might be a wrong road */
      wrong_road++;
    
    /* If turns two consecutive times in right, means is a worg road. */
      if (wrong_road == CONSECUTIVE_RIGHT_ROTATION)
      {
      /* Reset the position in the matrix */
      mat[xMove][yMove] = UNSET;
      }

//      goForword2(motorLeft1, motorLeft2, motorRight1, motorRight2);   
    }
  }

}
void showMatrix(bool a[MATRIXLEN][MATRIXLEN])
{
  for (int i = 0; i < MATRIXLEN; i++)
  {
    for (int j = 0; j < MATRIXLEN; j++)
    {
      Serial.print(a[i][j]);
      Serial.print(" ");
    }
    Serial.println();
  }
}
int readSensorDist(int echoPin, int trigPin)
{
  long duration;
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(2);
  digitalWrite(trigPin, LOW);

  duration = pulseIn(echoPin, HIGH);
  return (duration * 0.034 / 2); //return distance
}
void printDistance(int distance, char nameSensor)
{
  if (nameSensor == 'F')
    Serial.print("FRONT sensor: ");
  else
    Serial.print("LEFT  sensor: ");
  Serial.print(distance);
  Serial.println(" cm");
}

void turnLeft(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
{
//    digitalWrite(motorLeft1, LOW);
//    digitalWrite(motorLeft2, LOW);
//    digitalWrite(motorRight1, HIGH);
//    digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, LOW);    
    analogWrite(motorLeft2, 130);    
    analogWrite(motorRight1, 230);
    analogWrite(motorRight2, LOW);
    analogWrite(ledBackL,500);
    delay(330);

    stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
}
void turnRight(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
{
//    digitalWrite(motorLeft1, HIGH);
//    digitalWrite(motorLeft2, LOW);
//    digitalWrite(motorRight1, LOW);
//    digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, 230);    
    analogWrite(motorLeft2, LOW);    
    analogWrite(motorRight1, LOW);
    analogWrite(motorRight2, 80);
    analogWrite(ledBackR,500);
    delay(330);
    
    stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
}
void goForword(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
{
//    digitalWrite(motorLeft1, HIGH);
//    digitalWrite(motorLeft2, LOW);
//    digitalWrite(motorRight1, HIGH);
//    digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, 255);    
    analogWrite(motorLeft2, LOW);    
    analogWrite(motorRight1, 255);
    analogWrite(motorRight2, LOW);
    delay(450);
    stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
    analogWrite(motorLeft1, 100);    
    analogWrite(motorLeft2, LOW);
    delay(20);
    stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
}
void goForword2(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
{
//    digitalWrite(motorLeft1, HIGH);
//    digitalWrite(motorLeft2, LOW);
//    digitalWrite(motorRight1, HIGH);
//    digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, 255);    
    analogWrite(motorLeft2, LOW);    
    analogWrite(motorRight1, 250);
    analogWrite(motorRight2, LOW);
    delay(25);
    stopMotors(motorLeft1,motorLeft2,motorRight1,motorRight2);
}
void stopMotors(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
{
//  digitalWrite(motorLeft1, LOW);
//  digitalWrite(motorLeft2, LOW);
//  digitalWrite(motorRight1, LOW);
//  digitalWrite(motorRight2, LOW);
    analogWrite(motorLeft1, LOW);    
    analogWrite(motorLeft2, LOW);    
    analogWrite(motorRight1, LOW);
    analogWrite(motorRight2, LOW);
}
//void stopGoing(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
//{
//  digitalWrite(motorLeft1, LOW);
//  digitalWrite(motorLeft2, LOW);
//  digitalWrite(motorRight1, LOW);
//  digitalWrite(motorRight2, LOW);
//}
//void goBackword(int motorLeft1, int motorLeft2, int motorRight1, int motorRight2)
//{
//  digitalWrite(motorLeft1, LOW);
//  digitalWrite(motorLeft2, HIGH);
//  digitalWrite(motorRight1, LOW);
//  digitalWrite(motorRight2, HIGH);
//}
