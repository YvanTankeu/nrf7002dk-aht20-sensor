#ifndef I2C_CONTROLLER_H
#define I2C_CONTROLLER_H

#include <zephyr/drivers/i2c.h> 

// Déclaration des fonctions
// Déclaration de la fonction pour initialiser l'appareil I2C
int init_i2c_device(const struct i2c_dt_spec *dev_i2c);
int i2c_write_m(const struct i2c_dt_spec *dev_i2c, uint8_t *data, size_t len);
int i2c_read_m(const struct i2c_dt_spec *dev_i2c, uint8_t *data, size_t len);


#endif // I2C_CONTROLLER_H
