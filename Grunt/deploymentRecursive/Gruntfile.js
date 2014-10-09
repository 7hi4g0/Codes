"use strict";

module.exports = function (grunt) {
	grunt.config.init({
		pkg: grunt.file.readJSON('package.json'),
		copyFiles: {
			options: {
				workingDirectory: 'working',
				manifest: [
					'index.html', 'stylesheets/', 'javascripts/'
				]
			}
		}
	});

	var recursiveCopy = function (source, destination) {
		if (grunt.file.isDir(source)) {

			grunt.file.recurse(source, function (file) {
				recursiveCopy(file, destination);
			});

		} else {
			grunt.log.writeln('copying ' + source + ' to ' + destination);
			grunt.file.copy(source, destination + '/' + source);
		}
	};

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
			recursiveCopy(file, workingDirectory);
		});

		var content = '<%= pkg.name %> version <%= pkg.version %>';
		content = grunt.template.process(content);
		grunt.file.write(workingDirectory + '/version.txt', content);
	});

	grunt.registerTask('deploy',
			'Deploy files.', ['clean', 'createFolder', 'copyFiles']);
};
