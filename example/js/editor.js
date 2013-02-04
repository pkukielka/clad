(function () {
    var Range = ace.require('ace/range').Range
    var editor = ace.edit("editor");
    var timer, timeout = 500;

    editor.setTheme("ace/theme/monokai");
    editor.setFontSize("16px");
    editor.getSession().setMode("ace/mode/c_cpp");

    function addMarker(warning) {
        var range = new Range(warning.row, warning.column, warning.row, warning.column + warning.offset);
        editor.getSession().addMarker(range, "error", "error");
    }

    function removeAllMarkers() {
        var markers = editor.getSession().getMarkers();
        for (i in markers) {
            if (markers[i].type == "error") {
                editor.getSession().removeMarker(markers[i].id);
            }
        }
    }

    function displayDiagnostics(diagnostics) {
        removeAllMarkers();
        editor.getSession().setAnnotations(diagnostics);

        for (i in diagnostics) {
            addMarker(diagnostics[i]);
        }
    }

    function requestDiagnostics() {
        worker.postMessage(editor.getValue());
    }

    var worker = new Worker('js/clad.js');
    worker.onmessage = function(event) {
        displayDiagnostics(event.data);
    };

    editor.getSession().on('change', function(e) {
        if (typeof timer != undefined) {
            clearTimeout(timer);
        }
        timer = setTimeout(requestDiagnostics, timeout);
    });

    editor.on("guttermousedown", function(e){
        var target = e.domEvent.target;
        if (target.className.indexOf("ace_gutter-cell") != -1) {
            // TBD: implement fix-it for clicked e.getDocumentPosition().row
        }
    });

    requestDiagnostics();
})();
