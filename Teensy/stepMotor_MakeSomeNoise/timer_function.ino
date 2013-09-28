char str[10];
int m_itChkA = 0;
int m_intv = 0;
unsigned char m_TCNT = 0;

unsigned long m_timer = 0;
unsigned long m_time_diff = 0;

void init8BitTimerB_0(unsigned int intv)
{
  m_intv = 16000000 / intv - 1; 
  m_TCNT = intv;

//  DDRB = 0x40; //pin mode
  
  TCCR0A = 0x00; //OCnx DISCONNECTED, compare match with OCR1A(CTC MODE)
  TCCR0B = 0x01;   //00000001 : CLK/1 PRESCALEAR

  OCR0B = m_TCNT;
  TCNT0 = 0x00;

  TIMSK0 |= 0x04; //COMPB interrupt enable

  sei();
//  Serial.println("16 timer inited");
//  Serial.println(TIMSK1);
}

void stop8BitTimerB_0()
{
  TIMSK0 &= 0x00;
}

void restart8BitTimerB_0()
{
  TIMSK0 |= 0x04;
}

ISR(TIMER0_COMPB_vect)
{
//  Serial.println("16bit timer vector excuted");

//  if(mTimer3Flag == 0) stop16BitTimerA_3();
  
  if(m_itChkA == 1){
  stop8BitTimerB_0();
    
    return;
  }
  
//  m_itChkA = 1;

// *DAC time test code*

Serial.println("timerFunc excueted");
      m_timer = micros();        
//  dacfunc_VCA();
      m_time_diff = micros() - m_timer;
      sprintf(str, "%lu, dac running time: ", m_time_diff);
      Serial.println(str);
  
//  m_itChkA = 0;
  stop8BitTimerB_0();

}



