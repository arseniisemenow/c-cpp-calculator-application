let srcs = [
    "media/expression_calculator.gif",
    "media/graph_calculator.gif",
    "media/credit_calculator.gif",
    "media/deposit_calculator.gif",
]

function resizeGif(srcField, width) {
    var observer = new MutationObserver(function (mutationsList, observer) {
        for (var mutation of mutationsList) {
            if (mutation.addedNodes.length > 0) {
                var gifImage = document.querySelector(`img[src="${srcField}"]`);
                if (gifImage) {
                    gifImage.width = width;
                    // gifImage.height = 150;
                    observer.disconnect();
                }
            }
        }
    });

    // Start observing the body of the document
    observer.observe(document.body, { childList: true, subtree: true });
}

// Call resizeGif for each source in the srcs array
resizeGif(srcs[0], 350);
resizeGif(srcs[1], 350);
resizeGif(srcs[2], 350);
resizeGif(srcs[3], 1250);