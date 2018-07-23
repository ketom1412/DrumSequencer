//Testing Delete Button
const int DeleteButton = 7;
int ButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(DeleteButton, INPUT);
}

void loop()
{
    ButtonState = digitalRead(DeleteButton);
    Serial.println(ButtonState);
}