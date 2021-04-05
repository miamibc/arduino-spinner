/*
 * Spinner game with 1 button and 7-LEDs screen
 *
 * @package arduino-spinner
 * @author Sergei Miami <miami@blackcrystal.net>
 */
 
int PIN_DOT = 7;
int PIN_CENTER = 3;
int PIN_CIRCLE[6] = {9,8,6,5,4,2};
int PIN_BUTTON = 13;

int prev = PIN_CIRCLE[0];
double live = 1000;

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BUTTON, INPUT_PULLUP );
  pinMode(PIN_DOT, OUTPUT);
  pinMode(PIN_CENTER, OUTPUT);
  for (int i = 0; i < 6; i++) {
    pinMode(PIN_CIRCLE[i], OUTPUT);
  }
}


void loop()
{

  for (int i = 0; i < 6; i++) {
    
    digitalWrite(prev, LOW);
    prev = PIN_CIRCLE[i];

    
    digitalWrite(prev, HIGH);

    double score = the_delay(); 
    if (score == 0)
    {
      // nothing here      
      live = live - 5;
    }
    else if ((prev == 5 || prev == 9))
    {      
      live += live / score + 30;
    }
    else
    {
      live -= live / score + 30;
    }

    
    Serial.println( live, 1 );
      
    if (live <= 0) { the_end(); break; }
    
  }

  live = live * 8 / 9;
  if (live <= 0) { the_end(); }
  
}

int the_delay()
{

  unsigned long start = millis();   // start delay

  int result = 0;
    
  while(millis() - start <= live)
  {
      int pressed = !digitalRead(PIN_BUTTON);      
      digitalWrite(PIN_CENTER, pressed);
      // Serial.print( pressed );
      result+= pressed;
      delay(10);    
  }

  return result;
}

void the_end()
{  
  digitalWrite(PIN_CENTER, LOW);
  digitalWrite(PIN_DOT, HIGH);
  delay(10000);
     
  digitalWrite(PIN_DOT, LOW);
  
  live = 1000;   
}
