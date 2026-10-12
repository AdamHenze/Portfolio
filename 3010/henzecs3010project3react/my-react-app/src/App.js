//Adam Henze Project 3 React

import logo from './logo.svg';
import './App.css';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Layout from "./router/Layout";
import Home from "./router/Home";
import Account from "./router/Account";
import Signup from "./router/Signup";
import NoPage from "./router/NoPage";
import Login from "./router/Login";
import { useState , useEffect } from "react";

function App() {

    //bool logstate to track log-state
    const [logState, setLogState] = useState(false);

    //login function to set logstate to true
    const login = () => {
        setLogState(prevState => {
            if(prevState === true){
                return prevState;
            }
            else{
                return !prevState;
            }
        });
    }

    //logout for logout button to set logstate to false
    const logout = () => {
        setLogState( prevState => {
            return false;
        })
    }

        return (
            <BrowserRouter>

                <Routes>
                    <Route path="/" element={<Layout test={logState} change={logout}/>}>
                        <Route index element={<Home/>}/>
                        {
                            /*
                            The nested <Route>s inherit and add to the parent route.
                            So the blogs path is combined with the parent and becomes /blogs.
                            */
                        }
                        <Route path="Login" element={<Login change={login}/>}/>
                        <Route path="Account" element={<Account/>}/>
                        <Route path="Signup" element={<Signup/>}/>
                        {
                            /*
                            Setting the path to * will act as a catch-all for any undefined URLs.
                            This is great for a 404 error page.
                            */
                        }
                        <Route path="*" element={<NoPage/>}/>
                    </Route>
                </Routes>
            </BrowserRouter>
        );
}
export default App;