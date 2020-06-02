/**
 * \file
 *
 * \brief User board initialization template
 *
 */
/*
 * Support and FAQ: visit <a href="https://www.microchip.com/support/">Microchip Support</a>
 */

#include <asf.h>
#include <board.h>
#include <conf_board.h>

#define ioport_set_pin_peripheral_mode(pin, mode) \
do {\
	ioport_set_pin_mode(pin, mode);\
	ioport_disable_pin(pin);\
} while (0)

static void configure_console(void)
{
	const usart_serial_options_t uart_serial_options = {
		.baudrate = CONF_UART_BAUDRATE,
		#ifdef CONF_UART_CHAR_LENGTH
		.charlength = CONF_UART_CHAR_LENGTH,
		#endif
		.paritytype = CONF_UART_PARITY,
		#ifdef CONF_UART_STOP_BITS
		.stopbits = CONF_UART_STOP_BITS,
		#endif
	};

	/* Configure console UART. */
	sysclk_enable_peripheral_clock(ID_UART0);
	stdio_serial_init(UART0, &uart_serial_options);
}


void board_init(void)
{
	/* This function is meant to contain board-specific initialization code
	 * for, e.g., the I/O pins. The initialization can rely on application-
	 * specific board configuration, found in conf_board.h.
	 */
	
	ioport_init();
	
	// Set all LEDS to output
	ioport_set_pin_dir(LEDA_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LEDB_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LEDC_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LEDD_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LEDE_PIN, IOPORT_DIR_OUTPUT);
	ioport_set_pin_dir(LEDF_PIN, IOPORT_DIR_OUTPUT);
	
	// CAN Flags
	ioport_set_pin_peripheral_mode(PIN_CAN0_RX_IDX, PIN_CAN0_RX_FLAGS);
	ioport_set_pin_peripheral_mode(PIN_CAN0_TX_IDX, PIN_CAN0_TX_FLAGS);
	
	// UART Flags
	ioport_set_pin_peripheral_mode(USART1_RXD_GPIO, USART1_RXD_FLAGS);
	MATRIX->CCFG_SYSIO |= CCFG_SYSIO_SYSIO4;
	ioport_set_pin_peripheral_mode(USART1_TXD_GPIO, USART1_TXD_FLAGS);
	
	configure_console();
}
