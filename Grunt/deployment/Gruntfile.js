"use strict";

module.exports = function (grunt) {
	grunt.config.init({
		copyFiles: {
			options: {
				workingDirectory: 'working',
				manifest: [
					'index.html', 'stylesheets/style.css', 'javascripts/app.js'
				]
			}
		}
	});

	grunt.registerTask('createFolder',
			'Create the working folder.', function () {
		grunt.config.requires('copyFiles.options.workingDirectory');

		grunt.file.mkdir(grunt.config.get('copyFiles.options.workingDirectory'));
	});

	grunt.registerTask('clean',
			'Deletes the working folder and its contents.', function () {
		grunt.config.requires('copyFiles.options.workingDirectory');

		grunt.file.delete(grunt.config.get('copyFiles.options.workingDirectory'));
	});

	grunt.registerTask('copyFiles',
			'Copy files to working directory.', function () {
		var files, workingDirectory;

		grunt.config.requires('copyFiles.options.workingDirectory');
		grunt.config.requires('copyFiles.options.manifest');

		files = grunt.config.get('copyFiles.options.manifest');
		workingDirectory = grunt.config.get('copyFiles.options.workingDirectory');

		files.forEach(function (file) {
			var destination = workingDirectory + '/' + file;
			grunt.log.writeln('copying ' + file + ' to ' + destination);
			grunt.file.copy(file, destination);
		});
	});

	grunt.registerTask('deploy',
			'Deploy files.', ['clean', 'createFolder', 'copyFiles']);
};
