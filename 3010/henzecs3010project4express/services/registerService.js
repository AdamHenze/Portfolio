//Adam Henze Project 4 Express

const UserAccountsRepository = require('../repositories/userAccountsRepository');
const logger = require('../logger/logger');
const bcrypt = require('bcrypt');
const saltRounds = 10;

const registerLoginCredentials = async (request, response) => {
    const { userName, password } = request.body;
    const userAccountsRepository = new UserAccountsRepository();
    const existingUserAccount = await userAccountsRepository.select(userName);
    if (!existingUserAccount) {
        logger.info('Creating new record in user_account table');
        const salt = await bcrypt.genSalt(saltRounds);
        const passwordHash = await bcrypt.hash(password, salt);
        const newUserAccount = await userAccountsRepository.insert(userName, passwordHash);
        const id = newUserAccount.id;
        logger.info(`Record created with id ${id}`);
        return response.status(201).json({ id });
    } else {
        const error = `${userName} already has an account`;
        logger.error(error);
        return response.status(409).json({ error });
    }
};

module.exports = registerLoginCredentials;