import {Link, Outlet} from "react-router-dom";

// function togglelinks(props) {
//     let x = document.getElementById("login");
//     let y = document.getElementById("logout")
//     if(props.logstate = 1){
//         x.style.display = "none";
//         y.style.display = "block";
//     }else{
//         x.style.display = "block";
//         y.style.display = "none";
//     }
// }
const Layout = (props) => {
    // togglelinks();
    return (
        <>
            <div className="container-fluid p-3 bgChar">
                <div className="row justify-content-end">
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Home.html" target="_self" style={{color: "white"}}><b>Home</b></a>*/}
                        <Link to="/">Home</Link>
                    </div>
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Account.html" target="_self">Account</a>*/}
                        <Link to="/Account">Account</Link>
                    </div>
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Registration.html" target="_self">Signup</a>*/}
                        <Link to="/Signup">Signup</Link>
                    </div>
                    <div id={"login"} className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Login.html" target="_self">Login</a>*/}
                        <Link to="/Login">Login</Link>
                    </div>
                    <div id={"logout"} className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Home.html" target="_self">Logout</a>*/}
                        <Link to="/asd">Logout</Link>
                    </div>
                </div>
            </div>
            {
                /*
                The <Outlet> renders the current route selected.
                 */
            }
            <Outlet/>
            <footer>
                <div className="row">
                    <div className="col-12 bgChar" style={{padding: "20px"}}>
                        <a href="https://www.youtube.com/@TipsfromaShipwrightvideos" target="_blank">Tips From a Shipwright</a>
                    </div>
                </div>
            </footer>
        </>
    );
};

export default Layout;