#include <zephyr.h>
#include <shell/shell.h>
#include <board.h>
#include <sensor.h>

static int cmd_env_show(const struct shell *shell, size_t argc, char **argv)
{
    ARG_UNUSED(argc);
	ARG_UNUSED(argv);

    struct device *bmp_dev = device_get_binding("BME280");

    if (!bmp_dev) {
		shell_fprintf(shell, SHELL_ERROR, "Could not get pointer to BME280 sensor.");
		return -ENODEV;
	}

    struct sensor_value temp, press;
    sensor_sample_fetch(bmp_dev);
    sensor_channel_get(bmp_dev, SENSOR_CHAN_AMBIENT_TEMP, &temp);
    sensor_channel_get(bmp_dev, SENSOR_CHAN_PRESS, &press);

	shell_fprintf(shell, SHELL_NORMAL, "temp: %d.%02d C; press: %d.%06d\n",
		       temp.val1, temp.val2, press.val1, press.val2);

	return 0;
}

SHELL_CREATE_STATIC_SUBCMD_SET(sub_sensors)
{
	SHELL_CMD(env, NULL, "Show environmental sensor values.", cmd_env_show),
	SHELL_SUBCMD_SET_END
};

SHELL_CMD_REGISTER(sensors, &sub_sensors, "Show local sensor values", NULL);

