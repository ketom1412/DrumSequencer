//Honestly I dont know why this is here
#define TOLERANCE 0

//Also not sure what this is, prob has to do with interrupts
volatile int buttonState = LOW;

//Const pin values;
//NOTE CHECK ALL OF THESE WITH SCHEMATIC
//This pin is the big button, very obvious
const int BigButton = 19;
//This pin is the potentiometer that determines channel
const int ChannelPot = 14;
//This pin is the potentiometer that determines length of sequence
const int SeqLengthPot = 15; 
//This pin is the potentiometer that determines shuffle sequence
//Whatever that means
const int ShufflePot = 16;
//This pin is the reset button
const int ResetButton = 6;
//This pin is the delete button
const int DeleteButton = 7;
//This pin is the clear button
const int ClearButton = 4;
//This pin is for the BankLED, for visuals only
const int BankLED = 18;
//This pin is for the bank button
const int BankButton = 3;
//This pin is for the fill button
const int FillButton = 5;
//This pin is for the clckIn button
const int clckButton = 2;
//These pins define the mono mount outputs
const int Out1 = 8;
const int Out2 = 9;
const int Out3 = 10;
const int Out4 = 11;
const int Out5 = 12;
const int Out6 = 13;

//Variables to switch between the two channels of each mount
int BankArrayShift1 = 0;
int BankArrayShift2 = 0;
int BankArrayShift3 = 0;
int BankArrayShift4 = 0;
int BankArrayShift5 = 0;
int BankArrayShift6 = 0;

//Variables used to go through each sequence array at some row
int BankPush1 = 0;
int BankPush2 = 0;
int BankPush3 = 0;
int BankPush4 = 0;
int BankPush5 = 0;
int BankPush6 = 0;

//Variables used to run along the sequence based on shuffle val
int OldShuffleVal = 0;
int NewShuffleVal1 = 0;
int NewShuffleVal2 = 0;
int NewShuffleVal3 = 0;
int NewShuffleVal4 = 0;
int NewShuffleVal5 = 0;
int NewShuffleVal6 = 0;

//ChannelState# is the state of the 1-6 knob channels
//The channel is determined by the resistor values of
//of the potentiometer in the middle
//Tied to ChannelPot
int ChannelState1 = LOW;
int ChannelState2 = LOW;
int ChannelState3 = LOW;
int ChannelState4 = LOW;
int ChannelState5 = LOW;
int ChannelState6 = LOW;
int ChannelKnobValue = -1; //Initial value should not exist

//Steps and StepLength determine how long sequence
//of music is
//Tied to SeqLengthPot
int StepLength = 0;
int Steps = 0;

//ShuffleVal and ShuffleNum determine the Pot value
//of ShufflePot and the shuffle value
//Tied to ShufflePot
int ShuffleNum = 0;
int ShuffleVal = 0;

//Not sure what these variable does yet
//obviously has something to do with looper
int looper = 0;
int ClockKeep = 0;

//Values used to store state of Fill Button 
//as well as the states of each channel
int FillButtonState = 0;
int Fill1 = 0;
int Fill2 = 0;
int Fill3 = 0;
int Fill4 = 0;
int Fill5 = 0;
int Fill6 = 0;

//Values used to keep track of index to store in the sequence array
int Channel = 0;
int BankRecord = 0;

//Values used to keep track of the clear state
int ClearState = 0;

//Values used to store the time, pretty sure it has to do with the clock
long time = 0;
long debounce = 150;

//Values for the buttons are recorded with these variables
int BigButtonState = 0; //Records if BigButton is high or low
int PrevBigButtonState = 0; //Used for checking if BigButton has changed states
int DeleteButtonState = 0; //Records if Delete is high or low
int PrevDeleteButtonState = 0; //Used for checking Delete has changed states
int ClearButtonState = 0; //Records if Clear is high or low
int ResetButtonState = 0; //Records if Reset is high or low
int PrevResetButtonState = 0; //Used for checking if Clear has changed states

//GOTTA FIGURE OUT WHAT THESE ARRAYS ARE FOR
int ButtonBankSelectState[6];
int BankState[6] = {LOW, LOW, LOW, LOW, LOW, LOW};
int BankPrevious[6] = {HIGH, HIGH, HIGH, HIGH, HIGH, HIGH};
int BankArrayNumber = 0; //Used for visuals only

