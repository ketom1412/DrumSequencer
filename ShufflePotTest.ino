//Testing Channel Pot
const int ShufflePot = 14;
int ShuffleVal = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ShufflePot, INPUT);
}

void loop()
{
    ShuffleVal = analogRead(ShufflePot);
    Serial.println(ShuffleVal);
}