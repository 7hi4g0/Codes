/*global TERRAIN*/

var TERRAIN;

TERRAIN = {};

(function () {
	var gl;

	TERRAIN.gl = gl = null;
	TERRAIN.canvas = null;

	TERRAIN.init = function () {
		TERRAIN.canvas = document.querySelector("#glcanvas");

		initWebGL();
		initShaders();
	};

	function initWebGL() {
		TERRAIN.gl = gl = TERRAIN.canvas.getContext("webgl");

		gl.clearColor(0.0, 0.0, 0.0, 1.0);
		gl.enable(gl.DEPTH_TEST);
		gl.depthFunc(gl.LEQUAL);
		gl.viewport(0, 0, TERRAIN.canvas.width, TERRAIN.canvas.height);
		gl.clear(gl.COLOR_BUFFER_BIT, gl.DEPTH_BUFFER_BIT);
	}

	function initShaders() {
		var vertesShader,
			fragmentShader;

		vertexShader = getShader("shader-vs");
		fragmentShader = getShader("shader-fs");
	}
}());

window.onload = TERRAIN.init;
