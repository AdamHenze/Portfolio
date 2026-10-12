import FullLogo from "../img/FullLogo.png"
const Signup = () => {
    return (
        <div class="container-fluid">
            <div class="col-12">
                <img src={FullLogo} alt="logo" className="smlogo"></img>
            </div>
            <div class="row">
                <div class="col-0 col-sm-1 col-md-2"></div>
                <div class="col-12 col-sm-10 col-md-8 bgChar" style={{padding: '20px', marginbBottom: '70px', textAlign: 'justify'}}>
                    <form>
                        <h1>New Customer Registration</h1>
                        <div class="form-group">
                            <label for="userName">User Name:</label>
                            <input class="form-control" id="userName" name="userName" type="text"/>
                        </div>
                        <div class="form-group">
                            <label for="pass">New Password:</label>
                            <input class="form-control" id="pass" name="pass" type="text"/>
                        </div>
                        <div class="form-group">
                            <label for="pass2">Repeat Password:</label>
                            <input class="form-control" id="pass2" name="pass2" type="text"/>
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

export default Signup;