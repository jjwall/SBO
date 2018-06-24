
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

    // all JSON blobs will come through here with an event type
    // switch statment will call the function pertaining to that event type
    connection.onmessage = function(message):void {
        var jsonEvent = JSON.parse(message.data);
        var eventTypeName = jsonEvent["eventType"];

        switch(eventTypeName) {
            case "eventTypeTest":
                eventTypeTest(jsonEvent);
                break;
            case "anotherTest":
                console.log("trigger this eventType function");
                break;
            default:
                console.log("unknown eventType");
        }
        // console.log(message);
    }
}

// this is an example of a specific event type function
// will also have switch statement on event sub type
// an example would be eventType: attack -> call attack()
// switch on eventSubtType: fireball / sword slash etc...
function eventTypeTest(jsonEvent:JSON):void {
    var eventSubTypeName = jsonEvent["eventSubType"];

    switch(eventSubTypeName) {
        case "eventSpecifics":
            console.log(jsonEvent["eventData"]);
            // -> update global client info etc.
            break;
        default:
            console.log("unknown eventSubType");
    }
}