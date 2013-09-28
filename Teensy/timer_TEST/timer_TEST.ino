#include <avr/interrupt.h>
#include <avr/io.h>


char str[10];
boolean m_timeCheck = false;

unsigned long m_time = 0;
unsigned long m_time_diff = 0;

int count = 0;

void setup(){
  Serial.begin(9600);
  m_timeCheck = false;  
  
//  m_timer = micros();
  init8BitTimerB_0(0);

}

void loop(){
  
//  if(count % 100 == 0){
//    Serial.println((count / 100));
//    Serial.println("hi");
//    stop8BitTimerB_0();
//  }
  
  timer_delay();
//  delayMicroseconds(100);

}

void timer_delay()
{
  if((count % 100) == 0){
    if(m_timeCheck == false){
      m_time_diff = micros() - m_time;
      Serial.println(m_time_diff);      
      m_time = micros();    

      Serial.print("hi");
      Serial.println((count / 100));
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
  TCCR0B = 0x05;
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
//  Serial.println("ISR!");
//  m_timer = micros();        
//  m_time_diff = micros() - m_timer;

//  sprintf(str, "%lu, dac running time: ", m_time_diff);
//  Serial.println(str);
  

  count++;
//  TIMSK0 &= 0x00;


}



