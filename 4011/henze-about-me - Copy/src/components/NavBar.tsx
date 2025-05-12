import { Link } from 'react-router-dom';
import { AppBar, Toolbar, Typography, Button } from '@mui/material';

const NavBar = () => {
    return (
        <AppBar position="static" sx={{ bgcolor: '#123456' }}>
            <Toolbar>
                <Typography variant="h6" component="div" sx={{ flexGrow: 1 }}>
                    Adam Henze - About Me Project
                </Typography>
                {/*pages*/}
                <Button color="inherit" component={Link} to="/">About</Button>
                <Button color="inherit" component={Link} to="/hobbies">Hobbies</Button>
                <Button color="inherit" component={Link} to="/pets">Pets</Button>
            </Toolbar>
        </AppBar>
    );
}

export default NavBar;