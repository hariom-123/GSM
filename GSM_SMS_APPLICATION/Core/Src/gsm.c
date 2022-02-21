/*
 * gsm.c
 *
 *  Created on: 07-Feb-2022
 *      Author: hariom.intern
 */
#include"gsm.h"
#include "main.h"

hgsm Echo_OFF = {"ATE0","","",200};     	             // to turn the ECHO off
hgsm Echo_ON = {"ATE1","","",200};	                     // to turn the ECHO on
hgsm SIM_NO = {"AT+CICCID","","",200};	                 // to fetch SIM Number
hgsm Signal_strength = {"AT+CSQ","","",200};             // to fetch signal quality
hgsm IMEI = {"AT+CGSN","","",200};	                     // to fetch IMEI Number
hgsm IMSI = {"AT+CIMI","","",200};	                     // to fetch IMSI Number
hgsm SIM_Service_Provider = {"AT+CSPN?","","",200}; 	 // to fetch Service Provider Name
hgsm R_TIME = {"AT+CCLK?","","",200};	                     // to fetch Real Time

gsm gsm_main;
real_time_clock rtc;   // real_time_clock structure variable
/*

* @name Send_AT_Command()
* @brief Send GSM AT command function to gsm module
* It prepares the command for GSM module through ATCOMMAND structure
* Transmit AT command to the GSM module  through HAL transmit function
* Once the command is send it starts a timer for given timeout
* @param ATCOMMAND *atcommand
* @return void

*/
void Send_AT_Command(hgsm* atcommand)
{
	// empty response buffer
	int i = 0;
	for(i = 0; i < gsm_main.count; i++){
		gsm_main.gsm_rx_data[i] = '\0';
	}

	gsm_main.count = 0;

	// transmit at command data
	i = 0;
	while(atcommand->gsm_cmd[i] != '\0'){
		HAL_UART_Transmit(&huart3,&(atcommand->gsm_cmd[i]),1,100);
		i++;
	}
//	HAL_UART_Transmit(&huart3,atcommand->gsm_cmd,10,200);
	// \r \n in command
	HAL_UART_Transmit(&huart3,"\r\n",2,100);

	//wait for time
	HAL_Delay(atcommand->timeout);

	return;
}

/*
* @name Extract_Date_Time()
* @brief Extract Date and Time from gsm_rx_data (work for both ECHO_ON and ECHO_OFF)
* It traverses the gsm_rx_data and extract the date and time string and
* stores them in real_time_clock structure.
* @param none
* @return void
*/

void Extract_Date_Time()
{

	// Taking ptr to the starting character of date i.e. (1 more than ")
	char *start = jump_to_character(gsm_main.gsm_rx_data,'"');
	start++;

	// jump to end char of date (,)
	char *end = jump_to_character(start,',');

	// Extracting date

	extract_substring(rtc.date,start,end);

	// Taking ptr to the starting character of time i.e. (which is 1 step more from ,)
	start = ++end;

	// jump to end char of time (")
	end = jump_to_character(start,'"');

	// Extracting time
	extract_substring(rtc.time,start,end);

}

char* jump_to_character(char* ptr,char ch){

	while(*ptr != ch)
		ptr++;

	return ptr;
}

//including ptr1 & excluding ptr2
void extract_substring(char *dest_buffer,char *ptr1,char *ptr2){

	while(ptr1 != ptr2)
	{
		(*dest_buffer++) = (*ptr1++);
//		dest_buffer++;
//		ptr1++;
	}
}
