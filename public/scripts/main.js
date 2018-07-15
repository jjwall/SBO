var params = new URLSearchParams(window.location.search), g = {
    connection: null,
    currentPort: parseInt(params.get("port")),
    currentLoginUserId: parseInt(params.get("loginUserId")),
    hostName: window.location.hostname != "" ? window.location.hostname : "localhost",
    keyLeft: false,
    keyLeftIsDown: false,
    keyRight: false,
    keyRightIsDown: false
};
if (g.currentPort != null) {
    g.connection = new WebSocket("ws://" + g.hostName + ":" + g.currentPort);
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
window.onkeydown = function (e) {
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
        };
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
        };
        g.connection.send(JSON.stringify(keyData));
    }
};
window.onkeyup = function (e) {
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
        };
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
        };
        g.connection.send(JSON.stringify(keyData));
    }
};
//# sourceMappingURL=main.js.map