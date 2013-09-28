void timer_delay(int ht)
{
  if((count % ht) == 0){
    if(m_timeCheck == false){
      
      if(hold_B_toggle) hold_B_toggle = false;
      else hold_B_toggle = true;
//      hold_B_toggle != hold_B_toggle;

//      Serial.print("hold_B_toggle : ");
//      Serial.println(hold_B_toggle);
//      m_time_diff = micros() - m_time;
//      Serial.println(m_time_diff);      
//      m_time = micros();    
//      Serial.print("hi");
//      Serial.println((count / 100));

      m_timeCheck = true;
      count = 0;
    }
  }else{
    m_timeCheck = false;
  }
}


void init8BitTimerB_0(unsigned int intv)
{ 
  TCCR0A = 0x00; //OCnx DISCONNECTED, compare match with OCR1A(CTC MODE)
  TCCR0B = 0x02;
  TCNT0 = intv;
  
//  OCR0B = intv;

  TIMSK0 |= 0x04; //COMPB interrupt enable

  sei();
  
  Serial.println("16 timer inited");
  Serial.println(TIMSK0);
}

void stop8BitTimerB_0()
{
  TIMSK0 &= 0x00;
}

void restart8BitTimerB_0()
{
  TIMSK0 = TIMSK0 | 0x04;
}

ISR(TIMER0_COMPB_vect)
{
//  Serial.println("ISR");
//  m_timer = micros();        
//  m_time_diff = micros() - m_timer;

//  sprintf(str, "%lu, dac running time: ", m_time_diff);
//  Serial.println(str);
  

  count++;
//  Serial.print("count: ");  
//  Serial.println(count);

  timer_delay(rate_B);
//  TIMSK0 &= 0x00;


}



