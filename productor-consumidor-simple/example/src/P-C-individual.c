#include "board.h"
#include "FreeRTOS.h"
#include "task.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

static char sharedBuffer[256] = "";

/* Sets up system hardware */
static void prvSetupHardware(void)
{
	SystemCoreClockUpdate();
	Board_Init();
}


/* PRODUCTOR */
static void producer(void *pvParameters) {

	int index = 1;
	char result[5];

	while (1) {

		sprintf(result, "%d", index);
		strcat (sharedBuffer, result);

		index++;

		printf("P%s\r\n", sharedBuffer);

		//vTaskDelay(configTICK_RATE_HZ);
		vTaskDelay(30/portTICK_RATE_MS);
	}
}

/* CONSUMIDOR */
static void consumer(void *pvParameters) {

	while (1) {

		memset(sharedBuffer,'\0',sizeof(sharedBuffer));


		printf("C%s\r\n", sharedBuffer);

		/* About a 3s delay here */
		//vTaskDelay(3*configTICK_RATE_HZ);

		/* About a 1Hz period */
		//vTaskDelay(80 / portTICK_RATE_MS);
		vTaskDelay(40/portTICK_RATE_MS);
	}
}


/*****************************************************************************
 * Main
 ****************************************************************************/

int main(void)
{
	vTraceEnable(TRC_START);
	prvSetupHardware();

	/* sharedBuffer consumer thread */
	xTaskCreate(consumer, (signed char *) "vTaskC1",
					configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
					(xTaskHandle *) NULL);


	/* sharedBuffer producer thread */
	xTaskCreate(producer, (signed char *) "vTaskP1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 2UL),
				(xTaskHandle *) NULL);


	// Start the scheduler
	vTaskStartScheduler();

	// Should never arrive here
	return 1;
}
