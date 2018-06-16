// Need to clean up unneeded GET requests here

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
		console.log("Node server says: " + message);
	});
});

// check needs to be modified to only spin up game server if it isn't already running...
function requestConnections(port) {
	var portString = port.toString();
	if (wss.clients.length === 0 || wss.clients.length == undefined) {
		portConnectionsDict[portString] = 1;
		spinUpWebSocketServer(portString);
	}
	else {
		wss.clients.forEach(client => {
			client.send("get connections");
		});
	}
	console.log(portConnectionsDict);
}

app.use(express.static('./public'));

app.get("/", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/home.html"));
});

// keeping this here for now to simply spin up servers through the URL...
app.get("/playsbo/:port", function(req, res) {
	var routePort = req.params.port;
	requestConnections(routePort);
	res.sendFile(path.join(__dirname, "/public/game.html"));
	// findFirstAvailablePort();
	// console.log("Port Connections:");
	// console.log(portConnections);
});

app.get("/playsbo", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/game.html"));
});

app.get("/getportconnections", function(req, res) {
	// var routePort = req.params.port;
	// requestConnections(routePort);
	res.send(portConnectionsDict);
});

app.post("/creategameroom", function(req, res) {
	// var routePort = req.params.port;
	// requestConnections(routePort);
	res.send(portConnectionsDict);
});

// function findFirstAvailablePort() {
// 	for (var i = 0; i < portConnections.length; i++) {
// 		var currentPort = (i + 9001).toString();
// 		if (portConnections[i][currentPort].length > 3) {
// 			continue;
// 		}
// 		if (portConnections[i][currentPort].length === 0) {
// 			spinUpWebSocketServer(currentPort);
// 			portConnections[i][currentPort].push(true); // push socket connection not a bool
// 			return;
// 		}
// 		if (portConnections[i][currentPort].length > 0 && portConnections[i][currentPort].length < 3) {
// 			portConnections[i][currentPort].push(true); // push socket connection not a bool
// 			return;
// 		}
// 	}
// 	console.log("All the game rooms are full :(");
// }

function spinUpWebSocketServer(port) {
	var child = cp.spawn("./build_native/sbo.exe", [port]);
	child.stdout.on('data', function(data) {
		console.log(data.toString());
	});
}

server.listen(PORT, function () {
	console.log(`Node app listening on port ${PORT}`);
});