var colorWheel = iro.ColorPicker("#colorWheelDemo", {
    width: 300,
    height: 300,
    color: "rgb(0, 255, 0)",
    // color: '#fff',
    padding: 6,
    borderWidth: 0,
    borderColor: '#fff',
    handleRadius: 8,
    handleSvg: null, // Custom handle SVG
    handleOrigin: {
        x: 0,
        y: 0
    },
    wheelLightness: true,
    wheelAngle: 0, // starting angle
    wheelDirection: 'anticlockwise', // clockwise/anticlockwise
    sliderHeight: undefined,
    sliderMargin: 12,
    display: 'block', // CSS display value
    // layout: {} // Custom Layouts
});

colorWheel.on('input:end', function (color) {
    userRgbw = [];

    userRgbw[0] = color.rgb.r;
    userRgbw[1] = color.rgb.g;
    userRgbw[2] = color.rgb.b;

    userRgbw[3] = whiteColor;//pievieno arī baltās krāsas vērtību
    console.log('<0' + currentLampString + stringColorSet(userRgbw) + '>');
});

var whitePicker = new iro.ColorPicker("#colorWheelSlider", {
    width: 300,
    height: 300,
    color: "rgb(0, 0, 0)",
    // color: '#fff',
    padding: 6,
    borderWidth: 0,
    borderColor: '#fff',
    handleRadius: 8,
    handleSvg: null, // Custom handle SVG
    handleOrigin: {
        x: 0,
        y: 0
    },
    wheelLightness: true,
    wheelAngle: 0, // starting angle
    wheelDirection: 'anticlockwise', // clockwise/anticlockwise
    sliderHeight: undefined,
    sliderMargin: 12,
    display: 'block', // CSS display value

    layout: [
        {
            component: iro.ui.Slider,
            options: {}
        }
    ]
});

whiteColor = 0;
whitePicker.on('input:end', function (color) {
    whiteColor = color.rgb.r;
    console.log('User: ', color.rgb.r);
    userRgbw[3] = whiteColor;//pievieno arī baltās krāsas vērtību
    console.log(userRgbw);
    console.log('<0' + currentLampString + stringColorSet(userRgbw) + '>');
});