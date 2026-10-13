//Adam Henze Project 3 React

import FullLogo from "../img/FullLogo.png"
import { useState } from "react";

const Login = ({ change }) => {

    const [userName, setUserName] = useState("");
    const [password, setPassword] = useState("");

    const handleSubmit = async (event) => {
        console.log(userName);
        console.log(password);
        event.preventDefault();
        const response = await fetch('http://localhost:8080/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({ userName, password }),
        });
        const statusOut = await response.status;
        const data = await response.json();
        console.log('Data received:', data);
        console.log('Status received:', statusOut)
    }

    return (
        <div className="container-fluid">
            <div className="col-12">
                <img src={FullLogo} alt="logo" className="smlogo"></img>
            </div>
            <div className="row">
                <div className="col-0 col-sm-1 col-md-2"></div>
                    <div className="col-12 col-sm-10 col-md-8 bgChar" style={{padding: '20px', marginbBottom: '70px', textAlign: 'justify'}}>
                        <form onSubmit={handleSubmit}>
                            <div className="form-group">
                                <label htmlFor="userName">User Name:</label>
                                <input
                                    className="form-control"
                                    id="userName"
                                    name="userName"
                                    type="text"
                                    value={userName}
                                    onChange={(e) => setUserName(e.target.value)}
                                />
                            </div>
                            <div className="form-group">
                                <label htmlFor="pass">New Password:</label>
                                <input
                                    className="form-control"
                                    id="pass"
                                    name="pass"
                                    type="password"
                                    value={password}
                                    onChange={(e) => setPassword(e.target.value)}
                                />
                            </div>
                            <hr></hr>
                            <input className="btn btn-primary" type="submit" value="Login" onClick={() => change()}/>
                        </form>
                    </div>
                <div className="col-0 col-sm-1 col-md-2"></div>
            </div>
        </div>
    );
};
export default Login;
