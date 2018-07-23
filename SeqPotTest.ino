//Testing Seq Pot
const int SeqPot = 15;
int PotVal = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(SeqPot, INPUT);
}

void loop()
{
    PotVal = analogRead(SeqPot);
    Serial.println(PotVal);
}