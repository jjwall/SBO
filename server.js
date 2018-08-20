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
var pendingRequestsDict = {};
var getConnsArray = [];

wss.on('connection', function(connection) {
	console.log("Node app is connected to new instance of a C++ server.");

	// ping all game servers so we can resolve the requests set up by "/creategameroom" POST
	requestConnections();

	// listens for connection info from game servers
	connection.on('message', function(message) {
		var currentGameServerInfo = JSON.parse(message);
		var currentPort = currentGameServerInfo["port"];
		var numberOfConnections = currentGameServerInfo["connections"];

		// update port connection struct with new connection info
		portConnectionsDict[currentPort]["Connections"] = numberOfConnections;

		for (var key in pendingRequestsDict) {
			// resolve request
			pendingRequestsDict[key]();
			// delete value as request is no longer pending
			delete pendingRequestsDict[key];
		}

		// iterate through getConnsArray and resolve each request
		for (var i = 0; i < getConnsArray.length; i++) {
			// resolve request
			getConnsArray[i]();
			// delete value at index i as request has been resolved
			getConnsArray.splice(i, 1);
		}
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
	// ping all servers so our request can be resolved
	requestConnections();

	if (isEmpty(portConnectionsDict)) {
		res.send(portConnectionsDict);
	}
	else {
		// push response param onto getConnsArray
		getConnsArray.push(function(){
			res.send(portConnectionsDict);
		});
	}
});

app.post("/creategameroom", function(req, res) {
	findOpenPort(req.body.Name, res);
});

function requestConnections() {
	wss.clients.forEach(client => {
		client.send("get connections");
	});
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

	portConnectionsDict[openPort] = {"Name": gameRoomName, "Connections": 0};

	pendingRequestsDict[openPort] = function() {
		response.send(portConnectionsDict);
	}

	spinUpWebSocketServer(openPort);
}

function spinUpWebSocketServer(port) {
	//var child = cp.spawn("./build_native/sbo.exe", [port]);
	var child = cp.spawn("./build_x64_debug/build/x64-Debug/sbo.exe", [port]);
	child.stdout.on('data', function(data) {
		console.log(data.toString());
	});
}

function isEmpty(obj) {
	for(var key in obj) {
		if(obj.hasOwnProperty(key))
			return false;
	}
	return true;
}

server.listen(PORT, function () {
	console.log(`Node app listening on port ${PORT}`);
});