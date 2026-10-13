const dbClient = require("../db/client");

class UserAccountDetailsRepository  {
    constructor() {
    }
    static async insert(userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail) {
        const sql = `INSERT INTO user_account_details (user_id, first_name, last_name, address_1, address_2, city, state, zip_code, phone_number, email) 
                     VALUES ($1, $2, $3, $4, $5, $6, $7, $8, $9, $10)
                     RETURNING id`;
        const values = [userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail];
        const results = await dbClient.query(sql, values);
        return results.rows[0];
    }

    static async select(userId) {
        const sql = `SELECT user_id FROM user_account_details WHERE user_id = $1`;
        const values = [userId];
        const results = await dbClient.query(sql, values);
        return results.rows[0];
    }

    static async update(userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail) {
        const sql = `UPDATE User_account_details
                     SET user_id = $1, 
                     first_name = $2, 
                     last_name = $3, 
                     address_1 = $4, 
                     address_2 = $5, 
                     city = $6, 
                     state = $7, 
                     zip_code = $8, 
                     phone_number = $9, 
                     email = $10
                     WHERE user_id = $1`;
        const values = [userId, firstName, lastName, address1, address2, city, countryState, zipCode, phone, userEmail];
        const results = await dbClient.query(sql, values);
        return results.rows[0];
    }
}

module.exports = UserAccountDetailsRepository;