#include <zephyr/devicetree.h>
#include <zephyr/drivers/i2c.h>

// Initialisation de la communication I2C
/*void init_i2c(const struct i2c_dt_spec dev_i2c)
{
    if (!device_is_ready(dev_i2c.bus))
    {
        printk("I2C bus %s is not ready!\n", dev_i2c.bus->name);
        return;
    }
    printk("I2C bus %s is  ready!\n", dev_i2c.bus->name);
}*/
int init_i2c_device(const struct i2c_dt_spec *dev_i2c) {
    if (dev_i2c == NULL) {
        printk("I2C device not found!\n");
        return -1; // Ou tout autre code d'erreur approprié
    }

    if (!device_is_ready(dev_i2c->bus)) {
        printk("I2C bus %s is not ready!\n", dev_i2c->bus->name);
        return -1; // Ou tout autre code d'erreur approprié
    }

    return 0; // Succès
}

int i2c_write_m(const struct i2c_dt_spec *dev_i2c, const uint8_t *data, size_t len)
{
    if (i2c_write_dt(dev_i2c, data, len) != 0)
    {
        printk("I2C write failed\n");
        return -1; // Ou tout autre code d'erreur approprié
    }
    return 0; // Succès
}

int i2c_read_m(const struct i2c_dt_spec *dev_i2c, uint8_t *data, size_t len)
{
    int ret = i2c_read_dt(dev_i2c, data, len);
    if (ret != 0)
    {
        printk("I2C read failed\n");
        return -1; // Ou tout autre code d'erreur approprié
    }
    return 0; // Succès
}