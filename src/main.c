#include <zephyr.h>
#include <misc/printk.h>
#include <shell/shell.h>
#include <shell/shell_uart.h>
#include <version.h>
#include <logging/log.h>

#define LOG_LEVEL LOG_LEVEL_DEBUG
#include <logging/log.h>
LOG_MODULE_REGISTER(main);

SHELL_UART_DEFINE(shell_transport_uart);
SHELL_DEFINE(uart_shell, "uart:~$ ", &shell_transport_uart, 10);

void main(void)
{
    LOG_INF("Neonkey application");

    (void)shell_init(&uart_shell, NULL, true, true, LOG_LEVEL_INF);
}