const int VAL_PROBE = 0;
const int MOISTURE_LEVEL = 250;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:

}

void LedState(int state)
{
  digitalWrite(13, state);
}

void loop() {
  if(analogRead(VAL_PROBE) > MOISTURE_LEVEL)
  {
    LedState(HIGH);
  }
  else
  {
    LedState(LOW);
  }
  delay(50);
  // put your main code here, to run repeatedly:

  int nums[10];

  for (int i=0; i<10; i++)
  {
    nums[i] = analogRead(VAL_PROBE);
    delay(100);
  }

  int sum=0;
  int avg=0;

  for (int i=0; i<10; i++)
  {
    sum+=nums[i];
  }

  avg=sum/10;
  Serial.println(avg);

}