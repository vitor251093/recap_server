
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
                