// window.WebSocket = window.WebSocket || window.MozWebSocket;

var params = <URLSearchParams> new URLSearchParams(window.location.search),
g = {
    connection: <WebSocket> null,
    currentPort: <number>parseInt(params.get("port")),
    currentLoginUserId: <number>parseInt(params.get("loginUserId")),
    hostName: <string>window.location.hostname != "" ? window.location.hostname : "localhost",
    keyLeft: <boolean> false,
    keyLeftIsDown: <boolean> false,
    keyRight: <boolean> false,
    keyRightIsDown: <boolean> false,
}

if (g.currentPort != null) {// && currentPort > 9000 && currentPort < 9051) { // -> need to have this same sort of check in the node app when spinning up servers
    g.connection = new WebSocket("ws://" + g.hostName + ":" + g.currentPort);

    g.connection.onopen = function(event):void {
        var newPlayerData = {
            "eventType": "newPlayer",
            "eventData": {
                "class": "wizard", // -> example eventData
                "team": "red", // -> for player creation event
            }
        }
        g.connection.send(JSON.stringify(newPlayerData));
    }

    // all JSON blobs will come through here with an event type
    // switch statment will call the function pertaining to that event type
    g.connection.onmessage = function(message):void {
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

// keyboard controls
window.onkeydown = function(e) {
    if (e.keyCode === 37 && !g.keyLeftIsDown) {
        console.log("down_once_left");
        g.keyLeftIsDown = true;
        g.keyLeft = true;
        
        var keyData = {
            "eventType": "position",
            "eventData": {
                "key": "left",
                "state": "down"
            }
        }
        g.connection.send(JSON.stringify(keyData));
    }
    if (e.keyCode === 39 && !g.keyRightIsDown) {
        console.log("down_once_right");
        g.keyRightIsDown = true;
        g.keyRight = true;

        var keyData = {
            "eventType": "position",
            "eventData": {
                "key": "right",
                "state": "down"
            }
        }
        g.connection.send(JSON.stringify(keyData));
    }
}

window.onkeyup = function(e) {
    if (e.keyCode === 37 && g.keyLeftIsDown) {
        console.log("up_once_left");
        g.keyLeftIsDown = false;
        g.keyLeft = false;

        var keyData = {
            "eventType": "position",
            "eventData": {
                "key": "left",
                "state": "up"
            }
        }
        g.connection.send(JSON.stringify(keyData));
    }
    if (e.keyCode === 39 && g.keyRightIsDown) {
        this.console.log("up_once_right");
        g.keyRightIsDown = false;
        g.keyRight = false;

        var keyData = {
            "eventType": "position",
            "eventData": {
                "key": "right",
                "state": "up"
            }
        }
        g.connection.send(JSON.stringify(keyData));
    }
}