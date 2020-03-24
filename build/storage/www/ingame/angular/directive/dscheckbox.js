app.directive("dscheckbox", function() {
    return {
        restrict: 'E',
        transclude: true,
        replace: true,
        scope: {
            'ngModel': '='
        },
        controller: ['$scope', function($scope) {
            $scope.toggle = function() {
                $scope.ngModel = !$scope.ngModel;
            };
        }],
        template :  "<span class=\"input-checkbox-container\">" +
                    "    <input type=\"checkbox\" ng-model=\"ngModel\" />" +
                    "    <span class=\"checkmark\" ng-mouseup=\"toggle()\"></span>" +
                    "    <label ng-transclude></label>" +
                    "</span>"
    };
});