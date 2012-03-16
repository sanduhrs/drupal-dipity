(function ($) {
  Drupal.behaviors.dipityTimeline = {
    attach: function (context, settings) {
      $.each(settings.dipity_timeline, function(index, value) { 
        console.log(index);
        console.log(value);
        var canvas = document.getElementById('dipity-timeline-dom-id-' + index);
        var timeline = new dipity.widget(canvas, value);
      });
    }
  }
}(jQuery));