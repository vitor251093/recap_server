var DLSClient = {};
DLSClient.dlsApiUrl = "http://{{host}}/dls/api";
DLSClient.rawGetRequest = function(url, callback, errorCallback) {
    var xmlHttp = new XMLHttpRequest(); 
    xmlHttp.onload = function() {
        if (callback !== undefined) callback(xmlHttp.responseText);
    }
    xmlHttp.onerror = function(e) {
        if (errorCallback !== undefined) errorCallback(e, xmlHttp.responseText);
    };
    xmlHttp.open("GET", url, true);
    xmlHttp.send(null);
};
DLSClient.rawPostRequest = function(url, obj, callback, errorCallback) {
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
};
DLSClient.getRequest = function(name, params, callback, errorCallback) {
    if (params !== undefined && typeof params === 'object') {
        var str = [];
        for (var p in params)
            if (params.hasOwnProperty(p)) {
                str.push(encodeURIComponent(p) + "=" + encodeURIComponent(params[p]));
            }
        params = str.join("&");
    }
    DLSClient.rawGetRequest(DLSClient.dlsApiUrl + "?method=" + name + (params === undefined ? "" : ("&" + params)), callback, errorCallback);
};
DLSClient.postRequest = function(name, params, callback, errorCallback) {
    DLSClient.rawPostRequest(DLSClient.dlsApiUrl + "?method=" + name, params, callback, errorCallback);
};
DLSClient.log = function(object) {
    //var isDev = {{isDev}};
    //if (isDev) 
	DLSClient.postRequest("api.game.log", object);
};
