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

		printf("P -> %s\r\n", sharedBuffer);

		vTaskDelay(configTICK_RATE_HZ);

	}
}

/* Consumer Thread */
static void consumer(void *pvParameters) {

	while (1) {

		sharedBuffer[strlen(sharedBuffer)-1] = '\0';
		sharedBuffer[strlen(sharedBuffer)-2] = '\0';
		sharedBuffer[strlen(sharedBuffer)-3] = '\0';

		printf("C -> %s\r\n", sharedBuffer);

		/* About a 3s delay here */
		vTaskDelay(3*configTICK_RATE_HZ);

		/* About a 1Hz period */
		//vTaskDelay(80 / portTICK_RATE_MS);
	}
}


/*****************************************************************************
 * Main
 ****************************************************************************/

int main(void)
{

	prvSetupHardware();

	/* sharedBuffer producer thread */
	xTaskCreate(producer, (signed char *) "vTaskP1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);

	/* sharedBuffer consumer thread */
	xTaskCreate(consumer, (signed char *) "vTaskC1",
				configMINIMAL_STACK_SIZE, NULL, (tskIDLE_PRIORITY + 1UL),
				(xTaskHandle *) NULL);


	// Start the scheduler
	vTaskStartScheduler();

	// Should never arrive here
	return 1;
}
