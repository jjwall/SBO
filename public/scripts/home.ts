// TO DO:
// 1. (done) set up Create Room functionality by posting to the server, server will figure out
// which port to set it up on (somewhere between 9000 and 9051). Node app will send response
// back to client once the .exe has been spun up, then populateRoomList will be called after success
// 2. (done) set up long polling that pings node server for availablePorts... this ping will also cause the node
// server to ping all running .exe servers and they will return the number of connections which node will
// update the portConnections struct with and then send back to client which will update room list accordingly
// 3. (done) Give dynamic "roomJoin" button functionality -> we will replace our dynamic routing to port system
// by using URL params instead. That's what the dynamic join buttons will route players to
// 4. (done) ensure that static pages can be run WITHOUT being hosted on node. I.e. the script sourcing on
// game.html needs to be scrapped entirely since we will no longer be using dynamic routes - not sure how
// to connect to socket straight from a file path
// -> this will also allow for easier game engine testing as we will not need to prop up node server and 
// go through "game room lobby" in order to test changes. Can just run .exe from command line... and should
// 5. (done) Set up promise for getting connections / room list
// be able to ignore the .exe client connection errors...
// 6. (done) Set up TypeScript
// 7. (done) Set up communcation layer: C++ sending messages to TypeScript
// 8. (done) Set up communication layer: TypeScript sending messages to C++
// 9. Set up entity class in C++ that registers connection handlers and stores player index
// -> this player index will be crucial, it will be the index that client game state uses to update data for all connected players
// --> it will also be used as a deciding factor to init an entity class as a player logs on
// i.e. if 3 players max can play, the 4th player that logs on won't have an instance of the entity class for them
// furthermore, player index will need to be dynamic as players disconnect
// 10. Set up hash table with connection_hdl as keys, entity players objects as values
// -> or just keep them in a list and run a for (auto& player : players) {} on them
// 11. Set up Pixi.js and get Type Declarations for it

// global home variable
var gh = {
    createRoomButton: <HTMLButtonElement>document.getElementById('createRoomButton'),
    gameRooms: <HTMLElement>document.getElementById('gameRooms'),
    roomNameInput: <HTMLButtonElement>document.getElementById('roomNameInput'),
    createRoomText: <HTMLElement>document.getElementById('createRoomText'),
    currentLoginUserId: <number>100000 // -> will get dynamically through user auth eventually...
}

gh.createRoomButton.onclick = function():void {
    createRoom();
}

// probably should replace all FETCH requests with XHR requests and check browser implementations of URLSearchParamss
// but also might not be worth it...
function createRoom():void {
    if (isNullOrWhitespace(gh.roomNameInput.value)) {
        return alert("Room Name field must have a value.");
    }

    gh.createRoomButton.disabled = true;
    gh.roomNameInput.disabled = true;
    gh.createRoomText.innerHTML = 'Creating Room...';

    var url = <string>window.location.href + 'creategameroom';
    var data = <object>{Name: gh.roomNameInput.value};

    fetch(url, {
        method: 'POST',
        body: JSON.stringify(data),
        headers: new Headers({
            'Content-Type': 'application/json'
        })
    })
    .then(function(response):Promise<any> {
        console.log("creating game room...");
        return response.json();
    })
    .catch(function(error):void {
        console.log('Error: ' + error);
    })
    .then(function(ports:JSON):void {
        gh.createRoomButton.disabled = false;
        gh.roomNameInput.disabled = false;
        gh.createRoomText.innerHTML = 'Room created successfully!';
        populateRoomList(ports);
    });
}

var joinEvent = (element:HTMLElement, port:String):void => {
    element.onclick = function() {
        window.location.href = `/playsbo?port=${port}&loginUserId=${gh.currentLoginUserId}`
        console.log(port);
    }
}

function getRoomList():void {
    var url = <string>window.location.href + 'getportconnections';

    fetch(url)
    .then(function(response):Promise<any> {
        return response.json();
    })
    .catch(function(error):void {
        console.log('Error: ' + error);
    })
    .then(function(ports:JSON):void {
        console.log(ports);
        populateRoomList(ports);
    });
}

function populateRoomList(portsDict:JSON):void {
    gh.gameRooms.innerHTML = `
    <tr>
        <th>Room Name</th>
        <th>Players</th>
        <th>Join</th>
    </tr>`;

    for (var key in portsDict) {
        var currentPort = <string>key;
        var gameRoomName = <string>portsDict[key].Name;
        var players = <number>portsDict[key].Connections;
        gh.gameRooms.innerHTML += `
            <tr>
                <td>${gameRoomName}: (Port: ${currentPort})</td>
                <td>(${players}/3)</td>
                <td><button class="roomJoin" data-port=${key}>Join</button></<td>
            </tr>`
    }

    var joinButtonElements = <HTMLCollectionOf<HTMLElement>>document.getElementsByClassName('roomJoin');

    for (var i = 0; i < joinButtonElements.length; i++) {
        joinEvent(joinButtonElements[i], joinButtonElements[i].attributes[1].value);
    };
}

function isNullOrWhitespace(input):boolean {
    if (typeof input === 'undefined' || input == null) {
        return true;
    }
    return input.replace(/\s/g, '').length < 1;
}

getRoomList();

setInterval(function() {
    getRoomList();
}, 60000);