//
// EAWebKit jQuery
//
//   You may be wondering: why is there a custom jQuery for EAWebKit, instead of just using
//   an old version of jQuery? Well, I will tell you. EAWebKit is so different in some ways
//   that even older jQuery versions won't work properly in it.
//
//   This jQuery implementation was made specifically to support EAWebKit, and nothing else.
//

var _typeOf = function(obj) {
	var val = Object.prototype.toString.call(obj); // eg. '[object String]'
	return val.substr(8, val.length - 9).toLowerCase();
}

var _arrayOfElementsWithIdentifier = function(domId) {
	var _dom = null;
	if (_typeOf(domId) === "string") {
		var prefix = domId.substr(0,1);
		var realId = domId.substr(1);
		     if (prefix === '#') _dom = [document.getElementById(realId)];
		else if (prefix === '.') _dom =  document.getElementsByClassName(realId);
		else if (prefix === '<') _dom = [document.createElement(realId.substr(0, realId.length - 1))];
		else _dom = [];
	}
	else if (Array.isArray(domId)) {
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
		el.forEach(function(dom){ el[el.length++] = dom; });
		return el;
	};

	obj._mapClasses = function(func) {
		return this.forEach(function(dom){ 
			var classes = _arrayOfClassesWithClassesString(dom.className);
			classes = func(classes);
			dom.className = classes.join(" "); 
		});
	};
	obj.addClass = function(className) {
		return this._mapClasses(function(classesList){
			classesList.push(className);
			return classesList.filter(function(item, pos) {
				return classesList.indexOf(item) == pos;
			});
		});
	};
	obj.removeClass = function(className) {
		return this._mapClasses(function(classesList){
			return classesList.filter(function(item) {
				return className !== item;
			});
		});
	};
	obj.toggleClass = function(className, state) {
		if (state === true)  return this.addClass(className);
		if (state === false) return this.removeClass(className);
		return this._mapClasses(function(classesList){
			if (classesList.includes(className)) {
				return classesList.filter(function(item) {
					return className !== item;
				});
			}
			else {
				classesList.push(className);
				return classesList.filter(function(item, pos) {
					return classesList.indexOf(item) == pos;
				});
			}
		});
	};
	
	obj.append = function(el) {
		if (this._dom.length == 0) return;
		if (el === undefined || el === null) return;

		var dom = this._dom[0];
		if (el.length !== undefined) {
			el.forEach(function(rEl){dom.appendChild(rEl);});
			return;
		}
		dom.appendChild(el);
		return this;
	};
	obj.forEach = function(func) {
		this._dom.forEach(func);
		return this;
	};
	obj.attr = function(attrName, attrValue) {
		if (attrValue === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0][attrName];
		}
		// TODO: setAttribute does exist in browsers older than IE9, but with
		//  some inconsistent behaviors. It may need a polyfill on EAWebKit
		return this.forEach(function(dom){dom.setAttribute(attrName, attrValue)});
	};
	obj.removeAttr = function(attrName) {
		return this.forEach(function(dom){dom.removeAttribute(attrName)});
	};
	obj.children = function() {
		var newArray = [];
		this._dom.forEach(function(dom){ newArray = newArray.concat(Array.prototype.slice.call(dom.childNodes)) });
		return $(newArray);
	};
	obj.css = function(name, value) {
		if (value === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].style[name];
		}
		return this.forEach(function(dom){ dom.style[name] = value; });
	};
	obj.empty = function() {		
		return this.forEach(function(dom){ 
			while (dom.childNodes.length > 0) dom.removeChild(dom.childNodes[0]); 
		});
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
	obj.change = function(func) {
		return this.forEach(function(dom){ dom.onchange = func; });
	};
	obj.click = function(func) {
		return this.mouseUp(func);
	};
	obj.mouseUp = function(func) {
		return this.forEach(function(dom){ dom.addEventListener('mouseup', func); });
	};
	obj.html = function(text) {
		if (text === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].innerHTML;
		}
		return this.forEach(function(dom){dom.innerHTML = text});
	};
	obj.toggleChecked = function(value) {
		return this.forEach(function(dom){
			var tagName = dom.tagName.toUpperCase();
			var type = dom.type.toUpperCase();
			if (tagName === "INPUT" && type === "CHECKBOX") {
				dom.checked = (value === true || value === false) ? value : !dom.checked;
			}
		});
	};
	obj.val = function(value) {
		if (value === undefined) {
			if (this._dom.length == 0) return null;
			return this._dom[0].value;
		}
		return this.forEach(function(dom){ dom.value = value; });
	};

	return obj;
};

$.type = _typeOf;
