// Need to add fetch that checks to see if it is okay to connect to the port
// if the exe isn't already spun up then we should NOT attempt to connect

window.WebSocket = window.WebSocket || window.MozWebSocket;

var connection;
var params = new URLSearchParams(window.location.search);
var currentPort = parseInt(params.get("port"));
var currentLoginUserId = params.get("loginUserId");

if (currentPort != null) {// && currentPort > 9000 && currentPort < 9051) { // -> need to have this same sort of check in the node app when spinning up servers
    connection = new WebSocket("ws://" + window.location.hostname + ":" + currentPort);

    connection.onopen = function(event) {
        connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
    }
}

// function requestSocketToJoin() {
//     var url = window.location.href + '/getsocket';

//     fetch(url)
//         .then(function(response) {
//             return response.json();
//         })
//         .catch(function(error) {
//             console.log('Error: ' + error);
//         })
//         .then(function(availablePorts) {
//             console.log(availablePorts);
//             connectToPort(availablePorts);
//         });
// }

// requestSocketToJoin();

function connectToPort(ports) {
    for (var key in ports) {
        currentPort = key;
        if (ports[key] < 3) {
            connection = new WebSocket('ws://localhost:' + currentPort);
            onConnect();
            console.log("Connected to port " + currentPort);
            return;
        }
    }
}

// // connection.onmessage = function(message) {
// //     console.log(message);
// // }

function onConnect() {
    connection.onopen = function(event) {
        connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
    }
}