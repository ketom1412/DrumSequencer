//Testing Clear Button
const int ClearButton = 4;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ClearButton, INPUT);
}

void loop()
{
    ButtonState = digitalRead(ClearButton);
    Serial.println(ButtonState);
}