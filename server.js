var express = require('express');
var path = require('path');
var cp = require('child_process');
var bodyParser = require('body-parser');
var WebSocket = require('ws');
var http = require('http');
// var fs = require('fs');

var app = express();
var server = http.createServer(app);
var PORT = process.env.PORT || 8080;
var wss = new WebSocket.Server({ server });

// Sets up the Express app to handle data parsing
app.use(bodyParser.json());

var portConnectionsDict = {};

wss.on('connection', function(connection) {
	console.log("Node app is connected to new instance C++ server.");
	connection.on('message', function(message) {
		console.log("Node server says: ");
		var currentConnectionInfo = JSON.parse(message);
		var currentPort = Object.getOwnPropertyNames(currentConnectionInfo);
		var numberOfPlayers = currentConnectionInfo[currentPort];
		portConnectionsDict[currentPort]["Players"] = numberOfPlayers;
		console.log(portConnectionsDict);
	});
});

app.use(express.static('./public'));

app.get("/", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/home.html"));
});

app.get("/playsbo", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/game.html"));
});

app.get("/getportconnections", function(req, res) {
	requestConnections(res);
});

app.post("/creategameroom", function(req, res) {
	findOpenPort(req.body.Name, res);
});

function requestConnections(response) {
	wss.clients.forEach(client => {
		client.send("get connections");
	});
	// need to resolve a promise here before sending response
	response.send(portConnectionsDict);
}

function findOpenPort(gameRoomName, response) {
	var openPort = 9001;
	var iterator = 0;

	for (var key in portConnectionsDict) {
		var potentialAvailablePort = openPort + iterator;
		if (portConnectionsDict[potentialAvailablePort] === undefined) {
			openPort = potentialAvailablePort;
			break;
		}
		else if (portConnectionsDict[potentialAvailablePort + 1] === undefined) {
			openPort = potentialAvailablePort + 1;
			break;
		}
		iterator++;
	}

	spinUpWebSocketServer(openPort);
	portConnectionsDict[openPort] = {"Name": gameRoomName, "Players": 0};
	console.log(portConnectionsDict);
	requestConnections(response);
	//response.send(portConnectionsDict);
}

function spinUpWebSocketServer(port) {
	var child = cp.spawn("./build_native/sbo.exe", [port]);
	child.stdout.on('data', function(data) {
		console.log(data.toString());
	});
}

server.listen(PORT, function () {
	console.log(`Node app listening on port ${PORT}`);
});