/*
 * Address.h
 * @brief Defines the Address class for storing address-related information.
 *
 * This header file declares the Address class, which encapsulates details
 * about an address including the street name, postal code, city name, and
 * additional information.
 *
 *  Created on: Dec 21, 2024
 *      Author: Admin
 */

#ifndef ADDRESS_H_
#define ADDRESS_H_
#include <string>

/**
 * @class Address
 * @brief Represents an address with street, postal code, city, and extra info.
 *
 * The Address class provides a way to store and retrieve details about an
 * address, including the street name, postal code, city name, and any
 * additional information associated with the address.
 */
class Address
{
private:
    /**
     * @brief The name of the street.
     *
     * This attribute stores the name of the street for the address. It is
     * used to identify the specific street where the address is located.
     */
    std::string street;

    /**
     * @brief The postal code of the address.
     *
     * This attribute stores the postal code, which is used to identify the
     * specific area or locality of the address.
     */
    unsigned short postalCode;

    /**
     * @brief The name of the city.
     *
     * This attribute stores the name of the city associated with the address.
     * It helps in locating the geographical region of the address.
     */
    std::string cityName;

    /**
     * @brief Additional address-related information.
     *
     * This attribute stores any extra details or comments about the address,
     * such as apartment numbers, landmarks, or other identifying information.
     */
    std::string additionalInfo;
public:

    /**
     * @brief Constructs an Address object.
     *
     * Initializes an Address object with the given street, postal code, city,
     * and additional information.
     *
     * @param street The name of the street.
     * @param postalCode The postal code of the address.
     * @param cityName The name of the city.
     * @param additionalInfo Additional address-related information.
     */
	Address(std::string street, unsigned short postalCode,
			std::string cityName , std::string additionalInfo);

    /**
     * @brief Gets the street name.
     * @return The name of the street as a string.
     */
	const std::string getStreet() const {return street;};

    /**
     * @brief Gets the postal code.
     * @return The postal code as an unsigned short.
     */
	const unsigned short getPostalCode() const {return postalCode;};

    /**
     * @brief Gets the city name.
     * @return The name of the city as a string.
     */
	const std::string getCityName() const {return cityName;};

    /**
     * @brief Gets additional information.
     * @return The additional information as a string.
     */
	const std::string getAdditionalInfo() const {return additionalInfo;};
};

#endif /* ADDRESS_H_ */
