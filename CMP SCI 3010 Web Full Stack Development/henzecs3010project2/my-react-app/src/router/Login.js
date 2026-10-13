import FullLogo from "../img/FullLogo.png"
import { useState } from "react";
const Login = () => {

    const [logstate, setLogstate] = useState(0);

    const updateLogstate = () => {
        setLogstate(logstate => 1);
        console.log(logstate);
    };

    const resetLogstate = () => {
        setLogstate(logstate => 0);
        console.log(logstate);
    };


    return (
        <div className="container-fluid">
            <div className="col-12">
                <img src={FullLogo} alt="logo" className="smlogo"></img>
            </div>
            <div className="row">
                <div className="col-0 col-sm-1 col-md-2"></div>
                <div className="col-12 col-sm-10 col-md-8 bgChar" style={{padding: '20px', marginbBottom: '70px', textAlign: 'justify'}}>
                    <div className="form-group">
                        <label htmlFor="userName">User Name:</label>
                        <input className="form-control" id="userName" name="userName" type="text"/>
                    </div>
                    <div className="form-group">
                        <label htmlFor="pass">New Password:</label>
                        <input className="form-control" id="pass" name="pass" type="text"/>
                    </div>
                    <hr></hr>
                        <input className="btn btn-primary" type="submit" value="Login" onClick={updateLogstate}/>
                        <input className="btn btn-secondary" type="reset" value="Reset" onClick={resetLogstate}/>
                </div>
                <div className="col-0 col-sm-1 col-md-2"></div>
            </div>
        </div>
    );
};
export default Login;