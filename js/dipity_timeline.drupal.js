(function ($) {
  Drupal.behaviors.dipityTimeline = {
    attach: function (context, settings) {
      $.each(settings.dipity_timeline, function(index, value) { 
        var canvas = document.getElementById('dipity-timeline-dom-id-' + index);
        var timeline = new dipity.widget(canvas, value);
      });
    }
  }
}(jQuery));