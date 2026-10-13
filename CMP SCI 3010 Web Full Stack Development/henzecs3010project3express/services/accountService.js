//Adam Henze Project 3 Express

const registerAccountInfo = async (request, response) => {
    //destructure body into vars
    const {
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

    //console log on express side to check data pass
    console.log(`First: "${firstName}"`);
    console.log(`Last: "${lastName}"`);
    console.log(`Add1: "${address1}"`);
    console.log(`Add2: "${address2}"`);
    console.log(`City: "${city}"`);
    console.log(`State: "${countryState}"`);
    console.log(`Zip: "${zipCode}"`);
    console.log(`Phone: "${phone}"`);
    console.log(`Email: "${userEmail}"`);
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