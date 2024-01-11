// GopherCAN_devboard_example.c
//  This is a bare-bones module file that can be used in order to make a module main file

#include "GopherCAN_devboard_example.h"
#include "main.h"
#include <stdio.h>
#include "pulse_sensor.h"
#include "gopher_sense.h"

#define CONVERSION_RATIO (float)CALCULATE_MPH_CONVERSION_RATIO(30.0f, 7.8f) // Conversion ration from frequency of pulses to mph
#define HDMA_CHANNEL_4 2 // hdma value dma is going to use
#define HDMA_CHANNEL_3 3 // TODO: This is prob wrong, verify
#define DMA_STOPPED_TIMEOUT_MS 1000
#define LOW_PULSES_PER_SECOND 1 // 15 mph, when we only take 5 samples per dma check
#define HIGH_PULSES_PER_SECOND 300 // Don't expect to reach this but we don't want to take that many samples
#define MIN_SAMPLES 2
#define MAX_SAMPLES 20

// the HAL_CAN struct. This example only works for a single CAN bus
CAN_HandleTypeDef* example_hcan;
extern TIM_HandleTypeDef htim2;

// Use this to define what module this board will be
#define THIS_MODULE_ID PLM_ID
#define PRINTF_HB_MS_BETWEEN 1000


// some global variables for examples
U8 last_button_state = 0;
float wheel_speed_front_right;
float wheel_speed_front_left;
bool error = false;

// the CAN callback function used in this example
static void change_led_state(U8 sender, void* UNUSED_LOCAL_PARAM, U8 remote_param, U8 UNUSED1, U8 UNUSED2, U8 UNUSED3);
static void init_error(void);

int setup1, setup2;

// init
//  What needs to happen on startup in order to run GopherCAN
void init(CAN_HandleTypeDef* hcan_ptr)
{
	example_hcan = hcan_ptr;

	// initialize CAN
	// NOTE: CAN will also need to be added in CubeMX and code must be generated
	// Check the STM_CAN repo for the file "F0xx CAN Config Settings.pptx" for the correct settings
	if (init_can(GCAN0, example_hcan, THIS_MODULE_ID, BXTYPE_MASTER))
	{
		init_error();
	}

	// Set the function pointer of SET_LED_STATE. This means the function change_led_state()
	// will be run whenever this can command is sent to the module
	if (add_custom_can_func(SET_LED_STATE, &change_led_state, TRUE, NULL))
	{
		init_error();
	}

	if (setup_pulse_sensor_vss(
			&htim2,
			TIM_CHANNEL_4,
			CONVERSION_RATIO,
			&wheel_speed_front_right,
			DMA_STOPPED_TIMEOUT_MS,
			true,
			LOW_PULSES_PER_SECOND,
			HIGH_PULSES_PER_SECOND,
			MIN_SAMPLES,
			MAX_SAMPLES
			) != NO_PULSE_SENSOR_ISSUES) {
		init_error();
	}
	if (setup_pulse_sensor_vss(
			&htim2,
			TIM_CHANNEL_3,
			CONVERSION_RATIO,
			&wheel_speed_front_left,
			DMA_STOPPED_TIMEOUT_MS,
			true,
			LOW_PULSES_PER_SECOND,
			HIGH_PULSES_PER_SECOND,
			MIN_SAMPLES,
			MAX_SAMPLES
			) != NO_PULSE_SENSOR_ISSUES) {
		init_error();
	}
}


// can_buffer_handling_loop
//  This loop will handle CAN RX software task and CAN TX hardware task. Should be
//  called every 1ms or as often as received messages should be handled
void can_buffer_handling_loop()
{
	// handle each RX message in the buffer
	if (service_can_rx_buffer())
	{
		// an error has occurred
	}

	// handle the transmission hardware for each CAN bus
	service_can_tx(example_hcan);
}


