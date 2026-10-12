import logo from './logo.svg';
import './App.css';
import { BrowserRouter, Routes, Route } from "react-router-dom";
import Layout from "./router/Layout";
import Home from "./router/Home";
import Account from "./router/Account";
import Signup from "./router/Signup";
import NoPage from "./router/NoPage";
import Login from "./router/Login";
import { useState } from "react";
function App() {

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
      <BrowserRouter>

        <Routes>
          <Route path="/" element={<Layout/>}>
            <Route index element={<Home/>}/>
            {
              /*
              The nested <Route>s inherit and add to the parent route.
              So the blogs path is combined with the parent and becomes /blogs.
              */
            }
            <Route path="Login" element={<Login/>}/>
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