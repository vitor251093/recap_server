app.controller('registerCtrl', function($scope, $timeout) {
    $scope.isLoading = false;

    $scope.showMessageDialog = false;
    $scope.messageDialogTitle = "Error";
    $scope.messageDialogMessage = "x";
    $scope.closeWindowOnMessageClose = true;

    $scope.showModal = function(title, message, closingWindow) {
        $scope.showMessageDialog = true;
        $scope.messageDialogTitle = title;
        $scope.messageDialogMessage = message;
        $scope.closeWindowOnMessageClose = closingWindow;
    };
    $scope.closeModal = function() {
        $scope.showMessageDialog = false;
        
        if ($scope.closeWindowOnMessageClose) {
            EAWebKit.closeWindow();
        }
    };

    $scope.showAvatarDialog = false;
    $scope.avatarsById = [
        {id:15, code:'98187F20'},
        {id:14, code:'98187F21'},
        {id:16, code:'98187F23'},
        {id:11, code:'98187F24'},
        {id:10, code:'98187F25'},
        {id:13, code:'98187F26'},
        {id:12, code:'98187F27'},
        {id:6,  code:'626285B0'},
        {id:7,  code:'626285B1'},
        {id:4,  code:'626285B2'},
        {id:5,  code:'626285B3'},
        {id:2,  code:'626285B4'},
        {id:3,  code:'626285B5'},
        {id:0,  code:'626285B6'},
        {id:1,  code:'626285B7'},
        {id:8,  code:'626285BE'},
        {id:9,  code:'626285BF'}
    ];
    $scope.selectedAvatar = $scope.avatarsById.filter(function(avatar){return avatar.id === 0;})[0];
    $scope.selectAvatar = function(avatar) {
        $scope.selectedAvatar = avatar;  
    };
    $scope.toggleAvatarDialog = function() {
        $scope.showAvatarDialog = !$scope.showAvatarDialog;
    };


    $scope.showTerms = function() {
        EAWebKit.openExternalBrowser('http://tos.ea.com/legalapp/WEBTERMS/us/en/PC/Darkspore');
    };


    $scope.name = "";
    $scope.email = ""
    $scope.password = "";
    $scope.agreeTerms = false;

    $scope.register = function() {
        if (!$scope.agreeTerms) {
            $scope.showModal('Error', "You must agree with the terms to proceed!", false);
            return;
        }

        $scope.isLoading = true;

        ReCapClient.getRequest("api.game.registration", {
            name:   $scope.name,
            mail:   $scope.email,
            pass:   $scope.password,
            avatar: $scope.selectedAvatar.id
        }, 
        function(data) {
            var response = JSON.parse(data);

            $timeout(function(){
                if (response.stat === true || response.stat === 'ok') {
                    $scope.showModal('Success', "Account created successfully!", true);
                } else {
                    $scope.isLoading = false;
                    $scope.showModal('Error', "Your account could not be created!", false);
                }
            },0);
        });
    };
});