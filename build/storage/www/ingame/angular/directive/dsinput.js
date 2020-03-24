app.directive("dsinput", function() {
    return {
        restrict: 'E',
        scope: {
            'ngModel': '=',
            'maxlength': '@',
            'type': '@'
        },
        template : "<div class=\"form-input-bg\" ng-if=\"type === 'text'\">" + 
                   "    <input type=\"text\" class=\"form-input\" ng-model=\"ngModel\"" + 
                   "           ng-style=\"{color: ((maxlength !== undefined && ngModel.length > maxlength) ? 'yellow' : 'white')}\"/>" + 
                   "</div>" + 
                   "<div class=\"form-input-bg\" ng-if=\"type === 'password'\">" + 
                   "    <input type=\"text\" class=\"form-input password\" ng-model=\"ngModel\"" + 
                   "           ng-style=\"{color: ((maxlength !== undefined && ngModel.length > maxlength) ? 'yellow' : 'white')}\"/>" + 
                   "</div>"
    };
});