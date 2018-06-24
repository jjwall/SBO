var connection;
var params = new URLSearchParams(window.location.search);
var currentPort = parseInt(params.get("port"));
var currentLoginUserId = parseInt(params.get("loginUserId"));
var hostName = window.location.hostname != "" ? window.location.hostname : "localhost";
if (currentPort != null) {
    connection = new WebSocket("ws://" + hostName + ":" + currentPort);
    connection.onopen = function (event) {
        connection.send('JavaScript client says: HEYOOOO from PORT ' + currentPort);
    };
    connection.onmessage = function (message) {
        console.log(message);
    };
}
//# sourceMappingURL=main.js.map