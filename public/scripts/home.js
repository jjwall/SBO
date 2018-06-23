var createRoomButton = document.getElementById('createRoomButton');
var gameRooms = document.getElementById('gameRooms');
var roomNameInput = document.getElementById('roomNameInput');
var createRoomText = document.getElementById('createRoomText');
var currentLoginUserId = 100000;
createRoomButton.onclick = function () {
    createRoom();
};
function isNullOrWhitespace(input) {
    if (typeof input === 'undefined' || input == null) {
        return true;
    }
    return input.replace(/\s/g, '').length < 1;
}
function createRoom() {
    if (isNullOrWhitespace(roomNameInput.value)) {
        return alert("Room Name field must have a value.");
    }
    createRoomButton.disabled = true;
    roomNameInput.disabled = true;
    createRoomText.innerHTML = 'Creating Room...';
    var url = window.location.href + 'creategameroom';
    var data = { Name: roomNameInput.value };
    fetch(url, {
        method: 'POST',
        body: JSON.stringify(data),
        headers: new Headers({
            'Content-Type': 'application/json'
        })
    })
        .then(function (response) {
        console.log("creating game room...");
        return response.json();
    })["catch"](function (error) {
        console.log('Error: ' + error);
    })
        .then(function (ports) {
        createRoomButton.disabled = false;
        roomNameInput.disabled = false;
        createRoomText.innerHTML = 'Room created successfully!';
        populateRoomList(ports);
    });
}
var joinEvent = function (element, port) {
    element.onclick = function () {
        window.location.href = "/playsbo?port=" + port + "&loginUserId=" + currentLoginUserId;
        console.log(port);
    };
};
function getRoomList() {
    var url = window.location.href + 'getportconnections';
    fetch(url)
        .then(function (response) {
        return response.json();
    })["catch"](function (error) {
        console.log('Error: ' + error);
    })
        .then(function (ports) {
        console.log(ports);
        populateRoomList(ports);
    });
}
function populateRoomList(portsDict) {
    gameRooms.innerHTML = "\n    <tr>\n        <th>Room Name</th>\n        <th>Players</th>\n        <th>Join</th>\n    </tr>";
    for (var key in portsDict) {
        var currentPort = key;
        var gameRoomName = portsDict[key].Name;
        var players = portsDict[key].Players;
        gameRooms.innerHTML += "\n            <tr>\n                <td>" + gameRoomName + ": (Port: " + currentPort + ")</td>\n                <td>(" + players + "/3)</td>\n                <td><button class=\"roomJoin\" data-port=" + key + ">Join</button></<td>\n            </tr>";
    }
    var joinButtonElements = document.getElementsByClassName('roomJoin');
    for (var i = 0; i < joinButtonElements.length; i++) {
        joinEvent(joinButtonElements[i], joinButtonElements[i].attributes[1].value);
    }
    ;
}
getRoomList();
setInterval(function () {
    getRoomList();
}, 60000);
//# sourceMappingURL=home.js.map