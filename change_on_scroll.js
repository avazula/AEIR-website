$(function() {
    var header = $(".navbar");

    $(window).scroll(function() {
        var scroll = $(window).scrollTop();
        if (scroll >= 1000) {
            header.addClass("scrolled");
        } else {
            header.removeClass("scrolled");
        }
    });

});
