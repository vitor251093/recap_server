
var _arrayOfElementsWithIdentifier = function(domId) {
	var _dom = null;
	if (Utils.isString(domId)) {
		var prefix = domId.substr(0,1);
		var realId = domId.substr(1);
		     if (prefix === '#') _dom = [document.getElementById(realId)];
		else if (prefix === '.') _dom =  document.getElementsByClassName(realId);
		else _dom = [];
	}
	else if (Utils.isArray(domId)) {
		_dom = domId;
	} 
	else {
		_dom = [domId];
	}
	return _dom;
};
var _arrayOfClassesWithClassesString = function(classesString) {
	var classes = classesString.split(" ");
	while(classes.indexOf('') != -1) classes.splice(classes.indexOf(''), 1);
	return classes;
};

var $ = function(domId) {
	var obj = {};

	var _dom = _arrayOfElementsWithIdentifier(domId);
	obj.length = 0;
	_dom.forEach(function(dom){ obj[obj.length++] = dom; });
	obj._dom = _dom;

	obj.add = function(newDomId) {
		var el = $(domId);
		el._dom.push(_arrayOfElementsWithIdentifier(newDomId));
		el._dom.forEach(function(dom){ el[el.length++] = dom; });
		return el;
	};
	obj._mapClasses = function(func) {
		this._dom.forEach(function(dom){ 
			var classes = _arrayOfClassesWithClassesString(dom.className);
			classes = func(classes);
			dom.className = classes.join(" "); 
		});
		return this;
	};
	obj.addClass = function(className) {
		return this._mapClasses(function(classesList){
			classesList.push(className);
			var classes = classesList.filter(function(item, pos) {
				return classes.indexOf(item) == pos;
			});
			return classes;
		});
	};
	obj.removeClass = function(className) {
		return this._mapClasses(function(classesList){
			var classes = classesList.filter(function(item) {
				return className !== item;
			});
			return classes;
		});
	};
	obj.toggleClass = function(className, state) {
		if (state === true)  return this.addClass(className);
		if (state === false) return this.removeClass(className);
		return this._mapClasses(function(classesList){
			if (classesList.includes(className)) {
				var classes = classesList.filter(function(item) {
					return className !== item;
				});
				return classes;
			}
			else {
				classesList.push(className);
				var classes = classesList.filter(function(item, pos) {
					return classes.indexOf(item) == pos;
				});
				return classes;
			}
		});
	};
	obj.attr = function(attrName, attrValue) {
		if (attrValue === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0][attrName];
		}
		this._dom.forEach(function(dom){dom[attrName] = attrValue});
		return this;
	};
	obj.children = function() {
		var newArray = [];
		this._dom.forEach(function(dom){ newArray = newArray.concat(dom.childNodes) });
		return $(newArray);
	};
	obj.click = function(func) {
		this._dom.forEach(function(dom){ dom.onmouseup = func });
		return this;
	};
	obj.css = function(name, value) {
		if (value === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].style[name];
		}
		this._dom.forEach(function(dom){ dom.style[name] = value; });
		return this;
	};
	obj.empty = function() {		
		this._dom.forEach(function(dom){ 
			while (dom.childNodes.length > 0) dom.removeChild(dom.childNodes[0]); 
		});
		return this;
	};
	obj.get = function(index) {
		return this._dom[index];
	};
	obj.show = function(show) {
		return this.css('visibility', ((show === undefined || show === true) ? "visible" : "hidden"));
	};
	obj.hide = function(hide) {
		return this.css('visibility', ((hide === undefined || hide === true) ? "hidden" : "visible"));
	};
	obj.html = function(text) {
		if (text === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].innerHTML;
		}
		this._dom.forEach(function(dom){dom.innerHTML = text});
		return this;
	};
	obj.toggleChecked = function(value) {
		this._dom.forEach(function(dom){
			var tagName = dom.tagName.toUpperCase();
			var type = dom.type.toUpperCase();
			if (tagName === "INPUT" && type === "CHECKBOX") {
				dom.checked = (value === true || value === false) ? value : !dom.checked;
			}
		});
		return this;
	};
	obj.val = function(value) {
		if (value === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].value;
		}
		this._dom.forEach(function(dom){ dom.value = value; });
		return this;
	};

	return obj;
};
