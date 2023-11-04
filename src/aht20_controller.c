#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/drivers/i2c.h>
#include "aht20_controller.h"
#include "i2c_controller.h"

void perform_soft_reset(const struct i2c_dt_spec *dev_i2c)
{
    uint8_t cmd = AHT20_SOFT_RESET_BYTE;
    if (i2c_write_dt(dev_i2c, cmd, sizeof(cmd)) != 0)
    {
        printk("Failed to perform soft reset\n");
    }
    k_sleep(K_MSEC(WAIT_TIME_AFTER_SOFT_RESET));
}

void wait_for_idle(const struct i2c_dt_spec *dev_i2c, uint8_t status_reg)
{
    uint8_t data;
    while (1) {
        int ret = i2c_read_m(dev_i2c, &data, sizeof(data));

        if (ret != 0) {
            printk("Failed to read sensor status\n");
            return; // Gérer l'erreur ici, si nécessaire
        }

        if (!(data & status_reg)) {
            // Le bit d'occupation n'est plus défini, le capteur est inactif
            break;
        }

        k_sleep(K_MSEC(WAIT_TIME_IF_BUSY));
    }
}

int perform_calibration(const struct i2c_dt_spec *dev_i2c) {
    uint8_t data, cmd[3];
    int ret;

    // Calibration
    cmd[0] = AHT20_CALIBRATE_CMD;
    cmd[1] = AHT20_STATUS_CALIBRATED_BIT;
    cmd[2] = AHT20_CONFIG_0;

    ret = i2c_write_m(dev_i2c, cmd, sizeof(cmd));
    if (ret != 0) {
        printk("Failed to perform calibration\n");
        return -1; // Échec de la calibration
    }

    wait_for_idle(dev_i2c, AHT20_STATUS_BUSY_BIT);

    ret = i2c_read_m(dev_i2c, &data, sizeof(data));
    while (data & AHT20_STATUS_BUSY_BIT)
    {
        k_sleep(K_MSEC(WAIT_TIME_IF_BUSY));
    }

    printk("Data apres calibrage = %d\n", data);
    if (!(data & AHT20_STATUS_CALIBRATED_BIT))
    {
        printk("Non calibre");
    }
    return 0; // Calibration réussie
}

int trigger_measurement(const struct i2c_dt_spec *dev_i2c) {
    uint8_t cmd[3] = {AHT20_TRIGGER_MEASUREMENT_CMD, 0x33, 0};
    int ret = i2c_write_m(dev_i2c, cmd, sizeof(cmd));
    if (ret != 0) {
        printk("Failed to trigger measurement\n");
    }

    wait_for_idle(dev_i2c, AHT20_STATUS_BUSY_BIT);

    return ret;
}

void read_sensor_data(const struct i2c_dt_spec *dev_i2c, float *humidity, float *temperature)
{
    uint8_t hdata[6];
    int ret;

    // Effectuez la lecture des données du capteur AHT20
    ret = i2c_read_m(dev_i2c, hdata, sizeof(hdata));

    if (ret != 0)
    {
        printk("Failed to read data from AHT20 sensor\n");
        return; // Gérer l'erreur ici, si nécessaire
    }

    // Traitez les données lues pour extraire l'humidité et la température
    uint32_t h = hdata[1];
    h <<= 8;
    h |= hdata[2];
    h <<= 4;
    h |= hdata[3] >> 4;
    *humidity = ((float)h * 100) / 0x100000;

    uint32_t tdata = hdata[3] & 0x0F;
    tdata <<= 8;
    tdata |= hdata[4];
    tdata <<= 8;
    tdata |= hdata[5];
    *temperature = ((float)tdata * 200 / 0x100000) - 50;
}