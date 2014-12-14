http = require('http');

var opts = {
	host: 'proxy.addr',
	port: 3128,
	path: 'http://api.openweathermap.org/data/2.5/weather?q=69060000',
	method: 'GET',
	headers: {
		Host: 'api.openweathermap.org',
		'Proxy-Authorization': 'Basic ' + (new Buffer('user:pass')).toString('base64')
	}
};

var data;
var req = http.request(opts, function (res) {
	var buffer = [];

	res.on('data', function (d) {
		buffer.push(d);
	});

	res.on('end', function () {
		data = JSON.parse(buffer.join());

		console.log(data);
	});
});

req.end();
