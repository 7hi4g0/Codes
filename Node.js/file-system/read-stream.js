'use strict';
const
	fs = require('fs'),
	stream = fs.createReadStream(process.argv[2]);

stream.on('data', function (chunck) {
	process.stdout.write(chunck);
});


stream.on('error', function (err) {
	process.stderr.write('ERROR: ' + err.message + '\n');
});
