"use strict";

module.exports = function (grunt) {
	grunt.registerTask('default',
			'Prints an excited message.', function () {
		grunt.log.writeln("It worked!");
	});
};
