//Adam Henze Project 3 React

import FullLogo from "../img/FullLogo.png"
import {useState} from "react";
const Account = () => {

    //setup usestate for variables
    const [ firstName , setFirstName] = useState("");
    const [ lastName , setLastName] = useState("");
    const [ address1 , setAddress1] = useState("");
    const [ address2 , setAddress2 ] = useState("");
    const [ city , setCity] = useState("");
    const [ countryState , setCountryState] = useState("");
    const [ zipCode , setZipCode] = useState("");
    const [ phone , setPhone] = useState("");
    const [ userEmail , setUserEmail] = useState("");

    //handle submit on form submission
    const handleSubmit = async (event) => {

        //log info on dom side to check data in
        console.log(firstName);
        console.log(lastName);
        console.log(address1);
        console.log(address2);
        console.log(city);
        console.log(countryState);
        console.log(zipCode);
        console.log(phone);
        console.log(userEmail);

        event.preventDefault();

        //send to express
        const response = await fetch('http://localhost:8080/account', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                firstName,
                lastName,
                address1,
                address2,
                city,
                countryState,
                zipCode,
                phone,
                userEmail
            }),
        });
        //print data back from express end
        const statusOut = await response.status;
        const data = await response.json();
        console.log('Data received:', data);
        console.log('Status received:', statusOut)
    }

    //react form
    return (
        <div class="container-fluid">
            <div class="col-12">
                <img src={FullLogo} alt="logo" className="smlogo"></img>
            </div>
            <div class="row">
                <div class="col-0 col-sm-1 col-md-2"></div>
                <div class="col-12 col-sm-10 col-md-8 bgChar" style={{padding: '20px', marginBottom: '70px', textAlign: "justify"}}>
                    <form onSubmit={handleSubmit}>
                        <h1>Customer Account Info</h1>
                        <div class="form-group">
                            <label for="firstName">First name:</label>
                            <input
                                class="form-control"
                                id="firstName"
                                name="firstName"
                                type="text"
                                value={firstName}
                                onChange={(e) => setFirstName(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="lastName">Last name:</label>
                            <input
                                class="form-control"
                                id="lastName"
                                name="lastName"
                                type="text"
                                value={lastName}
                                onChange={(e) => setLastName(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="addLine1">Address Line 1:</label>
                            <input
                                class="form-control"
                                id="addLine1"
                                name="addLine1"
                                type="text"
                                value={address1}
                                onChange={(e) => setAddress1(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="addLine2">Address Line 2:</label>
                            <input
                                class="form-control"
                                id="addLine2"
                                name="addLine2"
                                type="text"
                                value={address2}
                                onChange={(e) => setAddress2(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="city">City:</label>
                            <input
                                class="form-control"
                                id="city"
                                name="city"
                                type="text"
                                value={city}
                                onChange={(e) => setCity(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <br></br>
                            State:
                            <label for="country-state"></label>
                            <select
                                id="country-state"
                                name="country-state"
                                value={countryState}
                                onChange={(e) => setCountryState(e.target.value)}
                            >
                                <option value="">Select state</option>
                                <option value="AL">Alabama</option>
                                <option value="AK">Alaska</option>
                                <option value="AS">American Samoa</option>
                                <option value="AZ">Arizona</option>
                                <option value="AR">Arkansas</option>
                                <option value="UM-81">Baker Island</option>
                                <option value="CA">California</option>
                                <option value="CO">Colorado</option>
                                <option value="CT">Connecticut</option>
                                <option value="DE">Delaware</option>
                                <option value="DC">District of Columbia</option>
                                <option value="FL">Florida</option>
                                <option value="GA">Georgia</option>
                                <option value="GU">Guam</option>
                                <option value="HI">Hawaii</option>
                                <option value="UM-84">Howland Island</option>
                                <option value="ID">Idaho</option>
                                <option value="IL">Illinois</option>
                                <option value="IN">Indiana</option>
                                <option value="IA">Iowa</option>
                                <option value="UM-86">Jarvis Island</option>
                                <option value="UM-67">Johnston Atoll</option>
                                <option value="KS">Kansas</option>
                                <option value="KY">Kentucky</option>
                                <option value="UM-89">Kingman Reef</option>
                                <option value="LA">Louisiana</option>
                                <option value="ME">Maine</option>
                                <option value="MD">Maryland</option>
                                <option value="MA">Massachusetts</option>
                                <option value="MI">Michigan</option>
                                <option value="UM-71">Midway Atoll</option>
                                <option value="MN">Minnesota</option>
                                <option value="MS">Mississippi</option>
                                <option value="MO">Missouri</option>
                                <option value="MT">Montana</option>
                                <option value="UM-76">Navassa Island</option>
                                <option value="NE">Nebraska</option>
                                <option value="NV">Nevada</option>
                                <option value="NH">New Hampshire</option>
                                <option value="NJ">New Jersey</option>
                                <option value="NM">New Mexico</option>
                                <option value="NY">New York</option>
                                <option value="NC">North Carolina</option>
                                <option value="ND">North Dakota</option>
                                <option value="MP">Northern Mariana Islands</option>
                                <option value="OH">Ohio</option>
                                <option value="OK">Oklahoma</option>
                                <option value="OR">Oregon</option>
                                <option value="UM-95">Palmyra Atoll</option>
                                <option value="PA">Pennsylvania</option>
                                <option value="PR">Puerto Rico</option>
                                <option value="RI">Rhode Island</option>
                                <option value="SC">South Carolina</option>
                                <option value="SD">South Dakota</option>
                                <option value="TN">Tennessee</option>
                                <option value="TX">Texas</option>
                                <option value="UM">United States Minor Outlying Islands</option>
                                <option value="VI">United States Virgin Islands</option>
                                <option value="UT">Utah</option>
                                <option value="VT">Vermont</option>
                                <option value="VA">Virginia</option>
                                <option value="UM-79">Wake Island</option>
                                <option value="WA">Washington</option>
                                <option value="WV">West Virginia</option>
                                <option value="WI">Wisconsin</option>
                                <option value="WY">Wyoming</option>
                            </select>
                        </div>
                        <br></br>
                        <div class="form-group">
                            <label for="zipCode">Zip Code:</label>
                            <input
                                class="form-control"
                                id="zipCode"
                                name="zipCode"
                                type="text"
                                value={zipCode}
                                onChange={(e) => setZipCode(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="phone">Phone Number:</label>
                            <input
                                class="form-control"
                                id="phone"
                                name="phone"
                                type="text"
                                value={phone}
                                onChange={(e) => setPhone(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="email">Email:</label>
                            <input
                                class="form-control"
                                id="email"
                                name="email"
                                type="text"
                                value={userEmail}
                                onChange={(e) => setUserEmail(e.target.value)}
                            />
                        </div>
                        <hr></hr>
                        <input class="btn btn-primary" type="submit" value="Submit Data"/>
                        <input class="btn btn-secondary" type="reset" value="Reset Data"/>
                    </form>
                </div>
                <div class="col-0 col-sm-1 col-md-2"></div>
            </div>
        </div>
    );
};

export default Account;