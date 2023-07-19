const portPath = 'COM3'
const { SerialPort } = require('serialport')
const serialport = new SerialPort({ path: portPath, baudRate: 9600 })

const express = require('express');
const app = express();
const port = 80;
app.use(express.static('web'));
app.get('/', (req, res) => {
    res.sendFile(__dirname + '/web/index.html');
});
const server = app.listen(port, () => {
//    updatetoken();
    console.log(`Server is running on port ${port}`);
});
const SocketServer = require("ws").Server;
const wss = new SocketServer({ server });
wss.on("connection", (ws) => {

    ws.on("message", (event) => {
        let res = JSON.parse(event.toString());
        if (res.get == "data") {
            serialport.write(`{"play":${res.data}}\r\n`)
        }
    });
    ws.on("close", () => {
        console.log("有人斷開連線");
    });
});