var express = require('express');
var path = require('path');
var cp = require('child_process');
// var bodyParser = require('body-parser');
// var fs = require('fs');

var app = express();
var PORT = process.env.PORT || 8080;

// Sets up the Express app to handle data parsing
// app.use(bodyParser.json());

app.use(express.static('./public'));

app.get("/", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/game.html"));
});

app.get("/playsbo", function(req, res) {
	res.sendFile(path.join(__dirname, "/public/game.html"));
	// cp.execFile("./build_native/sbo.exe", ["9001"], function(err, stdout, stderr) {
	// 	console.log(err);
	// 	console.log(stdout);
	// 	console.log(stderr);
	// }); 
	var child = cp.spawn("./build_native/sbo.exe", ["9001"]);
	child.stdout.on('data', function(data) {
		console.log(data.toString());
	});
});

app.listen(PORT, function () {
	console.log(`Node app listening on port ${PORT}`);
});