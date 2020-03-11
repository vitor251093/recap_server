
var EAWebKit = {
	isUserAgent: function() {
		return navigator.userAgent.indexOf("EAWebKit") != -1;
	},
	closeWindow: function() {
		if (EAWebKit.isUserAgent()) {
			Client.closeWindow();
		} else {
			window.close();
		}
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
	type: function(obj) {
		return Object.prototype.toString.call(obj);
	},
	isString: function(obj) {
		return Utils.type(obj) === '[object String]';
	},
	isArray: function(obj) {
		return Utils.type(obj) === '[object Array]';
	},
	splitVersionString: function(version) {
		if (version === undefined) return [];
		return version.split(".").map(function(num){ return parseInt(num); });
	},
	compareVersions: function(versionParts, versionArray) {
		if (Utils.isString(versionParts)) versionParts = Utils.splitVersionString(versionParts);
		if (Utils.isString(versionArray)) versionArray = Utils.splitVersionString(versionArray);

		var min = Math.min(versionParts.length, versionArray.length);
		for (var i = 0; i < min; i++) {
			if (versionParts[i] > versionArray[i]) return -1;
			if (versionParts[i] < versionArray[i]) return  1;
		}

		if (versionParts.length > versionArray.length) return -1;
		if (versionParts.length < versionArray.length) return  1;
		return 0;
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
