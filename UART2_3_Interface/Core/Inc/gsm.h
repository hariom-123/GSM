/*
 * gsm.h
 *
 *  Created on: 07-Feb-2022
 *      Author: hariom.intern
 */

#ifndef SRC_GSM_H_
#define SRC_GSM_H_

#define MAX_BUFFER_SIZE	512

// Structure for GSM Command
typedef struct{
	char gsm_cmd[50];
	char gsm_response[50];
	char response_status[20];
	int timeout;
} hgsm;

// Structure for GSM
typedef struct{
	unsigned char gsm_rx_data[MAX_BUFFER_SIZE];
	unsigned char gsm_tx_data[MAX_BUFFER_SIZE];
	int count;

} gsm;

extern gsm gsm_main;

// Structure for Real time clock
typedef struct{
	unsigned char date[9];                 // Current Date
	unsigned char time[12];                // Current Time
}real_time_clock;

extern real_time_clock rtc;





//for transmitting specified gsm command
void Send_AT_Command(hgsm* );

// Extract date and time from gsm_rx_data
void Extract_Date_Time();


#endif /* SRC_GSM_H_ */

