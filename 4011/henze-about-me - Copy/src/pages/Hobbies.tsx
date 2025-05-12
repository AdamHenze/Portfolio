import { Grid } from '@mui/material';
import HobbyPet from '../components/HobbyPet';
import { hobbies } from '../data/hobbies';

//take in data and map to items
const Hobbies = () => {
    return (
        <Grid container spacing={2}>
            {hobbies.map((hobby, index) => (
                <Grid item xs={12} sm={6} md={4} key={index}>
                    <HobbyPet {...hobby} />
                </Grid>
            ))}
        </Grid>
    );
}

export default Hobbies;