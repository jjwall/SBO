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
        var jsonEvent = JSON.parse(message.data);
        var eventTypeName = jsonEvent["eventType"];
        switch (eventTypeName) {
            case "eventTypeTest":
                eventTypeTest(jsonEvent);
                break;
            case "anotherTest":
                console.log("trigger this eventType function");
                break;
            default:
                console.log("unknown eventType");
        }
    };
}
function eventTypeTest(jsonEvent) {
    var eventSubTypeName = jsonEvent["eventSubType"];
    switch (eventSubTypeName) {
        case "eventSpecifics":
            console.log(jsonEvent["eventData"]);
            break;
        default:
            console.log("unknown eventSubType");
    }
}
//# sourceMappingURL=main.js.map