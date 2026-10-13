//Adam Henze Project 3 Express
const UserAccountsDetailsRepository = require('../repositories/userAccountDetailsRepository');
const {insert} = require("../repositories/userAccountDetailsRepository");
const logger = require("../logger/logger");
const bcrypt = require("bcrypt");
const {update} = require("../repositories/userAccountDetailsRepository");
const {select} = require("../repositories/userAccountDetailsRepository");

const registerAccountInfo = async (request, response) => {
    //destructure body into vars
    const {
        userId,
        firstName,
        lastName,
        address1,
        address2,
        city,
        countryState,
        zipCode,
        phone,
        userEmail
    } = request.body;

    const existingUserAccount = await select(userId);
    if (!existingUserAccount) {
        logger.info('Creating new record in user_account_details table');
        await insert(userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail);
        console.log(existingUserAccount);
        console.log("INSERT");
        return response.status(201);

    } else {
        console.log('UPDATE');
        await update(userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail);
        return response.status(201);
    }

    //confirm status to return
    console.log("Returned status 200")
    //return status and info passed in to check full circle of data i/o
    return response.status(200).json({
        firstName,
        lastName,
        address1,
        address2,
        city,
        countryState,
        zipCode,
        phone,
        userEmail
    })
};

module.exports = registerAccountInfo;