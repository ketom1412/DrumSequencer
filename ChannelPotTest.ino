//Testing Channel Pot
const int ChannelPot = 14;
int PotVal = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ChannelPot, INPUT);
}

void loop()
{
    PotVal = analogRead(ChannelPot);
    Serial.println(PotVal);
}