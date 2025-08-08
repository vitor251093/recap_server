var Client = (typeof Client === 'undefined') ? (window.parent || {}).Client : Client;
var DarksporeVersion = (window.parent || {}).DarksporeVersion;

var isEAWebKitUserAgent = navigator.userAgent.indexOf("EAWebKit") != -1;
if (isEAWebKitUserAgent) {
    var window = {}
    window.isEAWebKit = true
    window.close = function () {
        if (Client.closeWindow) {
            Client.closeWindow();
        }
        if (Client.closeCurrentApp) {
            Client.closeCurrentApp();
        }
    }
    window.minimize = function() {
        Client.minCurrentApp();
    }
    window.open = function(url) {
        Client.openExternalBrowser(url);
    }
}
else {
    window.isEAWebKit = false
    window.minimize = function () {
        console.log("Can't minimize a browser tab")
    }
}