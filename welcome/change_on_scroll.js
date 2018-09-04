$(function() {
    var header = $(".navbar");

    $(window).scroll(function() {
        var scroll = $(window).scrollTop();
        if (scroll >= window.innerHeight) {
            header.addClass("scrolled");
        } else {
            header.removeClass("scrolled");
        }
    });

});
