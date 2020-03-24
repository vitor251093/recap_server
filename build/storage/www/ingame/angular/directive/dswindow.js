app.directive("dswindow", function() {
    return {
        restrict: 'E',
        transclude: true,
        scope: {},
        template :  "<div class=\"body\">" +
                    "    <div class=\"fullscreen-window\">" +
                    "        <img src=\"/ingame/images/register_bg.png\" class=\"fullscreen-background\"/>" +
                    "        <div class=\"view\" ng-transclude></div>" +
                    "    </div>" +
                    "</div>"
    };
});