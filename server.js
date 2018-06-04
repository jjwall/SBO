var express = require('express');
// var bodyParser = require('body-parser');
var path = require('path');
// var fs = require('fs');

var app = express();
var PORT = process.env.PORT || 8080;

// Sets up the Express app to handle data parsing
// app.use(bodyParser.json());

app.use(express.static('./public'));

app.get("/", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/game.html"));
});

app.listen(PORT, function () {
	console.log(`app listening on port ${PORT}`);
});