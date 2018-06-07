var joinButton = document.getElementById('joinButton');

joinButton.onclick = function() {
    joinGame();
}

function joinGame() {
    window.location.href = '/playsbo';
}
