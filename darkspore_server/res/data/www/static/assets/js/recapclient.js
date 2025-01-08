var ReCapClient = {};
ReCapClient.recapApiUrl = "http://{{host}}/recap/api";
ReCapClient.getRequest = function(name, params, onSuccess, onError) {
    params["method"] = name;
    HTTP.get(ReCapClient.recapApiUrl, params, onSuccess, onError);
};
ReCapClient.postRequest = function(name, params, onSuccess, onError) {
    HTTP.post(ReCapClient.recapApiUrl + "?method=" + name, params, onSuccess, onError);
};
ReCapClient.log = function(str) {
    if (EAWebKit.isUserAgent()) {
        var isDev = ("{{isDev}}" === "true");    
        if (isDev) ReCapClient.postRequest("api.game.log", str);
    }
    else {
        console.log(str);
    }
};
