//Adam Henze Project 3 Express

const registerLoginCredentials = async (request, response) => {
    const { userName, password , rePassword } = request.body;
    console.log(`Input User: "${userName}"`)
    console.log(`Input Pass: "${password}"`)
    console.log(`Input rePass: "${rePassword}"`)
    console.log("Returned status 201")

    //small logic to check for matching pass' on register
    //intend to circle back and add better features on forms
    if(password !== rePassword){
        console.log("WARNING: NO MATCH")
    }

    return response.status(201).json({ userName , password , rePassword })
};

module.exports = registerLoginCredentials;