//FILL OUT SINCE IDK WHAT THIS IS
//PROBABLY STORES YOUR SOUND BITES
//FIGURED IT OUT HOLY SHIT
int Sequence[12][42] = {
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

void setup()
{
    Serial.begin(9600);
    //Set pins to input or output
    pinMode(ChannelPot, INPUT);
    pinMode(SeqLengthPot, INPUT);
    pinMode(ShufflePot, INPUT);
    pinMode(ClearButton, INPUT);
    pinMode(DeleteButton, INPUT);
    pinMode(ResetButton, INPUT);
    pinMode(BigButton, INPUT);
    pinMode(BankButton, INPUT);
    pinMode(FillButton, INPUT);
    pinMode(clckButton, INPUT);

    pinMode(BankLED, OUTPUT);
    pinMode(Out1, OUTPUT);
    pinMode(Out2, OUTPUT);
    pinMode(Out3, OUTPUT);
    pinMode(Out4, OUTPUT);
    pinMode(Out5, OUTPUT);
    pinMode(Out6, OUTPUT);

    //This section reads in the initial value of the
    //potentiometer that determines how long your sound
    //sequence will be
    DetermineStep();
    //End of inital sequence length section

    //This should create an interrupt based on the clckButton
    attachInterrupt(digitalPinToInterrupt(clckButton), isr, RISING);
}

void loop()
{
    //Read in the pin values at the beginning of each loop
    BigButtonState = digitalRead(BigButton);
    DeleteButtonState = digitalRead(DeleteButton);
    ResetButtonState = digitalRead(ResetButton);
    ClearButtonState = digitalRead(ClearButton);
    FillButtonState = digitalRead(FillButton);

    ButtonBankSelectState[BankArrayNumber] = digitalRead(BankButton);

    if(buttonState == HIGH)
    {
        //This section writes to each mono jack output only if their 
        //corresponding fill value is 1 and the value in the sequence is
        //also 1, each write has two channels since BankArrayShift#
        //is either 0 or 3, BankPush# starts at 0 and newShuffleVal#
        //is a number between 0 and 8
        //Row 0 and 3 for sequence
        WriteToMono();
        //End of Write to monojack section
    }
    else
    {
        //Not sure why he does this, since ClockKeep and looper
        //wouldn't increment anyways, maybe take this out later
        looper = looper;
        ClockKeep = ClockKeep;
    }

    //This section records values into your sequencer by determining
    //if the big button has been pressed, and based on the channel
    //which is based on the middle knob, you write 1 to the sequencer
    RecordSeq();
    //End of recording section

    //THIS SECTION IS JUST FOR VISUALS HAS LITERALLY NO TECHNICAL PROPERTIES
    SettingBanks();
    //END OF VISUAL SECTION WHY DO WE NEED THIS

    //This section switches the states of each channel based on the bank state
    //It changes only when the elapsed time between the last change is greater 
    //then the debounce value
    SwitchStates();
    //End of BankState change section

    //This section reads in the pot value of the 
    //shuffle pot and determines how much to shuffle
    //the sequence
    DetermineShuffle();
    //End of Shuffle reading section

    //Not really sure what this section does yet
    //Prob has to do with how you are shuffling your sequence
    SettingShuffle();
    //End of section

    //This section reads in the value of the potentiometer
    //That determines which channel is being used, there are 6 channels
    DetermineChannel();
    //End of channel select section

    //This section sets the variables that will access the 
    //sequence array based on the state of Bank and the state
    //of the channel 
    VariableSet();
    //End of variable setting for the sequence section

    //This section happens when you press the clear button
    //It clears out the row and sets them all to zero
    //Row is based on the channel and bank state
    ClearSeq();
    //End of clear button state

    //This section determines which channel will output from the
    //Mono jacks, since truth table for OR is true for all inputs except
    //when both are 0
    ChangeFill();
    //End of Fill section

    //From my understanding of this, you delete a part of your sequence here
    if(DeleteButtonState == HIGH)
    {
        Sequence[Channel + BankRecord][looper + 1] = 0;
    }
    //End of Delete Section

    //Reset button allows you to restart your sequence
    //by setting the beginning values back down to 0
    MakeReset();
    //End of reset section

    //This section continuously reads in the value of the
    //potentiometer that determines how long your sound
    //sequence will be
    DetermineStep();
    //End of sequence reading section

    //This section resets all the bank values
    //if their values are over steps
    ResetBank();
    //End of section

    //Keep track of the previous button states
    PrevBigButtonState = BigButtonState;
    PrevResetButtonState = ResetButtonState;
    PrevDeleteButtonState = DeleteButtonState;
    BankPrevious[BankArrayNumber] = ButtonBankSelectState[BankArrayNumber];
}

void DetermineStep()
{
    StepLength = analogRead(SeqLengthPot);
    if(0 <= StepLength && StepLength < 200)
    {
        Steps = 2;
    }
    else if(200 <= StepLength && StepLength < 500)
    {
        Steps = 4;
    }
    else if(500 <= StepLength && StepLength < 800)
    {
        Steps = 8;
    }
    else if(800 <= StepLength && StepLength < 1000)
    {
        Steps = 16;
    }
    else if(1000 <= StepLength)
    {
        Steps = 32;
    }
}

void isr()
{
    buttonState = HIGH;
}

void WriteToMono()
{
    digitalWrite(Out1, Sequence[0 + BankArrayShift1][BankPush1 + NewShuffleVal1] || Fill1);
    //Row 1 and 4 for sequence
    digitalWrite(Out2, Sequence[1 + BankArrayShift2][BankPush2 + NewShuffleVal2] || Fill2);
    //Row 2 and 5 for sequence
    digitalWrite(Out3, Sequence[2 + BankArrayShift3][BankPush3 + NewShuffleVal3] || Fill3);
    //Row 6 and 9 for sequence
    digitalWrite(Out4, Sequence[6 + BankArrayShift4][BankPush4 + NewShuffleVal4] || Fill4);
    //Row 7 and 10 for sequence
    digitalWrite(Out5, Sequence[7 + BankArrayShift5][BankPush5 + NewShuffleVal5] || Fill5);
    //Row 8 and 11 for sequence
    digitalWrite(Out6, Sequence[8 + BankArrayShift6][BankPush6 + NewShuffleVal6] || Fill6);
        
    delay(10);

    //Set all mounts back down to low
    digitalWrite(Out1, LOW);
    digitalWrite(Out2, LOW);
    digitalWrite(Out3, LOW);
    digitalWrite(Out4, LOW);
    digitalWrite(Out5, LOW);
    digitalWrite(Out6, LOW);
    //End of making sound section

    //Here we increment each value that controls where we are 
    //in the sequence matrix
    looper = looper + 1;
    BankPush1 = BankPush1 + 1;
    BankPush2 = BankPush2 + 1;
    BankPush3 = BankPush3 + 1;
    BankPush4 = BankPush4 + 1;
    BankPush5 = BankPush5 + 1;
    BankPush6 = BankPush6 + 1;
    ClockKeep = ClockKeep + 1;

    //So we don't always go into this part of the conditional
    //Only go here when BigButton is pressed?
    buttonState = LOW;
}

void RecordSeq()
{
    if((BigButtonState != PrevBigButtonState) && (BigButtonState == HIGH))
    {
        if(Channel == 0) //Row 0 to 3
        {
            Sequence[Channel + BankRecord][BankPush1 + NewShuffleVal1 + 1] = 1;
        }
        else if(Channel == 1) //Row 1 to 4
        {
            Sequence[Channel + BankRecord][BankPush2 + NewShuffleVal2 + 1] = 1;
        }
        else if(Channel == 2) //Row 2 to 5
        {
            Sequence[Channel + BankRecord][BankPush3 + NewShuffleVal3 + 1] = 1;
        }
        else if(Channel == 6) //Row 6 to 9
        {
            Sequence[Channel + BankRecord][BankPush4 + NewShuffleVal4 + 1] = 1;
        }
        else if(Channel == 7) //Row 7 to 10
        {
            Sequence[Channel + BankRecord][BankPush5 + NewShuffleVal5 + 1] = 1;
        }
        else if(Channel == 8) //Row 8 to 11
        {
            Sequence[Channel + BankRecord][BankPush6 + NewShuffleVal6 + 1] = 1;
        }
        else
        {
            //DO NOTHING
        }
        delay(5);
    }
}

void SettingBanks()
{
    if(ClockKeep%4 == 1)
    {
        if(BankRecord == 0)
        {
            digitalWrite(BankLED, HIGH);
        }
        else if(BankRecord == 3)
        {
            digitalWrite(BankLED, LOW);
        }
    }
    else
    {
        digitalWrite(BankLED, BankState[BankArrayNumber]);
    }
}

void SwitchStates()
{
    if((ButtonBankSelectState[BankArrayNumber]) == HIGH && (BankPrevious[BankArrayNumber] == LOW) && (millis() - time > debounce))
    {
        if(BankState[BankArrayNumber] == HIGH)
        {
            BankState[BankArrayNumber] = LOW;
        }
        else
        {
            BankState[BankArrayNumber] = HIGH;
            time = millis();
        }
    }
}

void DetermineShuffle()
{
    ShuffleVal = analogRead(ShufflePot);
    if(0 <= ShuffleVal && ShuffleVal < 127)
    {
        ShuffleNum = 0;
    }
    else if(127 <= ShuffleVal && ShuffleVal < 254)
    {
        ShuffleNum = 1;
    }
    else if(254 <= ShuffleVal && ShuffleVal < 383)
    {
        ShuffleNum = 2;
    }
    else if(383 <= ShuffleVal && ShuffleVal < 511)
    {
        ShuffleNum = 3;
    }
    else if(511 <= ShuffleVal && ShuffleVal < 638)
    {
        ShuffleNum = 4;
    }
    else if(638 <= ShuffleVal && ShuffleVal < 767)
    {
        ShuffleNum = 5;
    }
    else if(767 <= ShuffleVal && ShuffleVal < 895)
    {
        ShuffleNum = 6;
    }
    else if(895 <= ShuffleVal && ShuffleVal < 1000)
    {
        ShuffleNum = 7;
    }
    else if(1000 <= ShuffleVal)
    {
        ShuffleNum = 8;
    }
}

void SettingShuffle()
{
    int diff = abs(ShuffleNum - OldShuffleVal);

    if(diff > TOLERANCE)
    {
        if(ChannelState1 == HIGH)
        {
            NewShuffleVal1 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
        else if(ChannelState2 == HIGH)
        {
            NewShuffleVal2 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
        else if(ChannelState3 == HIGH)
        {
            NewShuffleVal3 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
        else if(ChannelState4 == HIGH)
        {
            NewShuffleVal4 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
        else if(ChannelState5 == HIGH)
        {
            NewShuffleVal5 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
        else if(ChannelState6 == HIGH)
        {
            NewShuffleVal6 = ShuffleNum;
            OldShuffleVal = ShuffleNum;
        }
    }
}

void DetermineChannel()
{
    ChannelKnobValue = analogRead(ChannelPot);

    if(0 <= ChannelKnobValue && ChannelKnobValue < 200)
    {
        ChannelState1 = HIGH;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(200 <= ChannelKnobValue && ChannelKnobValue < 400)
    {
        ChannelState1 = LOW;
        ChannelState2 = HIGH;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(400 <= ChannelKnobValue && ChannelKnobValue < 600)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = HIGH;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(600 <= ChannelKnobValue && ChannelKnobValue < 800)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = HIGH;
        ChannelState5 = LOW;
        ChannelState6 = LOW;
    }
    else if(800 <= ChannelKnobValue && ChannelKnobValue < 1000)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = HIGH;
        ChannelState6 = LOW;
    }
    else if(1000 <= ChannelKnobValue)
    {
        ChannelState1 = LOW;
        ChannelState2 = LOW;
        ChannelState3 = LOW;
        ChannelState4 = LOW;
        ChannelState5 = LOW;
        ChannelState6 = HIGH;
    }
}

void VariableSet()
{
    if((BankState[0] == LOW) && (ChannelState1 == HIGH))
    {
        Channel = 0;
        BankArrayNumber = 0;
        ClearState = 0;
        BankArrayShift1 = 0;
        BankRecord = 0;
    }
    else if((BankState[1] == LOW) && (ChannelState2 == HIGH))
    {
        Channel = 1;
        BankArrayNumber = 1;
        ClearState = 1;
        BankArrayShift2 = 0;
        BankRecord = 0;
    }
    else if((BankState[2] == LOW) && (ChannelState3 == HIGH))
    {
        Channel = 2;
        BankArrayNumber = 2;
        ClearState = 2;
        BankArrayShift3 = 0;
        BankRecord = 0;
    }
    else if((BankState[3] == LOW) && (ChannelState4 == HIGH))
    {
        Channel = 6;
        BankArrayNumber = 3;
        ClearState = 6;
        BankArrayShift4 = 0;
        BankRecord = 0;
    }
    else if((BankState[4] == LOW) && (ChannelState5 == HIGH))
    {
        Channel = 7;
        BankArrayNumber = 4;
        ClearState = 7;
        BankArrayShift5 = 0;
        BankRecord = 0;
    }
    else if((BankState[5] == LOW) && (ChannelState6 == HIGH))
    {
        Channel = 8;
        BankArrayNumber = 5;
        ClearState = 8;
        BankArrayShift6 = 0;
        BankRecord = 0;
    }
    else if((BankState[0] == HIGH) && (ChannelState1 == HIGH))
    {
        Channel = 0;
        BankArrayNumber = 0;
        ClearState = 0;
        BankArrayShift1 = 3;
        BankRecord = 3;
    }
    else if((BankState[1] == HIGH) && (ChannelState2 == HIGH))
    {
        Channel = 1;
        BankArrayNumber = 1;
        ClearState = 1;
        BankArrayShift2 = 3;
        BankRecord = 3;
    }
    else if((BankState[2] == HIGH) && (ChannelState3 == HIGH))
    {
        Channel = 2;
        BankArrayNumber = 2;
        ClearState = 2;
        BankArrayShift3 = 3;
        BankRecord = 3;
    }
    else if((BankState[3] == HIGH) && (ChannelState4 == HIGH))
    {
        Channel = 6;
        BankArrayNumber = 3;
        ClearState = 6;
        BankArrayShift4 = 3;
        BankRecord = 3;
    }
    else if((BankState[4] == HIGH) && (ChannelState5 == HIGH))
    {
        Channel = 7;
        BankArrayNumber = 4;
        ClearState = 7;
        BankArrayShift5 = 3;
        BankRecord = 3;
    }
    else if((BankState[5] == HIGH) && (ChannelState6 == HIGH))
    {
        Channel = 8;
        BankArrayNumber = 5;
        ClearState = 8;
        BankArrayShift6 = 3;
        BankRecord = 3;
    }
}

void ClearSeq()
{
    if(ClearButtonState == HIGH)
    {
        for(int i = 0; i < 41; i++)
        {
            Sequence[ClearState + BankRecord][i] = 0;
        }
    }
}

void ChangeFill()
{
    if(FillButtonState == HIGH)
    {
        if(Channel == 0)
        {
            Fill1 = 1;
            Fill2 = 0;
            Fill3 = 0;
            Fill4 = 0;
            Fill5 = 0;
            Fill6 = 0;
        }
        else if(Channel == 1)
        {
            Fill1 = 0;
            Fill2 = 1;
            Fill3 = 0;
            Fill4 = 0;
            Fill5 = 0;
            Fill6 = 0;
        }
        else if(Channel == 2)
        {
            Fill1 = 0;
            Fill2 = 0;
            Fill3 = 1;
            Fill4 = 0;
            Fill5 = 0;
            Fill6 = 0;
        }
        else if(Channel == 6)
        {
            Fill1 = 0;
            Fill2 = 0;
            Fill3 = 0;
            Fill4 = 1;
            Fill5 = 0;
            Fill6 = 0;
        }
        else if(Channel == 7)
        {
            Fill1 = 0;
            Fill2 = 0;
            Fill3 = 0;
            Fill4 = 0;
            Fill5 = 1;
            Fill6 = 0;
        }
        else if(Channel == 8)
        {
            Fill1 = 0;
            Fill2 = 0;
            Fill3 = 0;
            Fill4 = 0;
            Fill5 = 0;
            Fill6 = 1;
        }
    }
    else if(FillButtonState == LOW)
    {
        Fill1 = 0;
        Fill2 = 0;
        Fill3 = 0;
        Fill4 = 0;
        Fill5 = 0;
        Fill6 = 0;
    }
}

void MakeReset()
{
    if(ResetButtonState != PrevResetButtonState)
    {
        if(ResetButtonState == HIGH)
        {
            looper = 0;
            ClockKeep = 0;
            BankPush1 = 0;
            BankPush2 = 0;
            BankPush3 = 0;
            BankPush4 = 0;
            BankPush5 = 0;
            BankPush6 = 0;
        }
    }
}

void ResetBank()
{
    if(looper >= Steps)
    {
        looper = 0;
    }
    if(ClockKeep >= 32)
    {
        looper = 0;
        ClockKeep = 0;
    }

    if((BankPush1 + NewShuffleVal1) >= Steps)
    {
        BankPush1 = 0;
    }
    if((BankPush2 + NewShuffleVal2) >= Steps)
    {
        BankPush2 = 0;
    }
    if((BankPush3 + NewShuffleVal3) >= Steps)
    {
        BankPush3 = 0;
    }
    if((BankPush4 + NewShuffleVal4) >= Steps)
    {
        BankPush4 = 0;
    }
    if((BankPush5 + NewShuffleVal5) >= Steps)
    {
        BankPush5 = 0;
    }
    if((BankPush6 + NewShuffleVal6) >= Steps)
    {
        BankPush6 = 0;
    }
}
