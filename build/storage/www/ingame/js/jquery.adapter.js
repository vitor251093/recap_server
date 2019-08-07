// Reference:
// https://stackoverflow.com/questions/4536788/override-jquery-functions

jQuery.fn.toggleClass = function(className, enable) {
    var hasClass = jQuery.fn.hasClass.apply(this, [className]);

    if (hasClass && (enable !== true)) {
        jQuery.fn.removeClass.apply(this, [className]);
        return;
    } 

    if (!hasClass && (enable !== false)) {
        jQuery.fn.addClass.apply(this, [className]);
    }
};