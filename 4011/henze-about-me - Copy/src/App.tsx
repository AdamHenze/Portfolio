import React from 'react';
import { BrowserRouter as Router, Routes, Route } from 'react-router-dom';
import About from './pages/About';
import Hobbies from './pages/Hobbies';
import NavBar from './components/NavBar';
import Pets from "./pages/Pets";

//basic app rework, make sure to set about as default page
function App() {
  return (
      <Router>
        <NavBar />
        <Routes>
            <Route path="/" element={<About />} />
            <Route path="/hobbies" element={<Hobbies />} />
            <Route path="/pets" element={<Pets />} />
        </Routes>
      </Router>
  );
}

//NOTE: I could not get the images to work within the imbeded jpgs, not sure why, honestly just moved on and linked web addresses, apologies.

export default App;
