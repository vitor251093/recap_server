
var Utils = {
	forEach: function(array, func) {
		for (var i = 0; i < array.length; i++) func(array[i])
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

var UI = function(domId) {
	return {
		dom: function() {
			if (Utils.isString(domId)) {
				var prefix = domId.substr(0,1);
				var realId = domId.substr(1);
				if (prefix === '#') return [document.getElementById(realId)];
				if (prefix === '.') return  document.getElementsByClassName(realId);
				return [];
			}
			if (Utils.isArray(domId)) {
				return domId;
			}
			return [domId];
		},
		show: function(show) {
			this.style({visibility: ((show === undefined || show === true) ? "visible" : "hidden")});
		},
		hide: function(hide) {
			this.style({visibility: ((hide === undefined || hide === true) ? "hidden" : "visible")});
		},
		text: function(text) {
			Utils.forEach(this.dom(),function(dom){dom.innerHTML = text});
		},
		style: function(obj) {
			Utils.forEach(this.dom(),function(dom){for (var p in obj) dom.style[p] = obj[p]});
		}
		// animate: function(style, fromValue, toValue, time, framerate, valueParser) {
		// 	if (framerate === undefined) framerate = 30;
			
		// 	var value = fromValue;
		// 	var actionChange = (((fromValue - value)*1.0)/framerate)/(time/1000.0);
		// 	var actionTime = 1000.0/framerate;

		// 	if (value < toValue) {
		// 		value += actionChange;

		// 		var doms = this.dom();
		// 		setTimeout(function(){
		// 			UI(doms).animate(style, value, toValue, time - actionTime, framerate);
		// 		}, actionTime);
		// 	}
			
		// 	var styleObj = {};
		// 	styleObj[style] = (valueParser === undefined) ? value : valueParser(value);
		// 	this.style(styleObj);
		// }
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
};
