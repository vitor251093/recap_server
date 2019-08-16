
var UI = function(domId) {
	return {
		dom: function() {
			var prefix = domId.substr(0,1);
			var realId = domId.substr(1);
			if (prefix === '#') return [document.getElementById(domId.substr(1))];
			if (prefix === '.') return  document.getElementsByClassName(domId.substr(1));
			return [];
		},
		show: function(show) {
			var doms = this.dom();
			for (var i = 0; i < doms.length; i++) doms[i].style.visibility = (show === undefined || show === true) ? "visible" : "hidden";
		},
		hide: function(hide) {
			var doms = this.dom();
			for (var i = 0; i < doms.length; i++) doms[i].style.visibility = (hide === undefined || hide === true) ? "hidden" : "visible";
		},
		text: function(text) {
			var doms = this.dom();
			for (var i = 0; i < doms.length; i++) doms[i].innerHTML = text;
		}
	};
};

var HTTP = {
	get: function(url, obj, callback, errorCallback) {
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
		xmlHttp.onload = function() {
			if (callback !== undefined) callback(xmlHttp.responseText);
		}
		xmlHttp.onerror = function(e) {
			if (errorCallback !== undefined) errorCallback(e, xmlHttp.responseText);
		};
		xmlHttp.open("GET", url + (params === undefined ? "" : ("?" + params)), true);
		xmlHttp.send(null);
	},
	post: function(url, obj, callback, errorCallback) {
		var xmlHttp = new XMLHttpRequest(); 
		xmlHttp.onload = function() {
			if (callback !== undefined) callback(xmlHttp.responseText);
		}
		xmlHttp.onerror = function(e) {
			if (errorCallback !== undefined) errorCallback(e, xmlHttp.responseText);
		};
		xmlHttp.open("POST", url, true);
		xmlHttp.setRequestHeader("Content-Type", "application/json;charset=UTF-8");
		xmlHttp.send(JSON.stringify(obj));
	}
}