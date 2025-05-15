import { Typography, Box } from '@mui/material';

//Should be simple to get this page running, description of about and photo
const About = () => {
    return (
        <Box p={3}>
        <Typography variant="h4">About Me</Typography>
    <img src="https://westcomsw.com/wp-content/uploads/2016/05/oscar.png" alt="Profile" style={{ width: '100px', height: '100px' }} />
    <Typography paragraph>
        Hey everyone!

        Im Adam,

        Wrapping up my final few courses this semester and this is officially my last CS class, got through 4280 and 4750!

        I spend alot of time working in my woodshop for a hobby and often have some car project taking up time and money as well.

        Nice to meet you all!
    </Typography>
    </Box>
);
}

export default About;