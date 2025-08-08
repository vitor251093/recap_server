var ReCapClient = {};
ReCapClient.recapApiUrl = "http://{{host}}/recap/api";
ReCapClient.getRequest = function(name, params, onSuccess, onError) {
    params = (params === undefined || params === null) ? {} : params;
    params["method"] = name;
    HTTP.get(ReCapClient.recapApiUrl, params, onSuccess, onError);
};
ReCapClient.postRequest = function(name, params, onSuccess, onError) {
    params = (params === undefined || params === null) ? {} : params;
    HTTP.post(ReCapClient.recapApiUrl + "?method=" + name, params, onSuccess, onError);
};
ReCapClient.log = function(str) {
    if (window.isEAWebKit) {
        var isDev = ("{{isDev}}" === "true");    
        if (isDev) ReCapClient.postRequest("api.game.log", str);
    }
    else {
        console.log(str);
    }
};

if (window.isEAWebKit) {
    var console = {}
    console.log = function(str) {
        ReCapClient.log(str)
    }
    console.info = function(str) {
        ReCapClient.log(str)
    }
    console.warn = function(str) {
        ReCapClient.log(str)
    }
    console.error = function(str) {
        ReCapClient.log(str)
    }
}