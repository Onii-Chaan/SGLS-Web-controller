iro.use(iroTransparencyPlugin);

var COLOR_WHEEL_DIAMETER;
if(document.body.clientWidth<310){
    COLOR_WHEEL_DIAMETER = 220;
} else {
    COLOR_WHEEL_DIAMETER = 300;
}

var colorWheel = iro.ColorPicker("#colorWheelDemo", {
    transparency: true,
    width: COLOR_WHEEL_DIAMETER,
    height: COLOR_WHEEL_DIAMETER,
    color: {r: 255, g: 100, b: 100, a: 1},
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
    //Ievieto 4 vērtības masīvā
    whiteColor = scaleToRange(colorWheel.color.rgba.a , 1 , 0 , 0 , 255);
    userRgbw = [...userRgbw, color.rgb.r, color.rgb.g, color.rgb.b, whiteColor]

    sendAjaxData('<0' + currentLampString + stringColorSet(userRgbw) + '>' + ' ', 'setlamp');
    ajaxConsoleSend('<0' + currentLampString + stringColorSet(userRgbw) + '>');
});

// var whitePicker = new iro.ColorPicker("#colorWheelSlider", {
//     width: COLOR_WHEEL_DIAMETER,
//     height: COLOR_WHEEL_DIAMETER,
//     color: "rgb(0, 0, 0)",
//     // color: '#fff',
//     padding: 6,
//     borderWidth: 0,
//     borderColor: '#fff',
//     handleRadius: 8,
//     handleSvg: null, // Custom handle SVG
//     handleOrigin: {
//         x: 0,
//         y: 0
//     },
//     wheelLightness: true,
//     wheelAngle: 0, // starting angle
//     wheelDirection: 'anticlockwise', // clockwise/anticlockwise
//     sliderHeight: undefined,
//     sliderMargin: 12,
//     display: 'block', // CSS display value

//     layout: [
//         {
//             component: iro.ui.Slider,
//             options: {}
//         }
//     ]
// });

// whiteColor = 0;
// whitePicker.on('input:end', function (color) {//LAI TE NOTIKTU LIETAS TIEK IZVEIDOTS TAIMERIS UZ ONCLICK
//     whiteColor = color.rgb.r;
//     // console.log('User: ', color.rgb.r);
//     userRgbw[3] = whiteColor;//pievieno arī baltās krāsas vērtību
//     // console.log(userRgbw);
//     sendAjaxData('<0' + currentLampString + stringColorSet(userRgbw) + '>' + ' ', 'setlamp');
//     ajaxConsoleSend('<0' + currentLampString + stringColorSet(userRgbw) + '>');
// });

