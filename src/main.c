#include <zephyr/kernel.h>
#include <zephyr/device.h>
#include <zephyr/devicetree.h>
#include <zephyr/sys/printk.h>
#include <zephyr/drivers/i2c.h>

#include "aht20_controller.h"
#include "i2c_controller.h"

#define I2C1_AHT20_NODE DT_NODELABEL(ath20)

const struct i2c_dt_spec dev_i2c = I2C_DT_SPEC_GET(I2C1_AHT20_NODE);

int main(void)
{
        int ret;
        float humidity, temperature;

        ret = init_i2c_device(&dev_i2c);
        if (ret == 0)
        {
                // I2C initialization successful, you can continue with other operations.
                printk("I2C initialization successful!\n");

                // ... Rest of your code ...
        }
        else
        {
                // Handle the error appropriately.
                printk("I2C initialization failed!\n");

                // ... Handle the error ...
        }

        while (1)
        {
                // Effectuez la calibration (si nécessaire)
                ret = perform_calibration(&dev_i2c);
                if (ret != 0)
                {
                        printk("Calibration failed\n");
                        continue; // Essayez à nouveau ou gérez l'erreur
                }

                // Déclenchez une mesure
                ret = trigger_measurement(&dev_i2c);
                if (ret != 0)
                {
                        printk("Failed to trigger measurement\n");
                        continue; // Essayez à nouveau ou gérez l'erreur
                }

                // Attendez un certain temps pour que la mesure soit terminée
                k_sleep(K_MSEC(WAIT_TIME_COLLECT_DATA_MS));

                // Lisez les données du capteur
                read_sensor_data(&dev_i2c, &humidity, &temperature);

                // Affichez les données
                printk("Relative Humidity: %.2f %%RH\n", humidity);
                printk("Temperature: %.2f °C\n", temperature);

                // Attendez un certain temps avant la prochaine mesure
                k_sleep(K_MSEC(INTERVAL_BETWEEN_MEASUREMENTS));
        }
        return 0;
}
