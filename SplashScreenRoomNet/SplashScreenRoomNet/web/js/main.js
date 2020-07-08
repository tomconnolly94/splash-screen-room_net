//alert(" it works boi!");

// delegate event for performance, and save attaching a million events to each anchor

var link_tags = document.getElementsByClassName("resource-link");

for (var i = 0; i < link_tags.length; i++) {

    link_tags[i].addEventListener('click', function (event) {

        event.preventDefault();

        var target = this;
        if (target.tagName.toLowerCase() == 'a') {
            var port = target.getAttribute('href').match(/^(.*):(\d+)(.*)/);
            if (port) {
                window.location.port = port[2];
                window.location = port[1];
            }
        }
    }, false);

} 