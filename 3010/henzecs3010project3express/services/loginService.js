//Adam Henze Project 3 Express

const validateLoginCredentials = (request, response) => {
    const { userName, password } = request.body;
    console.log(`Input User: "${userName}"`)
    console.log(`Input Pass: "${password}"`)
    console.log( "Returned status 200")
    return response.status(200).json({ userName , password })
};

module.exports = validateLoginCredentials;