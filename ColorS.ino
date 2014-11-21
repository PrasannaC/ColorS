  
#define VCC  12
#define OUT  7
#define S2   5
#define S3   6
#define S0   3
#define S1   4

#define  Filters_R  0
#define  Filters_G  1
#define  Filters_B  2

long count = 0;
int counter = 0;
int G_flag = 1;
int RGB = 0;
float scaleFactor[] = {2.32, 2, 0.7 };

void setup()
{
  pinMode(OUT, INPUT);
  pinMode(S2, OUTPUT);
  pinMode(S3, OUTPUT);
  pinMode(S0, OUTPUT);
  pinMode(S1, OUTPUT);
 
  digitalWrite(S2, HIGH);
  digitalWrite(S3, LOW);
  digitalWrite(S0, LOW);  // OUTPUT FREQUENCY SCALING 2%
  digitalWrite(S1, HIGH);


  Serial.begin(9600);
  Serial.println("Starting...");
  
  digitalWrite(VCC, HIGH);
  

}

void loop()
{
  
  float value;
  
  Serial.println("loop");
  
  digitalWrite(VCC, HIGH);
  delay(100);
  
  for(int i=0; i<3; i++)
  {
    RGB=i;
    Select_Filters(i);
    float sf=0;
    count=0;
    int lastDigitalRead = HIGH;
    for(int j=0; j<25000; j++)
    {
      int digitalReadValue = digitalRead(OUT);
      if (lastDigitalRead == LOW && digitalReadValue == HIGH) 
      {
        count++;
      }
   
      lastDigitalRead = digitalReadValue;
    }
      sf = 255.0/count; 
    value = sf*count;
    
    Serial.print("value: ");
    Serial.println(value);
   // Serial.print("counter ");
    //Serial.println(counter);
    counter=0;
    count=0;
  }
  
  digitalWrite(VCC, LOW);
  digitalWrite(S2, LOW);
  digitalWrite(S3, LOW);
  digitalWrite(S0, LOW);
  digitalWrite(S1, LOW);  
  
  delay(500);
  digitalWrite(S1, HIGH);
}


void Select_Filters(int RGB)
{
  switch(RGB)
  {
    case Filters_R:          //Red
    digitalWrite(S2, LOW);    
    digitalWrite(S3, LOW);
    Serial.println("Red color");
    break;
    
    case Filters_G:          //Green
    digitalWrite(S2, HIGH);    
    digitalWrite(S3, HIGH);
    Serial.println("Green color");
    break;
    
    case Filters_B:          //Blue
    digitalWrite(S2, LOW);    
    digitalWrite(S3, HIGH);
    Serial.println("Blue color");
    break;
    
    default:                  //Clear(no filter)
    digitalWrite(S2, HIGH);    
    digitalWrite(S3, LOW);
    Serial.println("-----no filter");
    break;
  }
}


