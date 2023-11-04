/**
 * @file aht20_controller.h
 * @brief Définitions et déclarations pour le contrôleur AHT20.
 *
 * Ce fichier contient les déclarations de fonctions, les constantes et les structures de données
 * utilisées pour interagir avec le capteur AHT20 via le bus I2C.
 */

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

/**
 * @brief Effectue une réinitialisation du capteur AHT20 via le bus I2C.
 *
 * Cette fonction envoie une commande de réinitialisation au capteur AHT20
 * pour le réinitialiser.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 */
void perform_soft_reset(const struct i2c_dt_spec *dev_i2c);

/**
 * @brief Effectue la calibration du capteur AHT20 via le bus I2C.
 *
 * Cette fonction déclenche la calibration du capteur AHT20 en envoyant les commandes appropriées via le bus I2C.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 *
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int perform_calibration(const struct i2c_dt_spec *dev_i2c);

/**
 * @brief Attend que le capteur AHT20 soit actif en vérifiant son statut via le bus I2C.
 *
 * Cette fonction surveille le statut du capteur AHT20 en vérifiant régulièrement le bit d'occupation
 * sur le bus I2C jusqu'à ce que le capteur soit actif.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 * @param status_reg Le registre de statut du capteur AHT20 à vérifier.
 */
void wait_for_idle(const struct i2c_dt_spec *dev_i2c, uint8_t status_reg);

/**
 * @brief Déclenche une mesure du capteur AHT20 via le bus I2C.
 *
 * Cette fonction envoie une commande pour déclencher une mesure du capteur AHT20 via le bus I2C.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 *
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int trigger_measurement(const struct i2c_dt_spec *dev_i2c);

/**
 * @brief Lit les données du capteur AHT20 via le bus I2C et les convertit en humidité et température.
 *
 * Cette fonction lit les données du capteur AHT20 via le bus I2C, les convertit en humidité et température
 * et les renvoie sous forme de valeurs flottantes.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 * @param humidity Pointeur vers la variable où stocker l'humidité.
 * @param temperature Pointeur vers la variable où stocker la température.
 */
void read_sensor_data(const struct i2c_dt_spec *dev_i2c, float *humidity, float *temperature);

#endif // AHT20_CONTROLLER_H
