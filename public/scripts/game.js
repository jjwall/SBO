window.WebSocket = window.WebSocket || window.MozWebSocket;

var connection;
var currentPort;

function requestSocketToJoin() {
    var url = window.location.href + '/getsocket';

    fetch(url)
        .then(function(response) {
            return response.json();
        })
        .catch(function(error) {
            console.log('Error: ' + error);
        })
        .then(function(availablePorts) {
            console.log(availablePorts);
            connectToPort(availablePorts);
        });
}

requestSocketToJoin();

function connectToPort(ports) {
    for (var i = 0; i < ports.length; i++) {
		currentPort = (i + 9001).toString();
		if (ports[i][currentPort].length > 3) {
			continue;
		}
		if (ports[i][currentPort].length < 3) {
            connection = new WebSocket('ws://localhost:' + currentPort);
            onConnect();
            console.log("Connected to port " + currentPort);
			return;
		}
    }
    console.log("No rooms are available at this time :(");
}

// connection.onmessage = function(message) {
//     console.log(message);
// }

function onConnect() {
    connection.onopen = function(event) {
        connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
    }

    window.onunload = function() {
        //connection.close();
        var url = window.location.href + '/disconnect';
        var data = {port: currentPort};

        fetch(url, {
            method: 'POST',
            body: JSON.stringify(data),
            headers: new Headers({
                'Content-Type': 'application/json'
            })
        }).then(res => res.json())
        .catch(error => console.error('Error:', error))
        .then(response => console.log('Success:', response));
    }
}