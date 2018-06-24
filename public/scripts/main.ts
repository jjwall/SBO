
// window.WebSocket = window.WebSocket || window.MozWebSocket;

var connection;
var params = new URLSearchParams(window.location.search);
var currentPort = <number>parseInt(params.get("port"));
var currentLoginUserId = <number>parseInt(params.get("loginUserId"));
var hostName = <string>window.location.hostname != "" ? window.location.hostname : "localhost";

if (currentPort != null) {// && currentPort > 9000 && currentPort < 9051) { // -> need to have this same sort of check in the node app when spinning up servers
    connection = new WebSocket("ws://" + hostName + ":" + currentPort);

    connection.onopen = function(event):void {
        connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
    }

    connection.onmessage = function(message) {
        console.log(message);
    }
}

// function onConnect() {
//     connection.onopen = function(event):void {
//         connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
//     }
// }