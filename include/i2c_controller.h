/**
 * @file i2c_controller.h
 * @brief Définitions et déclarations pour le contrôleur I2C.
 *
 * Ce fichier contient les déclarations de fonctions et les constantes
 * utilisées pour l'initialisation et la communication avec les périphériques
 * I2C sur le microcontrôleur.
 */

#ifndef I2C_CONTROLLER_H
#define I2C_CONTROLLER_H

#include <zephyr/drivers/i2c.h> 

/**
 * @brief Initialise un dispositif I2C.
 *
 * Cette fonction vérifie la disponibilité du dispositif I2C spécifié dans le devicetree
 * et l'état de préparation du bus I2C.
 *
 * @param dev_i2c Spécification I2C de devicetree.
 *
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int init_i2c_device(const struct i2c_dt_spec *dev_i2c);

/**
 *@brief Écrivez une quantité définie de données sur un périphérique I2C.
 *
 *@param spec Spécification I2C de devicetree.
 *@param data Pool de mémoire à partir duquel les données sont transférées.
 *@param len Nombre d'octets à écrire.
 *
 *@return 0 en cas de succès, -1 en cas d'erreur.
 */
int i2c_write_m(const struct i2c_dt_spec *dev_i2c, uint8_t *data, size_t len);

/**
 *@brief Lit une quantité définie de données à partir d'un appareil I2C.
 *
 *@param dev_i2c Spécification I2C de Devicetree.
 *@param data Pool de mémoire qui stocke les données récupérées.
 *@param len Nombre d'octets à lire.
 *
 * @return 0 en cas de succès, -1 en cas d'erreur.
 */
int i2c_read_m(const struct i2c_dt_spec *dev_i2c, uint8_t *data, size_t len);


#endif // I2C_CONTROLLER_H
