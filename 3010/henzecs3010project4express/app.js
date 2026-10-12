//Adam Henze Project 3 Express

const express = require('express');
const app = express();
const logger = require('./logger/logger');
const cors = require('cors');
const validateLoginCredentials = require('./services/loginService');
const registerLoginCredentials = require('./services/registerService')
const registerAccountInfo = require('./services/accountService')
//const express port
const port = 8080;

app.use(express.json({ limit: '100mb' }));
app.use(express.urlencoded({
    extended: true
}));
//Simple request time logger
app.use(
    (request, response, next) => {
        console.log("A new request received at " + new Date(Date.now()));
        next();
    }
);
//cors to allow SOP break
app.use(cors());
//posts to endpoints
app.post('/login', (request, response) => validateLoginCredentials(request, response));
app.post('/signup', (request, response) => registerLoginCredentials(request, response));
app.post('/account', (request, response) => registerAccountInfo(request, response));

//listener message
app.listen(port, () => {
    console.log(`Henze project app listening on port ${port}`);
});