// main_loop
//  another loop. This includes logic for sending a CAN command. Designed to be
//  called every 10ms
void main_loop()
{
	static U32 last_print_hb = 0;

	// send the current tick over UART every second
	if (!error && (HAL_GetTick() - last_print_hb >= PRINTF_HB_MS_BETWEEN))
	{
		printf("Current tick: %lu\n", HAL_GetTick());
		last_print_hb = HAL_GetTick();
		HAL_GPIO_TogglePin(HBeat_GPIO_Port, Hbeat_Pin);
		HAL_GPIO_TogglePin(Pullup_1_GPIO_Port, Pullup_1_Pin);
		HAL_GPIO_TogglePin(Pullup_2_GPIO_Port, Pullup_2_Pin);
		HAL_GPIO_TogglePin(Pullup_3_GPIO_Port, Pullup_3_Pin);
		HAL_GPIO_TogglePin(PU4_GPIO_Port, PU4_Pin);
		HAL_GPIO_TogglePin(PU5_GPIO_Port, PU5_Pin);
		HAL_GPIO_TogglePin(PU6_GPIO_Port, PU6_Pin);
		HAL_GPIO_TogglePin(PU7_GPIO_Port, PU7_Pin);
		HAL_GPIO_TogglePin(PU8_GPIO_Port, PU8_Pin);
		HAL_GPIO_TogglePin(PU9_GPIO_Port, PU9_Pin);
		HAL_GPIO_TogglePin(PU10_GPIO_Port, PU10_Pin);
		HAL_GPIO_TogglePin(PU11_GPIO_Port, PU11_Pin);
		HAL_GPIO_TogglePin(PU12_GPIO_Port, PU12_Pin);
		HAL_GPIO_TogglePin(GSense_GPIO_Port, GSense_Pin);




	}

	if (check_pulse_sensors() != NO_PULSE_SENSOR_ISSUES) {
		error = true;
//		HAL_GPIO_WritePin(HBeat_GPIO_Port, HBeat_Pin, 1);
//		HAL_GPIO_WritePin(HBeat, GPIO_PIN_34, 1);
//		HAL_GPIO_WritePin(Pullup_1, GPIO_PIN_2, 1);
//		HAL_GPIO_WritePin(Pullup_2, GPIO_PIN_3, 1);
//		HAL_GPIO_WritePin(Pullup_3, GPIO_PIN_4, 1);
//		HAL_GPIO_WritePin(PU4, GPIO_PIN_57, 1);
//		HAL_GPIO_WritePin(PU5, GPIO_PIN_56, 1);
//		HAL_GPIO_WritePin(PU6, GPIO_PIN_54, 1);
//		HAL_GPIO_WritePin(PU7, GPIO_PIN_40, 1);
//		HAL_GPIO_WritePin(PU8, GPIO_PIN_39, 1);
//		HAL_GPIO_WritePin(PU9, GPIO_PIN_38, 1);
//		HAL_GPIO_WritePin(PU10, GPIO_PIN_37, 1);
//		HAL_GPIO_WritePin(PU11, GPIO_PIN_36, 1);
//		HAL_GPIO_WritePin(PU12, GPIO_PIN_35, 1);
//		HAL_GPIO_WritePin(GSense, GPIO_PIN_33, 1);

	} else {
		error = false;
	}

	update_and_queue_param_float(&pulseSensor1_V, wheel_speed_front_right);
	update_and_queue_param_float(&pulseSensor2_V, wheel_speed_front_left);

	// DEBUG
	static U8 last_led = 0;
	static U32 last_led_time = 0;

	if (HAL_GetTick() - last_led_time >= 250)
	{
		send_can_command(PRIO_HIGH, ALL_MODULES_ID, SET_LED_STATE, last_led, last_led, last_led, last_led);
		last_led_time = HAL_GetTick();
		last_led = (last_led + 1) % 2;
	}


}


// can_callback_function example

// change_led_state
//  a custom function that will change the state of the LED specified
//  by parameter to remote_param. In this case parameter is a U16*, but
//  any data type can be pointed to, as long as it is configured and casted
//  correctly
static void change_led_state(U8 sender, void* parameter, U8 remote_param, U8 UNUSED1, U8 UNUSED2, U8 UNUSED3)
{
	HAL_GPIO_WritePin(HBeat_GPIO_Port, HBeat_Pin, !!remote_param);
	return;
}


// init_error
//  This function will stay in an infinite loop, blinking the LED in a 0.5sec period. Should only
//  be called from the init function before the RTOS starts
void init_error(void)
{
	while (1)
	{
		HAL_GPIO_TogglePin(HBeat_GPIO_Port, HBeat_Pin);
		HAL_Delay(250);

	}
}

// end of GopherCAN_example.c
