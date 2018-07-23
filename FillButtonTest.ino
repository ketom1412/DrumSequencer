//Testing Fill Button
const int FillButton = 5;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(FillButton, INPUT);
}

void loop()
{
    ButtonState = digitalRead(FillButton);
    Serial.println(ButtonState);
}