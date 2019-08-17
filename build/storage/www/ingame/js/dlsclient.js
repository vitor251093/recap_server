var DLSClient = {};
DLSClient.dlsApiUrl = "http://{{host}}/dls/api";
DLSClient.getRequest = function(name, params, callback, errorCallback) {
    params["method"] = name;
    HTTP.get(DLSClient.dlsApiUrl, params, callback, errorCallback);
};
DLSClient.postRequest = function(name, params, callback, errorCallback) {
    HTTP.post(DLSClient.dlsApiUrl + "?method=" + name, params, callback, errorCallback);
};
DLSClient.log = function(object) {
    //var isDev = {{isDev}};
    //if (isDev) 
	DLSClient.postRequest("api.game.log", object);
};
