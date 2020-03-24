app.directive("dsmodal", function() {
    return {
        restrict: 'E',
        transclude: true,
        scope: {
            'title': '@'
        },
        template :  "<div class=\"body modal\">" +
                    "    <div class=\"modal-window\">" +
                    "        <img src=\"/ingame/images/register_bg.png\" class=\"fullscreen-background\"/>" +
                    "        <div class=\"modal-title darkspore-font\">{{title}}</div>" +
                    "        <div ng-transclude></div>" +
                    "    </div>" +
                    "</div>"
    };
});