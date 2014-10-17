'use strict';

module.exports = function (grunt) {
	var chromeLauncher = require('./lib/chrome_launcher.js').init(grunt);
	grunt.registerTask('open',
			'Opens the file or URL with Chrome.', function (file) {
		var done = this.async();
		chromeLauncher.open(file, done);
	});
};
