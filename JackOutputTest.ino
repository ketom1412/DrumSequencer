//Testing Output Jacks 1-6
const int ChannelPot = 14;
const int BigButton = 19;
const int Out1 = 8;
const int Out2 = 9;
const int Out3 = 10;
const int Out4 = 11;
const int Out5 = 12;
const int Out6 = 13;

int ChannelKnobValue = 0;
int ChannelState1 = 0;
int ChannelState2 = 0;
int ChannelState3 = 0;
int ChannelState4 = 0;
int ChannelState5 = 0;
int ChannelState6 = 0;
int BigButtonState = 0;

void setup()
{
    Serial.begin(9600);
    pinMode(ChannelPot, INPUT);
    pinMode(BigButton, INPUT);

    pinMode(Out1, OUTPUT);
    pinMode(Out2, OUTPUT);
    pinMode(Out3, OUTPUT);
    pinMode(Out4, OUTPUT);
    pinMode(Out5, OUTPUT);
    pinMode(Out6, OUTPUT);
}

void loop()
{
    ChannelKnobValue = analogRead(ChannelPot);
    Serial.println(PotVal);
    if(0 < ChannelKnobValue && ChannelKnobValue < 200)
    {
        ChannelState1 = HIGH;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(200 < ChannelKnobValue && ChannelKnobValue < 400)
    {
        ChannelState1 = LOW;
        ChannelState2 = HIGH;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(400 < ChannelKnobValue && ChannelKnobValue < 600)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = HIGH;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(600 < ChannelKnobValue && ChannelKnobValue < 800)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = HIGH;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(800 < ChannelKnobValue && ChannelKnobValue < 1000)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = HIGH;
        ChannelState6 = LOW;
    }
    else if(1000 < ChannelKnobValue)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = HIGH;
    }

    BigButtonState = digitalRead(BigButton);
    if(BigButtonState == HIGH)
    {
        digitalWrite(Out1, ChannelState1);
        digitalWrite(Out2, ChannelState2);
        digitalWrite(Out3, ChannelState3);
        digitalWrite(Out4, ChannelState4);
        digitalWrite(Out5, ChannelState5);
        digitalWrite(Out6, ChannelState6);

        delay(50);

        digitalWrite(Out1, LOW);
        digitalWrite(Out2, LOW);
        digitalWrite(Out3, LOW);
        digitalWrite(Out4, LOW);
        digitalWrite(Out5, LOW);
        digitalWrite(Out6, LOW);
    }
}