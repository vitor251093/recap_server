var DLSClient = {};
DLSClient.getRequest = function(url, callback, errorCallback) {
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
DLSClient.request = function(name, params, callback, errorCallback) {
    if (params !== undefined && typeof params === 'object') {
        var str = [];
        for (var p in params)
            if (params.hasOwnProperty(p)) {
                str.push(encodeURIComponent(p) + "=" + encodeURIComponent(params[p]));
            }
        params = str.join("&");
    }
    DLSClient.getRequest("http://{{host}}/dls/api?method=" + name + (params === undefined ? "" : ("&" + params)), callback, errorCallback);
};