
#define BITSPERCHAR 8

int manchesterSenderLed = 22;

/* UART FSM States */
typedef enum{
  IDLE = 0U,
  START,
  BYTE,
  PARITY,
  STOP,
} UART_State_t;

/* FSM variables */
UART_State_t txState = IDLE; // State register
unsigned char txBitn; // Number of sent bits
unsigned char txData; // Current data register
unsigned char txSym = 1; // Bit to transmit
unsigned char txStart = 0; // 1 if UART is sending data, 0 if idle
unsigned char parity = 0;
unsigned char flag = 1;
/* FSM state transition */
void uart_state_machine()
{
 switch(txState)
 {
 case START:
 if(flag){
 txSym = 1;
 }
 else{
 txSym = 0;
 txState = BYTE;
 }
 flag ^= 1;
 txBitn = 0;
 break;
 case BYTE:
 txSym = (txData & 0x01);
 if(flag) {
 txData = (txData & 0xfe) | (txSym^1);
 parity ^= txSym;
 }
 else {
 txData = txData >> 1;
 txBitn++;
 txState = txBitn < BITSPERCHAR ? BYTE : PARITY;
 }
 txSym = !txSym;
 flag ^= 1;
 break;
 case PARITY:
 if(!flag){
 txState = STOP;
 }
 txSym = parity^flag;
 flag ^= 1;
 break;
 case STOP:
 txData = 0;
 if(!flag){
 txState = IDLE;
 }
 txSym = 1^flag;
 flag ^= 1;
 txStart = 0;
 break;
 case IDLE:
 txSym = flag^1;
 flag ^= 1;
 if (txStart != 0 && flag){
 txState = START;
 }
 break;
 default:
 break;
 }
}
void TC0_Handler() {
 TC_GetStatus(TC0,0);
 digitalWrite(manchesterSenderLed, txSym);
 uart_state_machine();
}

void setupManchesterSender()
{
 pmc_set_writeprotect(false);
 pmc_enable_periph_clk(ID_TC0);
 TC_Configure(TC0, 0, TC_CMR_WAVE | TC_CMR_WAVSEL_UP_RC | TC_CMR_TCCLKS_TIMER_CLOCK1);
 unsigned int clk = VARIANT_MCK / 2/ (2*MANCHESTER_BAUD);
 TC_SetRC(TC0,0,clk);
 TC_Start(TC0,0);
 TC0->TC_CHANNEL[0].TC_IER = TC_IER_CPCS;
 NVIC_EnableIRQ(TC0_IRQn);
 pinMode(manchesterSenderLed, OUTPUT);

 Serial1.begin(MANCHESTER_BAUD, SERIAL_8E1);
 USART0->US_MR |= US_MR_MAN | // Enable Manchester decoder
 US_MR_MODSYNC | // Start bit is 1 to 0 transition
 US_MR_ONEBIT; // One bit start
 USART0->US_MAN = US_MAN_RX_MPOL | US_MAN_RX_PL(1) | // Expect at least one preamble
 US_MAN_TX_MPOL | US_MAN_TX_PL(1); // Send at least one preamble

 Serial.begin(USB_BAUD);

}
int b = 0;

void loopManchesterSender(){
  if (txStart == 0){
    if(b==0xFF) b=0;
    txData = b++;
    txStart = 1;
  }
  
  while (Serial1.available()) {
  uint8_t new_data = Serial1.read();
  Serial.println(new_data);
  }
  while (Serial.available()) {
  uint8_t new_data = Serial.read();
  Serial1.write(new_data);
  }
  delay(100);
}
