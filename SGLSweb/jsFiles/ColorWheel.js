//Krāsu apļa kods
color_picker = document.getElementById("color_picker");
color_id = document.getElementById("color_id");
color_picker.onmousedown = select_color;
color_picker_add();

function color_picker_add() {
    color_picker_ = color_picker.getContext("2d"),
        center_x = (color_picker.width) / 2,
        center_y = (color_picker.height) / 2,
        sx = center_x,
        sy = center_y;
    palette = new color_picker_element(center_x, center_y, sx, sy);
    palette.draw();
}

function select_color(e) {
    var x = e.pageX - color_picker.offsetLeft,
        y = e.pageY - color_picker.offsetTop,
        pixel = color_picker.getContext("2d").getImageData(x, y, 1, 1).data;

    for (i = 0; i < 3; i++) {
        rgbw[i] = pixel[i];
    }
    dataType = 1;
    stringColorSet();
}

function color_picker_element(center_x, center_y, sx, sy) {
    this.center_x = center_x;
    this.center_y = center_y;
    this.sx = sx;
    this.sy = sy;
    this.draw = function () {
        for (var i = 0; i < 360; i += 0.1) {
            var rad = (i - 45) * (Math.PI) / 180;
            color_picker_.strokeStyle = "hsla(" + i + ", 100%, 50%, 1.0)";
            color_picker_.beginPath();
            color_picker_.moveTo(center_x, center_y);
            color_picker_.lineTo(center_x + sx * Math.cos(-rad), center_y + sy * Math.sin(-rad));
            color_picker_.stroke();
        }
    }
}

