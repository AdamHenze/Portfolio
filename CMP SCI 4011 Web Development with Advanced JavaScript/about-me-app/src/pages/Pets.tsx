import { Grid } from '@mui/material';
import HobbyPet from '../components/HobbyPet';
import { pets } from '../data/pets';

//take in data and map to items
//copy and past job from hobbys page to add another pet page
const Pets = () => {
    return (
        <Grid container spacing={2}>
            {pets.map((pet, index) => (
                <Grid item xs={12} sm={6} md={4} key={index}>
                    <HobbyPet {...pet} />
                </Grid>
            ))}
        </Grid>
    );
}

export default Pets;