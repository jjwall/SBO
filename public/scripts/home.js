// TO DO:
// 1. (done) set up Create Room functionality by posting to the server, server will figure out
// which port to set it up on (somewhere between 9000 and 9051). Node app will send response
// back to client once the .exe has been spun up, then populateRoomList will be called after success
// 2. set up long polling that pings node server for availablePorts... this ping will also cause the node
// server to ping all running .exe servers and they will return the number of connections which node will
// update the portConnections struct with and then send back to client which will update room list accordingly
// 3. (done) Give dynamic "roomJoin" button functionality -> we will replace our dynamic routing to port system
// by using URL params instead. That's what the dynamic join buttons will route players to
// 4. (PRIORITIZE) ensure that static pages can be run WITHOUT being hosted on node. I.e. the script sourcing on
// game.html needs to be scrapped entirely since we will no longer be using dynamic routes
// -> this will also allow for easier game engine testing as we will not need to prop up node server and 
// go through "game room lobby" in order to test changes. Can just run .exe from command line... and should
// be able to ignore the .exe client connection errors...
// 5. Set up TypeScript
// 6. Set up Pixi.js and get Type Declarations for it
// 7. Begin working on engine...

var createRoomButton = document.getElementById('createRoomButton');
var gameRooms = document.getElementById('gameRooms');
var roomNameInput = document.getElementById('roomNameInput');
var currentLoginUserId = 100000 // -> will get dynamically through user auth eventually...

createRoomButton.onclick = function() {
    createRoom();
}

function isNullOrWhitespace(input) {
    if (typeof input === 'undefined' || input == null) {
        return true;
    }
    return input.replace(/\s/g, '').length < 1;
}

// probably should replace all FETCH requests with XHR requests and check browser implementations of URLSearchParamss
// but also might not be worth it...
function createRoom() {
    if (isNullOrWhitespace(roomNameInput.value)) {
        return alert("Room Name field must have a value.");
    }

    var url = window.location.href + 'creategameroom';

    var data = {Name: roomNameInput.value};

    fetch(url, {
        method: 'POST',
        body: JSON.stringify(data),
        headers: new Headers({
            'Content-Type': 'application/json'
        })
    })
    .then(function(response) {
        return response.json();
    })
    .catch(function(error) {
        console.log('Error: ' + error);
    })
    .then(function(ports) {
        alert("Room created successfully!");
        populateRoomList(ports);
    });
}

var joinEvent = (element, port) => {
    element.onclick = function() {
        window.location.href = `/playsbo?port=${port}&loginUserId=${currentLoginUserId}`
        console.log(port);
    }
}

function getRoomList() {
    var url = window.location.href + 'getportconnections';

    fetch(url)
    .then(function(response) {
        return response.json();
    })
    .catch(function(error) {
        console.log('Error: ' + error);
    })
    .then(function(ports) {
        console.log(ports);
        populateRoomList(ports);
    });
}

function populateRoomList(availablePorts) {
    gameRooms.innerHTML = `
    <tr>
        <th>Room Name</th>
        <th>Players</th>
        <th>Join</th>
    </tr>`;

    for (var key in availablePorts) {
        var currentPort = key;
        var gameRoomName = availablePorts[key].Name;
        var players = availablePorts[key].Players;
        gameRooms.innerHTML += `
            <tr>
                <td>${gameRoomName}: (Port: ${currentPort})</td>
                <td>(${players}/3)</td>
                <td><button class="roomJoin" data-port=${key}>Join</button></<td>
            </tr>`
    }

    var joinButtonElements = document.getElementsByClassName('roomJoin');

    for (var i = 0; i < joinButtonElements.length; i++) {
        joinEvent(joinButtonElements[i], joinButtonElements[i].attributes[1].value);
    };
}

getRoomList();