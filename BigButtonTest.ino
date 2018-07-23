//Testing Big Button
const int BigButton = 19;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(BigButton, INPUT);
}

void loop()
{
    ButtonState = digitalRead(BigButton);
    Serial.println(ButtonState);
}