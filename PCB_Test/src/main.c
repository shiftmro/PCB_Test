/**
 * \file
 *
 * \brief Empty user application template
 *
 */

/**
 * \mainpage User Application template doxygen documentation
 *
 * \par Empty user application template
 *
 * Bare minimum empty user application template
 *
 * \par Content
 *
 * -# Include the ASF header files (through asf.h)
 * -# "Insert system clock initialization code here" comment
 * -# Minimal main function that starts with a call to board_init()
 * -# "Insert application code here" comment
 *
 */

/*
 * Include header files for all drivers that have been imported from
 * Atmel Software Framework (ASF).
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */
#include <asf.h>
#include "shift_can.h"
#include "shift_led.h"
#include "testing/shift_can_testing.h"

/** UART Interface */
#define CONF_UART            CONSOLE_UART
/** Baudrate setting */
#define CONF_UART_BAUDRATE   (115200UL)
/** Character length setting */
#define CONF_UART_CHAR_LENGTH  US_MR_CHRL_8_BIT
/** Parity setting */
#define CONF_UART_PARITY     US_MR_PAR_NO
/** Stop bits setting */
#define CONF_UART_STOP_BITS    US_MR_NBSTOP_1_BIT

static void display_menu(void)
{
	printf("Menu :\r\n"
	"  -- Select the action:\r\n"
	"  0: Test mcan init. \r\n"
	"  1: Test simple message. \r\n"
	"  2: Test add single filters. \r\n"
	"  3: Test add range filters. \r\n"
	"  4: Test send too large message. \r\n"
	"  5: Test send message with no data. \r\n"
	"  6: Test send message with no ID.. \r\n"
	"  7: Test send custom message \r\n"
	"  8: Test custom filter \r\n"
	"  h: Display menu \r\n\r\n");
}

int main (void)
{
	/* Insert system clock initialization code here (sysclk_init()). */
	sysclk_init();

	board_init();
	
	uint8_t key;
	
	blink_led(LEDA_PIN, 2);
		
	while (1) {
		scanf("%c", (char *)&key);

		switch (key) {
			case 'h':
			display_menu();
			break;

			case '0':
			printf("  0: Test mcan init. \r\n");
			init_can_module();
			add_range_filter_module_0(0, 0x00, 0x7FF);
			add_single_filter_module_0(0x15, 1);
			add_range_filter_module_1(2, 0x00, 0x7FF);
			add_single_filter_module_1(0x15, 3);
			break;

			case '1':
			printf("  1: Test simple message. \r\n");
			test_send_message_simple();
			
			break;

			case '2':
			printf("  2: Test add single filters. \r\n");
			test_add_single_filters();
			break;

			case '3':
			printf("  3: Test add range filters. \r\n");
			test_add_range_filters();
			break;

			case '4':
			printf("  4: Test send too large message. \r\n");
			test_send_too_big_message();
			break;

			case '5':
			printf("  5: Test send message with no data. \r\n");
			test_send_message_no_data();
			break;

			case '6':
			printf("  6: Test send message with no ID. \r\n");
			test_send_message_no_id();
			break;
			
			case '7':
			printf("  7: Test send custom message \r\n");
			uint32_t customId;
			scanf("%d\r\n", (uint32_t*) &customId);
			
			shift_can_message_t customMsg;
			
			simple_struct_t test_struct;
			test_struct.x = 26;
			test_struct.y = 200;
			test_struct.z = 120;
			
			uint8_t buffer[64];

			serialize_data(&test_struct, sizeof(test_struct), buffer);
			customMsg.data = buffer;
			customMsg.dataSize = sizeof(test_struct);
			customMsg.id = customId;
			
			send_message_module_0(&customMsg);
			printf("Sent message with id: %d \r\n", customId);
			break;
			
			case '8':
			printf("  8: Test custom filter \r\n");
			uint32_t filterId;
			scanf("%d\r\n", (uint32_t*) &filterId);
			
			add_single_filter_module_1(filterId, 6);
			printf("Added filter with ID: %d \r\n", filterId);
			break;

			default:
			break;
		}
	};
}

void message_received(shift_can_message_t* message)
{
	printf("Message received in main!\n");
	test_message_received(message);
}
