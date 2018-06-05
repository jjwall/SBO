window.WebSocket = window.WebSocket || window.MozWebSocket;

var connection = new WebSocket('ws://localhost:9001');

connection.onmessage = function(message) {
    console.log(message);
}

console.log("This is a test...");

connection.onopen = function(event) {
    connection.send('HEYOOOO from the JavaScripts!!!');
}