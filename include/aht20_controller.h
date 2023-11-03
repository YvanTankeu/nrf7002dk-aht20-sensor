#ifndef AHT20_CONTROLLER_H
#define AHT20_CONTROLLER_H

// Bits d'état
#define AHT20_STATUS_BUSY_BIT 0x80       // Bit [7] : Indication d'occupation
#define AHT20_STATUS_CALIBRATED_BIT 0x08 // Bit [3] : Indication d'étalonnage

// Commandes
#define AHT20_CONFIG_0 0x00                // Configuration du capteur à 0
#define AHT20_SOFT_RESET_BYTE 0xBA         // Effectuer un "soft reset" du capteur AHT20
#define AHT20_INIT_CMD 0xBE                // Initialisation du capteur AHT20
#define AHT20_CALIBRATE_CMD 0xE1           // Calibration command
#define AHT20_TRIGGER_MEASUREMENT_CMD 0xAC // Déclencher une mesure sur le capteur AHT20
#define AHT20_STATUS_BUSY_CMD 0x71         // Demande du mot d'octet de calibration

// Temps d'attente
#define WAIT_TIME_COLLECT_DATA_MS 75
#define WAIT_TIME_AFTER_POWER_ON 40
#define WAIT_TIME_AFTER_SOFT_RESET 20
#define WAIT_TIME_IF_BUSY 10
#define INTERVAL_BETWEEN_MEASUREMENTS 5000

// Déclaration des fonctions
void perform_soft_reset(const struct i2c_dt_spec *dev_i2c);
int perform_calibration(const struct i2c_dt_spec *dev_i2c);
void wait_for_idle(const struct i2c_dt_spec *dev_i2c, uint8_t status_reg);
int calibrate_aht20(const struct i2c_dt_spec *dev_i2c);
int trigger_measurement(const struct i2c_dt_spec *dev_i2c);
void read_sensor_data(const struct i2c_dt_spec *dev_i2c, float *humidity, float *temperature);

#endif // AHT20_CONTROLLER_H
