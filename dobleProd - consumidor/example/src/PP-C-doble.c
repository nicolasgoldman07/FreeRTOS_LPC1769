#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <queue.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>


#define SIZE 50
#define tempSize 5

xQueueHandle xQueue1;

typedef struct  {
	int temp;
	char * str;
} QueueData;


/* Sets up system hardware */
static void prvSetupHardware(void) {
	SystemCoreClockUpdate();
	Board_Init();
}



/*****************************************************************************
 * Producers functions
 ****************************************************************************/
static void  temperatureGenerator() {

	QueueData * temperatureQue;
	temperatureQue = malloc(sizeof(QueueData *));
	temperatureQue->str = malloc (sizeof (SIZE));
	temperatureQue->str = NULL;

	int temperature = 0;
	while (1) {

		//rand () % (N-M+1) + M;   // Este está entre M y N
		temperature = rand() % 10 + 20; //

		//temperature += 1;
		temperatureQue->temp = temperature;
		xQueueSend(xQueue1, (QueueData *) &temperatureQue, 5000);
		//printf("Temperatura de la funcion temp --> %02d \r\n", temperature);
		vTaskDelay(30 / portTICK_RATE_MS);

	}
}


static void stringGenerator() {


	QueueData * stringQue;
	stringQue = malloc (sizeof (QueueData *));
	stringQue->str = malloc (SIZE);
	stringQue->temp = NULL;

	srand((unsigned int)(time(NULL)));

	char charVocabulary[] = "abcdefghijklmnopqrstuvwxyz0123456789";
	int stringLength = 0;
	char finalStr[SIZE] = "";

	while(1){

		//%(N-M+1) + M
		stringLength = rand() % (11) + 10;
		for (int i = 0; i < stringLength; i++){
			finalStr[i] = charVocabulary[rand() % (sizeof (charVocabulary) - 1)];
		}

		finalStr[stringLength] = '\0';

		strcpy(stringQue->str, finalStr);

		xQueueSend(xQueue1, (QueueData *) &stringQue, 5);

		for (int i = 0; i < stringLength; i++){
			finalStr[i] = '\0';
		}
		vTaskDelay((10 * ((rand() % 10) + 6) * portTICK_RATE_MS));


	}

}


/*****************************************************************************
 * Consumer function
 ****************************************************************************/

/* Consumer Thread */
static void consumidor(void *pvParameters) {

	QueueData * recQue;
	recQue = malloc (sizeof (QueueData *));
	recQue->str = malloc (SIZE);

	while (1) {


		if(xQueueReceive(xQueue1, &recQue, portMAX_DELAY)){

			if(recQue->str != NULL){
				printf("String-> %s\r\n", recQue->str);
			}
			if(recQue->temp != NULL){
				printf("Temperature -> %2d ºC\r\n", recQue->temp);
			}
		}

		//printf("Temperatura -> %d \r\nString -> %s \r\n", pxRxedMessage->temp, pxRxedMessage->str/*xQueueInfo.temp, xQueueInfo.str*/);

		//vTaskDelay(2*configTICK_RATE_HZ);


	}
}


/*****************************************************************************
 * Main
 ****************************************************************************/

int main(void)
{

	prvSetupHardware();

	vTraceEnable(TRC_START);

	xQueue1 = xQueueCreate(20, sizeof(QueueData *) );

	srand(time(NULL));

	/* sharedBuffer producer thread */
	xTaskCreate(temperatureGenerator, (signed char *) "vTaskP1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 3UL),
				(xTaskHandle *) NULL);

	xTaskCreate(stringGenerator, (signed char *) "vTaskP2",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
					(xTaskHandle *) NULL);

	/* sharedBuffer consumer thread */
	xTaskCreate(consumidor, (signed char *) "vTaskC1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);


	// Start the scheduler
	vTaskStartScheduler();

	// Should never arrive here
	return 1;
}

