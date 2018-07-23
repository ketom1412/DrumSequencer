//Testing Reset Button
const int ResetButton = 6;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ResetButton, INPUT);
}

void loop()
{
    ButtonState = digitalRead(ResetButton);
    Serial.println(ButtonState);
}