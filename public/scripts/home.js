// TO DO:
// 1. set up Create Room functionality by posting to the server, server will figure out
// which port to set it up on (somewhere between 9000 and 9051). Node app will send response
// back to client once the .exe has been spun up, then populateRoomList will be called after success
// 2. set up long polling that pings node server for availablePorts... this ping will also cause the node
// server to ping all running .exe servers and they will return the number of connections which node will
// update the portConnections struct with and then send back to client which will update room list accordingly
// 3. Give dynamic "roomJoin" button functionality -> we will replace our dynamic routing to port system
// by using URL params instead. That's what the dynamic join buttons will route players to
// 4. ensure that static pages can be run WITHOUT being hosted on node. I.e. the script sourcing on
// game.html needs to be scrapped entirely since we will no longer be using dynamic routes
// -> this will also allow for easier game engine testing as we will not need to prop up node server and 
// go through "game room lobby" in order to test changes. Can just run .exe from command line... and should
// be able to ignore the .exe client connection errors...
// 5. Set up TypeScript
// 6. Set up Pixi.js and get Type Declarations for it
// 7. Begin working on engine...

var createRoomButton = document.getElementById('createRoomButton');
var gameRooms = document.getElementById('gameRooms');

createRoomButton.onclick = function() {
    createRoom();
}

function createRoom() {
    // window.location.href = '/playsbo';
    console.log("Attempting to create a room...");
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
                        <td><button class="roomJoin" data-index=${5}>Join</button></<td>
                    </tr>`
            }
        });
    
    // $('.roomJoin').each(function() {
    //     $(this).on("click", function(event){
    //         event.preventDefault();
    //         var gameRoute = $(this).data('index');
    //         window.location.href = '/' + gameRoute;
    //         //console.log(gameNum);
    //     });
    // });
}

populateRoomList();