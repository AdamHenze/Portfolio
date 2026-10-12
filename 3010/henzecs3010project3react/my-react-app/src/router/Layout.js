//Adam Henze Project 3 React

import {Link, Outlet} from "react-router-dom";
import {useEffect, useState} from "react";
const Layout = (props) => {

    const [showLinks, setShowLinks] = useState(false);

    //use effect shows hook updates based on props.test dependency to call setshowlinks
    useEffect(() => {
        //update showlinks to props.test value
        setShowLinks(() => props.test)
    }, [props.test])

    //conditionals perform link visibility, logout calls props.change function, sets logstate to false
    return (
        <>
            <div className="container-fluid p-3 bgChar">
                <div className="row justify-content-end">
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Home.html" target="_self" style={{color: "white"}}><b>Home</b></a>*/}
                        <Link to="/">Home</Link>
                    </div>
                    {showLinks === true &&
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Account.html" target="_self">Account</a>*/}
                        <Link to="/Account">Account</Link>
                    </div>
                    }
                    {showLinks === false &&
                    <div className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Registration.html" target="_self">Signup</a>*/}
                        <Link to="/Signup">Signup</Link>
                    </div>
                    }
                    {showLinks === false &&
                    <div id={"login"} className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Login.html" target="_self">Login</a>*/}
                        <Link to="/Login">Login</Link>
                    </div>
                    }
                    {showLinks === true &&
                    <div id={"logout"} className="col-12 col-sm-3 col-md-2 col-lg-1">
                        {/*<a href="Home.html" target="_self">Logout</a>*/}
                        <Link to="/"><span onClick={props.change}>Logout</span></Link>
                    </div>
                    }
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