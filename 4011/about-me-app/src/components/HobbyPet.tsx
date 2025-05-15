// import necessary media
import { Card, CardMedia, CardContent, Typography } from '@mui/material';

//interface for cards
interface HobbyPetProps {
    title: string;
    description: string;
    imgSrc: string;
}

//hobbypet cards creation
const HobbyPet = ({ title, description, imgSrc }: HobbyPetProps) => {
    return (
        // photo
        <Card sx={{ margin: '24px' }}>
            <CardMedia
                component="img"
                height="140"
                image={imgSrc}
                alt={title}
            />
            {/*text*/}
            <CardContent>
                <Typography gutterBottom variant="h5" component="div">
                    {title}
                </Typography>
                <Typography variant="body2" color="text.secondary">
                    {description}
                </Typography>
            </CardContent>
        </Card>
    );
}

export default HobbyPet;