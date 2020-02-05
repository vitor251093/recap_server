var ReCapClient = {};
ReCapClient.recapApiUrl = "http://{{host}}/recap/api";
ReCapClient.getRequest = function(name, params, callback) {
    params["method"] = name;
    HTTP.get(ReCapClient.recapApiUrl, params, callback);
};
ReCapClient.postRequest = function(name, params, callback) {
    HTTP.post(ReCapClient.recapApiUrl + "?method=" + name, params, callback);
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
