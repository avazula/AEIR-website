// get the value of the bottom of the #main element by adding the offset of that element plus its height, set it as a variable
// var mainbottom = $('#main').offset().top + $('#main').height();
//
// // on scroll,
// $(window).on('scroll',function(){
//
//     // we round here to reduce a little workload
//     stop = Math.round($(window).scrollTop());
//     if (stop > mainbottom) {
//         $('.nav').addClass('past-main');
//     } else {
//         $('.nav').removeClass('past-main');
//    }
//
// });

$(document).ready(function(){
  $(window).scroll(function(){
  	var scroll = $(window).scrollTop();
	  if (scroll > 300) {
	    // $(".black").css("background" , "blue");
	  }

	  else{
		  $(".nav").css("background" , "#e2251b");  	
	  }
  })
})
