var params = new URLSearchParams(window.location.search), g = {
    connection: null,
    currentPort: parseInt(params.get("port")),
    currentLoginUserId: parseInt(params.get("loginUserId")),
    hostName: window.location.hostname != "" ? window.location.hostname : "localhost"
};
if (g.currentPort != null) {
    g.connection = new WebSocket("ws://" + g.hostName + ":" + g.currentPort);
    g.connection.onopen = function (event) {
        g.connection.send('JavaScript client says: HEYOOOO from PORT ' + g.currentPort);
    };
    g.connection.onmessage = function (message) {
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