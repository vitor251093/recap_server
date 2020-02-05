var ReCapClient = {};
ReCapClient.recapApiUrl = "http://{{host}}/recap/api";
ReCapClient.getRequest = function(name, params, callback, errorCallback) {
    params["method"] = name;
    HTTP.get(ReCapClient.recapApiUrl, params, callback, errorCallback);
};
ReCapClient.postRequest = function(name, params, callback, errorCallback) {
    HTTP.post(ReCapClient.recapApiUrl + "?method=" + name, params, callback, errorCallback);
};
ReCapClient.log = function(object) {
    if (EAWebKit.isUserAgent()) {
        var isDev = ("{{isDev}}" === "true");    
        if (isDev) ReCapClient.postRequest("api.game.log", object);
    }
    else {
        console.log(object);
    }
};
