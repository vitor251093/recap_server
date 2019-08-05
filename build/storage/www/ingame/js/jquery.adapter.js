// Reference:
// https://stackoverflow.com/questions/4536788/override-jquery-functions

jQuery.fn.toggleClass = function(className, enable) {
    var hasClass = jQuery.fn.hasClass.apply(this, [className]);

    if (hasClass && (enable !== true)) {
        var classList = this.className.split(" ");

        var index = classList.indexOf(className);
        while (index > -1) {
            classList.splice(index, 1);
            index = classList.indexOf(className);
        }

        this.className = classList.join(" ");
        return;
    } 

    if (!hasClass && (enable !== false)) {
        this.className += " " + className;
    }
};