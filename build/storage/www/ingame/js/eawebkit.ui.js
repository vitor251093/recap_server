
var UI = function(domId) {
	return {
		dom: function() {
			return document.getElementById(domId.substr(1));
		},
		show: function(show) {
			this.dom().style.visibility = (show === undefined || show === true) ? "visible" : "hidden";
		},
		hide: function(hide) {
			this.dom().style.visibility = (hide === undefined || hide === true) ? "hidden" : "visible";
		},
		text: function(text) {
			this.dom().innerHTML = text;
		}
	};
};
                