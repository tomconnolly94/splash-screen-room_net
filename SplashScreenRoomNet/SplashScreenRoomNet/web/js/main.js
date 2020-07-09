//alert(" it works boi!");

// delegate event for performance, and save attaching a million events to each anchor

var link_tags = document.getElementsByClassName("resource-link");

for (var i = 0; i < link_tags.length; i++) {

    link_tags[i].addEventListener('click', function (event) {
        event.preventDefault();
        window.open(this.getAttribute('href'), "_blank");
    }, false);

} 