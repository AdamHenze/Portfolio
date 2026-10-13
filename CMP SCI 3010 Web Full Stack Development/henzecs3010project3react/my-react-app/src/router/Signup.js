//Adam Henze Project 3 React

import FullLogo from "../img/FullLogo.png"
import {useState} from "react";
const Signup = () => {

    const [userName, setUserName] = useState("");
    const [password, setPassword] = useState("");
    const [rePassword, setRePassword] = useState("")
    const handleSubmit = async (event) => {
        console.log(userName);
        console.log(password);
        console.log(rePassword);
        event.preventDefault();
        const response = await fetch('http://localhost:8080/signup', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ userName, password, rePassword }),
        });
        const statusOut = await response.status;
        const data = await response.json();
        console.log('Data received:', data);
        console.log('Status received:', statusOut)
    }

    return (
        <div class="container-fluid">
            <div class="col-12">
                <img src={FullLogo} alt="logo" className="smlogo"></img>
            </div>
            <div class="row">
                <div class="col-0 col-sm-1 col-md-2"></div>
                <div class="col-12 col-sm-10 col-md-8 bgChar" style={{padding: '20px', marginbBottom: '70px', textAlign: 'justify'}}>
                    <form onSubmit={handleSubmit}>
                        <h1>New Customer Registration</h1>
                        <div class="form-group">
                            <label for="userName">User Name:</label>
                            <input
                                class="form-control"
                                id="userName"
                                name="userName"
                                type="text"
                                value={userName}
                                onChange={(e) => setUserName(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="pass">New Password:</label>
                            <input
                                class="form-control"
                                id="pass"
                                name="pass"
                                type="password"
                                value={password}
                                onChange={(e) => setPassword(e.target.value)}
                            />
                        </div>
                        <div class="form-group">
                            <label for="pass2">Repeat Password:</label>
                            <input
                                class="form-control"
                                id="repass"
                                name="repass"
                                type="password"
                                value={rePassword}
                                onChange={(e) => setRePassword(e.target.value)}
                            />
                        </div>
                        <hr></hr>
                        <input
                            class="btn btn-primary"
                            type="submit"
                            value="Submit Data"/>
                        <input
                            class="btn btn-secondary"
                            type="reset"
                            value="Reset Data"/>
                    </form>
                </div>
                <div class="col-0 col-sm-1 col-md-2"></div>
            </div>
        </div>
    );
};

export default Signup;