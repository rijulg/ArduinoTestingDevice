/*
Copyright (c) 2016, Farzad Noorian <farzad.noorian@sydney.edu.au> All rights
reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this
list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice,
this list of conditions and the following disclaimer in the documentation
and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

*/

void setupManchesterDecoder()
{
  Serial1.begin(MANCHESTER_BAUD, SERIAL_8E1);
  USART0->US_MR |= US_MR_MAN      |  // Enable Manchester decoder
                   US_MR_MODSYNC  |  // Start bit is 1 to 0 transition
                   US_MR_ONEBIT;     // One bit start
  USART0->US_MAN = US_MAN_RX_MPOL | US_MAN_RX_PL(1)  |  // Expect at least one preamble
                   US_MAN_TX_MPOL | US_MAN_TX_PL(1);    // Send at least one preamble
                
  Serial.begin(USB_BAUD);
}

void loopManchesterDecoder()
{
  while (Serial1.available()) {
    uint8_t new_data = Serial1.read();
    Serial.write(new_data);
  }

  while (Serial.available()) {
    uint8_t new_data = Serial.read();
    Serial1.write(new_data);
  }
}
