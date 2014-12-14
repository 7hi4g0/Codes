'use strict';
const
	fs = require('fs'),
	spawn = require('child_process').spawn,
	filename = process.argv[2],
	command = process.argv[3] || 'ls';

if (!filename) {
	throw new Error('A file to watch must be specified!');
}

fs.watch(filename, function () {
	let
		ls = spawn(command, process.argv.slice(3).concat(filename)),
		output = '';

	ls.stdout.on('data', function (chunck) {
		output += chunck.toString();
	});

	ls.on('close', function () {
		process.stdout.write(output);
	});
});
console.log('Watching file ' + filename + ' for changes...');
