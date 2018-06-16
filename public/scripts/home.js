// TO DO:
// 1. set up Create Room functionality by posting to the server, server will figure out
// which port to set it up on (somewhere between 9000 and 9051). Node app will send response
// back to client once the .exe has been spun up, then populateRoomList will be called after success
// 2. set up long polling that pings node server for availablePorts... this ping will also cause the node
// server to ping all running .exe servers and they will return the number of connections which node will
// update the portConnections struct with and then send back to client which will update room list accordingly
// 3. Give dynamic "roomJoin" button functionality -> we will replace our dynamic routing to port system
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
var currentLoginUserId = 100000 // -> will get dynamically through user auth eventually...

createRoomButton.onclick = function() {
    createRoom();
}

// -> this is the event that will send an ajax request to the Node app to spin up the "next" server in line
// i.e. if servers, 9001, 9002, & 9003 are spun up already, then node app will need to spin up 9004 with the
// next time a user triggers this event. Pretty much, the functionality from the GET request on dynamic
// route "/playsbo:port" will be replaced with a POST request "/creategameroom" etc.
// probably should replace all FETCH requests with XHR requests and check browser implementations of URLSearchParamss
// but also might not be worth it...
function createRoom() {
    // window.location.href = '/playsbo';
    console.log("Attempting to create a room...");
}

var joinEvent = (element, port) => {
    element.onclick = function() {
        window.location.href = `/playsbo?port=${port}&loginUserId=${currentLoginUserId}`
        console.log(port);
    }
}

function populateRoomList() {
    var url = window.location.href + 'getportconnections';

    fetch(url)
        .then(function(response) {
            return response.json();
        })
        .catch(function(error) {
            console.log('Error: ' + error);
        })
        .then(function(availablePorts) {
            console.log(availablePorts);
            gameRooms.innerHTML = `
                <tr>
                    <th>Port #</th>
                    <th>Players</th>
                    <th>Join</th>
                </tr>`;

            for (var key in availablePorts) {
                var currentPort = key;
                var players = availablePorts[key];
                gameRooms.innerHTML += `
                    <tr>
                        <td>${currentPort}</td>
                        <td>(${players}/3)</td>
                        <td><button class="roomJoin" data-port=${key}>Join</button></<td>
                    </tr>`
            }

            var joinButtonElements = document.getElementsByClassName('roomJoin');

            for (var i = 0; i < joinButtonElements.length; i++) {
                joinEvent(joinButtonElements[i], joinButtonElements[i].attributes[1].value);
            };
    });
}

populateRoomList();