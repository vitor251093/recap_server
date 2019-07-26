$(function() {
    if (window.PIE) {
        $('.button-rounded').each(function() {
            PIE.attach(this);
        });
    }
});