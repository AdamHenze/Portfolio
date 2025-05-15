//necessary imports
import React, { useState } from 'react';
import axios from 'axios';
import { TextField, Button, Card, CardContent, Typography, CardMedia, Grid, Alert } from '@mui/material';

//Anything after ruby and sapphire is just a digimon. That one is just freaking key-chain!?
//And ill submit quite a few designs up to here were borderline.
//Voltorb -> Cool: looks like a haunter possesed a pokeball.
//Electrode -> you just flipped it and ruined the eyes? it looks like it needs glasses.
//But now all the pokemon are inanimate objects and concepts, did I miss something where they haunt everyday objects now?
//we went from pigeons and rats fighting to the concepts of time and space. The gen one legendaries atleast felt more grounded (not a bird pun)
//and yeah the UNKNOWNS were weird but silver gold ruby and sapphire felt in the same creative realm
//whatever, im just old i guess.

//main component
const QueryPokedex: React.FC = () => {
    //setup usestates for data retrieval
    const [pokemonId, setPokemonId] = useState<string>('');
    //get data as any type expecting json
    const [pokemonData, setPokemonData] = useState<any>(null);
    //error state as catch for bad search
    const [error, setError] = useState<string | null>(null);

    //update pokemon id searched when text updated
    const handleInputChange = (event: React.ChangeEvent<HTMLInputElement>) => {
        setPokemonId(event.target.value);
    };

    //search func
    const handleSearch = async () => {
        //return if no id found
        if (!pokemonId) return;
        try {
            //no error, set returned data as pokemon data
            setError(null);
            const response = await axios.get(`https://pokeapi.co/api/v2/pokemon/${pokemonId}`);
            setPokemonData(response.data);
        } catch (err) {
            //catched error update error state for display
            setError('Pokemon not found or an error occurred.');
            setPokemonData(null);
        }
    };

    //returned elements
    return (
        //pokedex bg
        <Grid container
              spacing={2}
              direction="column"
              alignItems="center"
              justifyContent="center"
              style={{ width: '50%',
                  height: '50%',
                  background: 'red',
                  padding: '50px',
                  borderRadius: '20px',
                  margin: 'auto',
                  marginTop: '50px'}}>
            {/*pokedex title*/}
            <Grid item>
                <h1>
                    POKEDEX
                </h1>
            </Grid>
            {/*input field for pokemon query*/}
            <Grid item style={{backgroundColor: 'white', borderRadius: '5px'}}>
                <TextField
                    style={{padding: '20px', paddingLeft: '5px'}}
                    label="Pokemon ID"
                    type="number"
                    value={pokemonId}
                    onChange={handleInputChange}
                    variant="outlined"
                />
            </Grid>
            {/*search button*/}
            <Grid item>
                <Button variant="contained" color="primary" onClick={handleSearch}>
                    Search
                </Button>
            </Grid>
            {/*check for error and display if so*/}
            {error && (
                <Grid item>
                    <Alert severity="error">{error}</Alert>
                </Grid>
            )}
            {/*check for poke data and display*/}
            {pokemonData && (
                <Grid item>
                    {/*create card media*/}
                    <Card style={{ maxWidth: 345 }}>
                        {/*picture*/}
                        <CardMedia
                            component="img"
                            alt={pokemonData.name}
                            height="auto"
                            image={pokemonData.sprites.front_default}
                            title={pokemonData.name}
                        />
                        {/*use returned pokedata to populate text*/}
                        <CardContent>
                            <Typography gutterBottom variant="h5" component="div">
                                {pokemonData.name}
                            </Typography>
                            <Typography variant="body2" color="textSecondary" component="p">
                                Type: {pokemonData.types.map((typeInfo: any) => typeInfo.type.name).join(', ')}
                            </Typography>
                            <Typography variant="body2" color="textSecondary" component="p">
                                Height: {pokemonData.height}
                            </Typography>
                            <Typography variant="body2" color="textSecondary" component="p">
                                Weight: {pokemonData.weight}
                            </Typography>
                            {/*NOTE: use slice to display only four of the returned moves of array*/}
                            <Typography variant="body2" color="textSecondary" component="p">
                                Moves: {pokemonData.moves.slice(0, 4).map((moveInfo: any) => moveInfo.move.name).join(', ')}
                            </Typography>
                        </CardContent>
                    </Card>
                </Grid>
            )}
        </Grid>
    );
};

export default QueryPokedex;