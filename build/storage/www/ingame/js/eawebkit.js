
var EAWebKit = {
	isUserAgent: function() {
		return navigator.userAgent.indexOf("EAWebKit") != -1;
	},
	openExternalBrowser: function(url) {
		if (EAWebKit.isUserAgent()) {
			Client.openExternalBrowser(url);
		} else {
			window.open(url);
		}
	}
};



var Utils = {
	filter: function(array, func) {
		var newArray = [];
		for (var i = 0; i < array.length; i++) if (func(array[i], i)) newArray.push(array[i]);
		return newArray;
	},
	forEach: function(array, func) {
		for (var i = 0; i < array.length; i++) func(array[i], i)
	},
	map: function(array, func) {
		var newArray = [];
		for (var i = 0; i < array.length; i++) newArray.push(func(array[i], i));
		return newArray;
	},
	type: function(obj) {
		return Object.prototype.toString.call(obj);
	},
	isString: function(obj) {
		return Utils.type(obj) === '[object String]';
	},
	isArray: function(obj) {
		return Utils.type(obj) === '[object Array]';
	}
};



// Originally, we used .onload, but Darkspore 5.3.0.15 never
// calls .onload, and the readyState here never changes to 4,
// so it's done that way for backwards compatibility. We also
// can't add .onerror, because 5.3.0.15 will always call it

var HTTP = {
	get: function(url, obj, callback) {
		var params = obj;
		if (params !== undefined && typeof params === 'object') {
			var str = [];
			for (var p in params)
				if (params.hasOwnProperty(p)) {
					str.push(encodeURIComponent(p) + "=" + encodeURIComponent(params[p]));
				}
			params = str.join("&");
		}

		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onreadystatechange = function () {
			if (xmlHttp.status === 200 && callback !== undefined) callback(xmlHttp.responseText);
		};
		xmlHttp.open("GET", url + (params === undefined ? "" : ("?" + params)), true);
		xmlHttp.send(null);
	},
	post: function(url, obj, callback) {
		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onreadystatechange = function () {
			if (xmlHttp.status === 200 && callback !== undefined) callback(xmlHttp.responseText);
		};
		xmlHttp.open("POST", url, true);
		xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
		xmlHttp.send(JSON.stringify(obj));
	}
};
