//Test for interrupt
int buttonState = 0
const int interruptPin = 2;

void setup()
{
    Serial.begin(9600);
    attachInterrupt(digitalPinToInterrupt(interruptPin), isr, RISING);
}

void loop()
{
    if(buttonState == HIGH)
    {
        Serial.println("HIGH");
        buttonState = LOW;
    }
    else
    {
        Serial.println("LOW")
    }
}

void isr()
{
    buttonState = HIGH;
}