app.directive("dsbutton", function() {
    return {
        restrict: 'E',
        transclude: true,
        scope: {
            'ngClick': '&',
            'title': '@'
        },
        template : "<div class=\"dsbutton\" ng-mouseup=\"ngClick\">" +
                   "    <div class=\"left-side\"></div>" +
                   "    <div class=\"text\">{{title}}</div>" +
                   "    <div class=\"right-side\"></div>" +
                   "</div>"
    };
});