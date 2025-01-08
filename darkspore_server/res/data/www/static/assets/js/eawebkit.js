// Those are required by the bootstrap/launcher's index file, so it doesn't
// need to make a manual bridge between itself and the wrapper.html file
var Client = (typeof Client === 'undefined') ? (window.parent || {}).Client : Client;
var DarksporeVersion = (window.parent || {}).DarksporeVersion;

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



// Originally, we used .onload, but Darkspore 5.3.0.15 never
// calls .onload, and the readyState here never changes to 4,
// so it's done that way for backwards compatibility. We also
// can't add .onerror, because 5.3.0.15 will always call it

var HTTP = {
	get: function(url, obj, onSuccess, onError) {
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
			if (xmlHttp.readyState === 4) {
				if (xmlHttp.status >= 200 && xmlHttp.status < 300) {
					if (onSuccess) onSuccess(xmlHttp.responseText);
				} else {
					if (onError) onError(xmlHttp.status, xmlHttp.responseText);
				}
			}
		};
		xmlHttp.open("GET", url + (params === undefined ? "" : ("?" + params)), true);
		xmlHttp.send(null);
	},
	post: function(url, obj, onSuccess, onError) {
		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onreadystatechange = function () {
			if (xmlHttp.readyState === 4) {
                if (xmlHttp.status >= 200 && xmlHttp.status < 300) {
                    if (onSuccess) onSuccess(xmlHttp.responseText);
                } else {
                    if (onError) onError(xmlHttp.status, xmlHttp.responseText);
                }
            }
		};
		xmlHttp.open("POST", url, true);
		xmlHttp.setRequestHeader("Content-Type", "application/json");
		xmlHttp.send(JSON.stringify(obj));
	}
};
