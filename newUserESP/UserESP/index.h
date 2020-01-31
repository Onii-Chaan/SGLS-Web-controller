const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html lang="en">

<head>
    <meta charset="UTF-8">
    <title>SGLS</title>
    <meta name="viewport" content="width=device-width,initial-scale=1.0">
    <!-- <link rel=stylesheet href=styles.css type=text/css>  -->

    <style>
        /*Galvenā daļa, te atrodas daļas, kas atbild par visiem elementiem kopumā*/

        * {
            margin: 0;
            padding: 0;
            font-size: 16px;
            font-family: Arial, Helvetica, sans-serif;
            /* Nepieļauj teksta iezīmēšanu */
            -webkit-user-select: none;
            /* webkit (safari, chrome) browsers */
            -moz-user-select: none;
            /* mozilla browsers */
            -khtml-user-select: none;
            /* webkit (konqueror) browsers */
            -ms-user-select: none;
            /* IE10+ */
        }

        :root {
            --testColor: red;
            --colorPrimary: darkgray;
            --colorPrimaryPressed: lightBlue;
            --colorSecondary: #9ab8a0;
            --colorTertiary: #52796f;
            --colorTertiaryTwo: #b3dec1;
            --colorBorder: #333333;
            --colorButtons: #9ab8a0;
            --colorButtonPressed: #6c8270;
            --colorBackground: #f0f0f0;
            --colorBackgroundSecondary: #e0e0e0;
            /*var(--colorBackgroundSecondary)*/
        }

        body {
            background: var(--colorBackground);
            color: black;
            overflow-y: scroll;
        }

        .main {
            /*šajā daļā atrodas viss tas, kas atrodas zem headera*/
            background: var(--colorBackground);
            padding-top: 50px;
        }

        /*Header, jeb augšējā lapas daļa*/

        /*Te atrodas settings poga un SGLS nosaukums*/

        .linkBlock {
            /*<a>, kas padara SGLS bloku un nosaukumu par linku*/
            text-decoration: none;
            color: black;
        }

        .titleDiv {
            height: 50px;
            width: 100%;
            background: var(--colorPrimary);
            position: fixed;
            display: flex;
            /*Nepieciešams, lai iekšējos div blokus varētu vadīt izmantojot left right top un bottom*/
            justify-content: space-between;
            /*Nepieciešams, lai pa vidu paliktu tukšums*/
            z-index: 1;
        }

        .SGLSTitleDiv {
            position: relative;
            height: 100%;
            width: 100px;
            left: 10px;
            right: auto;
            text-align: center;
            line-height: 50px;
            /*nepieciešams, lai SGLS nosaukuma teksts tiktu horizontāli centrēts. Tā line-height uzstādīts uz tik pat lielu vērtību kā div blokam kurā tā atrodas*/
        }

        .headerButton {
            /*settings poga*/
            position: relative;
            height: 100%;
            width: 50px;
            left: auto;
            right: 10px;
            cursor: pointer;
        }

        .headerButton:hover {
            background: var(--colorPrimaryPressed);
        }



        /*Mājaslapas vidējā daļa, te atrodas viss līdz izplešanās uz leju pogai*/

        .allLampsMainDiv {
            top: 10px;
            position: relative;
        }

        .allLampsMainDivPart {
            width: 98%;
            height: 40px;
            margin-bottom: 10px;
            display: flex;
            justify-content: space-between;
            border-bottom: 1px solid var(--colorBorder);
            margin-left: auto;
            margin-right: auto;
        }

        .allLampsMainDivPartTextDiv {
            /* width: 170px; */
            height: 100%;
            left: 10px;
            position: relative;
            text-align: center;
            line-height: 40px;
        }

        #sliderValueTextDiv {
            text-align: left !important;
            width: 50px !important;
        }


        /*Augšējo daļa*/

        .switch {
            position: relative;
            display: inline-block;
            width: 60px;
            height: 34px;
            margin-left: auto;
            margin-right: 20px;
            margin-top: auto;
            margin-bottom: auto;
        }

        .switch input {
            opacity: 0;
            width: 0;
            height: 0;
        }

        .slider {
            position: absolute;
            cursor: pointer;
            top: 0;
            left: 0;
            right: 0;
            bottom: 0;
            background-color: gray;
            -webkit-transition: .4s;
            transition: .4s;
        }

        .slider:before {
            position: absolute;
            content: "";
            height: 26px;
            width: 26px;
            left: 4px;
            bottom: 4px;
            background-color: white;
            -webkit-transition: .4s;
            transition: .4s;
        }

        input:checked+.slider {
            background-color: lightgray;
        }

        input:focus+.slider {
            box-shadow: 0 0 1px var(--colorTertiaryTwo);
        }

        input:checked+.slider:before {
            -webkit-transform: translateX(26px);
            -ms-transform: translateX(26px);
            transform: translateX(26px);
        }

        /* Rounded sliders */

        .slider.round {
            border-radius: 34px;
        }

        .slider.round:before {
            border-radius: 50%;
        }

        /*Slider with value*/

        .slidecontainer {
            width: 35%;
            margin-right: 10px;
            margin-left: auto;
            margin-top: auto;
            margin-bottom: auto;
            position: relative;
            display: inline-block;
        }

        .slideValue {
            -webkit-appearance: none;
            width: 100%;
            height: 15px;
            border-radius: 5px;
            background: var(--colorTertiary);
            outline: none;
            -webkit-transition: .2s;
            transition: opacity .2s;
        }

        .slideValue::-webkit-slider-thumb {
            -webkit-appearance: none;
            appearance: none;
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: var(--colorTertiaryTwo);
            cursor: pointer;
        }

        .slideValue::-moz-range-thumb {
            width: 25px;
            height: 25px;
            border-radius: 50%;
            background: var(--colorTertiaryTwo);
            cursor: pointer;
        }

        /*Collapsed daļa*/

        .collapsible {
            background-color: var(--colorPrimary);
            cursor: pointer;
            margin-right: auto;
            margin-left: auto;
            display: flex;
        }

        .active,
        .collapsible:hover,
        .collapsible:hover .bookmark:before,
        .active .bookmark:before {
            background-color: var(--colorPrimaryPressed);
        }

        .expandButton {
            height: 100%;
            width: 95%;
            border: none;
            color: white;
            outline: none;
            position: relative;
            text-align: center;
            padding-left: 10px;
            padding-right: 10px;
        }

        .content {
            margin-right: auto;
            margin-left: auto;
            max-height: 0;
            width: 95%;
            overflow: hidden;
            transition: max-height 0.2s ease-out;
            background-color: var(--colorBackgroundSecondary);
            padding-top: 5px;
        }


        /*Dinamiski genereta baltas krasas izvelne*/

        .whiteCenterDiv {
            width: 40%;
            height: 30%;
            position: fixed;
            left: 0;
            right: 0;
            margin-right: auto;
            margin-left: auto;
            top: 100px;
            display: none;
            padding-left: 5px;
            padding-right: 5px;
        }

        /*Settings lodzins*/

        .optionsDiv {
            position: fixed;
            right: 60px;
            background: var(--colorBackgroundSecondary);
            width: 300px;
            height: 600px;
            overflow: scroll;
            overflow-x: hidden;
            border-left: 2px dashed var(--colorBorder);
            border-bottom: 2px dashed var(--colorBorder);
        }


        .optionsDivButton:hover {
            background: var(--colorTertiary);
        }



        /*JAUNAIS KODS*/

        /*Krāsu aplis*/

        #s_color_picker_id {
            text-align: center;
        }

        /*Bultiņa*/

        div.arrow {
            transform: rotate(-45deg);
        }

        div.arrow::before {
            content: '';
            width: 70%;
            height: 70%;
            border-width: .4vmin .4vmin 0 0;
            border-style: solid;
            border-color: black;
            transition: .2s ease;
            display: block;
            transform-origin: 70% 0;
        }

        div.arrow:after {
            content: '';
            float: left;
            position: relative;
            top: -70%;
            width: 70%;
            height: 70%;
            border-width: 0 .4vmin 0 0;
            border-style: solid;
            border-color: black;
            transform-origin: 70% 0;
            transition: .2s ease;
        }

        /* Ikonas izmērs */

        .medIcon {
            height: 20px;
            width: 20px;
            position: relative;
        }

        /* Vieta kur atrodas pogas */

        .elemPlaceHolder {
            width: 95%;
        }

        /* Bookmark ikona */

        .bookmark {
            color: #000;
            position: absolute;
            margin-left: 5px;
            width: 10px;
            height: 15px;
            border-radius: 1px 1px 0 0;
            border-top: solid 1px currentColor;
            border-left: solid 1px currentColor;
            border-right: solid 1px currentColor;
            background-color: currentColor;
        }

        .bookmark:before {
            content: '';
            position: absolute;
            top: 10px;
            left: 1px;
            width: 7px;
            height: 7px;
            border-top: solid 1px currentColor;
            border-left: solid 1px currentColor;
            -webkit-transform: rotate(45deg);
            transform: rotate(45deg);
            background-color: var(--colorPrimary);
        }

        /* Collapsible pogas nosaukums */

        .collapsibleLabel {
            margin-left: 5px;
        }

        /* Krāsu poga */

        .colorBlock {
            height: 40px;
            text-align: center;
            line-height: 40px;
            display: inline-block;
            margin-bottom: 5px;
            margin-right: 5px;
            box-shadow: 1px 2px 3px #888888;
        }

        .colorBlock:hover {
            cursor: pointer;
            box-shadow: inset 0 0 100px 100px rgba(255, 255, 255, 0.1);
        }

        /* Animāciju poga */

        .animBlock {
            width: 100%;
            height: 30px;
            background: darkgray;
            line-height: 30px;
            border-bottom: #e0e0e0 1px solid;
            padding-left: 5px;
            color: white;
        }

        .animBlock:hover {
            background: lightBlue;
            cursor: pointer;
        }

        /* Settings loga lapas aptumšojošais elements */

        .documentCover {
            height: 100%;
            width: 100%;
            position: fixed;
            background: rgba(0, 0, 0, 0.5);
            display: none;
            top: 0;
            left: 0;
            z-index: 2;
        }

        /* Settings logs */

        .settingsPopUp {
            box-shadow: 1px 2px 3px #888888;
            padding-left: 3px;
            padding-top: 3px;
            border: 1px solid black;
            /* top: 50%;
  left: 50%; */
            position: fixed;
            /* -webkit-transform: translate(-50%, -50%);
  transform: translate(-50%, -50%); */
            /* display: block; */
            background: var(--colorBackground);
            z-index: 3;
            top: 0;
            bottom: 0;
            left: 0;
            right: 0;
            margin: auto;
            width: max-content;
            height: max-content;
        }

        /* Mazā settings ievade */

        .smInput {
            width: 50px;
        }

        /* Explore ikona */

        .explore {
            color: #000;
            position: absolute;
            margin-top: 0;
            margin-left: 3px;
            width: 12px;
            height: 12px;
            border: solid 2px currentColor;
            border-radius: 100%;
            -webkit-transform: rotate(-45deg);
            transform: rotate(-45deg);
        }

        .explore:before {
            content: '';
            position: absolute;
            top: 12px;
            left: 5px;
            height: 6px;
            width: 2px;
            background-color: currentColor;
        }

        /* Grupu pogu atrašanās vieta */

        .buttonGroupHolder {
            width: 95%;
            margin-top: 10px;
            margin-bottom: 10px;
            margin-left: auto;
            margin-right: auto;
        }

        .groupButtonHolder {
            display: flex;
        }

        .lampButton {
            background: var(--colorButtonPressed);
            height: 30px;
            margin-left: auto;
            margin-right: auto;
            text-align: center;
            border: 1px solid var(--colorBackground);
            /* width: 60px; */
            color: white;
        }

        .lampButton:hover {
            background: var(--colorButtons);
            cursor: pointer;
        }

        /* Menu ikona */

        .menu {
            color: #000;
            position: absolute;
            /* margin-left: 2px; */
            /* margin-top: 10px; */
            width: 27px;
            height: 4px;
            background-color: currentColor;
        }

        .menu:before {
            content: '';
            position: absolute;
            top: -8px;
            left: 0;
            width: 27px;
            height: 4px;
            background-color: currentColor;
        }

        .menu:after {
            content: '';
            position: absolute;
            top: 8px;
            left: 0;
            width: 27px;
            height: 4px;
            background-color: currentColor;
        }

        /* Menu ikonas turētājs */

        .menuHolder {
            height: 20px;
            width: 20px;
            position: relative;
            left: 43%;
            top: 64%;
            transform: translate(-50%, -50%);
            /* transform: translateY(-50%); */
        }

        /* Tur kur atrodas lapas galvenais kontents, krāsu aplis */

        .mainColor {
            /*šajā daļā atrodas viss tas, kas atrodas zem headera*/
            /* background: var(--colorBackground); */
            margin-top: 20px;
        }

        /* Nepieļauj teksta iezīmēšanu */

        /* .no_selection {
  -webkit-user-select: none; /* webkit (safari, chrome) browsers */

        /* -moz-user-select: none; mozilla browsers */

        /* -khtml-user-select: none; webkit (konqueror) browsers */

        /* -ms-user-select: none; IE10+ */

        /* } */

        /* Nocentrē krāsu apli */

        .iro__colorPicker {
            margin-left: auto;
            margin-right: auto;
        }

        .btn {
            margin-right: 1px;
            font-size: 14px;
            padding: 6px 12px;
            margin-bottom: 0;
            display: inline-block;
            text-decoration: none;
            text-align: center;
            white-space: nowrap;
            vertical-align: middle;
            -ms-touch-action: manipulation;
            touch-action: manipulation;
            cursor: pointer;
            -webkit-user-select: none;
            -moz-user-select: none;
            -ms-user-select: none;
            user-select: none;
            background-image: none;
            border: 1px solid transparent;
        }

        .btn:focus,
        .btn:active:focus {
            outline: thin dotted;
            outline: 5px auto -webkit-focus-ring-color;
            outline-offset: -2px;
        }

        .btn:hover,
        .btn:focus {
            color: #333;
            text-decoration: none;
        }

        .btn:active {
            background-image: none;
            outline: 0;
            -webkit-box-shadow: inset 0 3px 5px rgba(0, 0, 0, .125);
            box-shadow: inset 0 3px 5px rgba(0, 0, 0, .125);
        }

        /* default
---------------------------- */

        .btn-default {
            color: #333;
            background-color: #fff;
            border-color: #ccc;
        }

        .btn-default:focus {
            color: #333;
            background-color: #e6e6e6;
            border-color: #8c8c8c;
        }

        .btn-default:hover {
            color: #333;
            background-color: #e6e6e6;
            border-color: #adadad;
        }

        .btn-default:active {
            color: #333;
            background-color: #e6e6e6;
            border-color: #adadad;
        }

        /* success */

        .btn-success {
            color: #fff;
            background-color: #28a745;
            border-color: #28a745;
        }

        .btn-success:hover {
            color: #fff;
            background-color: #218838;
            border-color: #1e7e34;
        }

        .btn-success:focus,
        .btn-success.focus {
            box-shadow: 0 0 0 0.2rem rgba(72, 180, 97, 0.5);
        }

        .btn-success.disabled,
        .btn-success:disabled {
            color: #fff;
            background-color: #28a745;
            border-color: #28a745;
        }

        /* Danger */

        .btn-danger {
            color: #fff;
            background-color: #dc3545;
            border-color: #dc3545;
        }

        .btn-danger:hover {
            color: #fff;
            background-color: #c82333;
            border-color: #bd2130;
        }

        .btn-danger:focus,
        .btn-danger.focus {
            box-shadow: 0 0 0 0.2rem rgba(225, 83, 97, 0.5);
        }

        .btn-danger.disabled,
        .btn-danger:disabled {
            color: #fff;
            background-color: #dc3545;
            border-color: #dc3545;
        }

        /* Lampu pogu vērtības atrādīšana */

        .displayLampGroup {
            margin-left: 2.5%;
        }
    </style>
</head>

<body onload="buildSettings();createDynamicContent();/*output.innerHTML = slider.value;*/ ">

    <header class="titleDiv">
        <a href="main.html" class="linkBlock">
            <div class="SGLSTitleDiv">
                <!--SGLS nosaukums-->
                <h1 class="mainText" id="SGLSmainName"><b>SGLS</b></h1>
            </div>
        </a>
        <!--On/Off paziņojums-->

        <label class="switch" id="onOffSwitch">
            <!--On/Off poga-->
            <input type="checkbox" onclick="onOffTextChange();" id="onOffButton">
            <!--On off poga ievade-->
            <span class="slider round"></span>
        </label>

        <div class="headerButton" onclick="openSettings();">
            <!--Options poga-->
            <!-- <img src="pics/settingsButtonPic.png" id="settingsButtonPic" /> -->
            <div class='menuHolder'>
                <div class='menu'></div>
            </div>
            <!--Jāpievieno arī hrefs-->
        </div>

        <div class="optionsDiv">

        </div>

    </header>
    <main class="main">

    </main>
    <main class="mainColor">
        <!--Visa satura bloks-->


        <section id="s_color_picker_id">
            <!--Krāsu aplis-->
            <!-- <canvas id="color_picker" width="200" height="200"></canvas> -->
            <div class="wheel" id="colorWheelDemo"></div>
            <div class='wheelSlider' id='colorWheelSlider'></div>
        </section>
        <div class='displayLampGroup'>
            <p>Group: <span id='displayCurrentLamp'>All</span></p>
            <button id='saveColorButt' onclick='createUserColor();' class='btn btn-default'>Save this color</button>
        </div>


        <div class="dynamicButtonSpace">
            <!--Katras lampas pogas parādīšanās vieta-->
        </div>

        <div class="whiteCenterDiv">
            <div class="whiteCenterDivTop">
                <p class="whiteCenterDivOptionsText">
                    White center value:&nbsp;
                </p>
                <p class="whiteCenterDivOptionsText" id="whiteBrightnessSliderTextValue">

                </p>
            </div>
            <div class="whiteCenterDivMiddle">
                <input type="range" min="0" max="100" value="100" class="slideValue" id="whiteRange">
                <!--white brightness slīderis, ievade-->
            </div>
            <div class="whiteCenterDivBottom">
                <button class="whiteCenterDivOk" onclick="okWhite();">
                    <p class="whiteCenterDivOptionsText">
                        Ok
                    </p>
                </button>
                <button class="whiteCenterDivCancel" onclick="cancelWhite();">
                    <p class="whiteCenterDivOptionsText">
                        Cancel
                    </p>
                </button>
            </div>
        </div>

    </main>


    <div id="collHolder"></div>
    <div id='lampButtHold'
        style='margin-top: 5px; display:flex;text-align: center;width: 95%;margin-right: auto;margin-left: auto;'>
    </div>



    <!--<div id = "testColorBlocksDiv" style = 'height: 500px;width: 400px;  margin-left: 20px;'></div>-->
</body>

<script>
    //TE ATRODAS VISI GLOBĀLIE MAINĪGIE UN TO PASKAIDROJUMI

    //var totalLamps = Number(prompt("Ievadi lampu daudzumu: "));
    var lampButtonPressed = "#9ab8a0";//dinamisko pogu krasa kad ta tika nospiesta
    var lampButtonDefault = "#6c8270";//dinamisko pogu krasa kad ta nav nospiesta

    var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
    var buttonOn = false;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu
    var lampNum = "00";//lampu numura String vērtība
    var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās
    var funcNum = 0;//lampu funkcijas numurs
    var currentLamp; //seko līdzi tam, kura lampa ir pašlaik nospiesta

    var colorCount = 0;//seko līdzi tam cik krāsu pogu ir saglabāts 
    var animCount = 0;//seko līdzi tam cik animāciju pogu ir saglabāts

    var animLimit = 30; //nosaka saglabāto animāciju skaitlisko limitu
    var colorLimit = 30;//nosaka saglabāto krāsu skaitlisko limitu

    var brightness = 50;//glabā sevī krāsu apļa spožumu atkarībā no slīdera
    var whiteColor = 0;//glabā sevī visiem pieejamu baltās krāsas vērtību 
    var userRgbw = [0, 255, 0];//glabā lietotāja saglabātos, pēdējās nospiestās rgbw vērtības 

    var currentLampString = '1-25#';//jau izveidots string priekš lampu numuriem
    var onOff = false;//seko līdzi tam, vai lampas ieslēgtas vai izslēgtas
</script>
<script>
    function createDynamicContent() {

        createColl(document.body);//izveido saved pogu un tās kontentu
        createSubColl();//izveido papildus divas

        document.body.appendChild(buildElementNode('DIV', 'buttonGroupHolder'));//izveido lampu pogu un grupu pogu atrašanās vietu
        document.getElementsByClassName('buttonGroupHolder')[0].id = 'groupHolder';//pievieno id pogu div elementam

        createLampButts();//izveido lampu pogas
        createExploreColl(document.body);//izveido explore sadaļu

        for (var i = 0; i < document.getElementsByClassName('elemPlaceHolder').length; i++) {//izveido konstantu krāsu un funkciju parent div lielumu, lai varētu
            //  ar atbilstošajām pogām aizpildīt visu laukumu
            document.getElementsByClassName('elemPlaceHolder')[i].style.width =
                Math.ceil(document.getElementsByClassName('elemPlaceHolder')[i].clientWidth) + 'px';
        }
    }

    /*ExploreArr masīvā glabājas visas explore pogu vērtības*/
    var exploreArr = [
        ['SameColor', 123, 123, 123, 123],
        ['hmhmmhh', 0, 23, 0, 122],
        ['word', 255, 255, 0, 0],
        ['manyWords', 10, 10, 23, 18],
        ['manyMore', 10, 23, 15, 200],
        ['Yeye', 100, 200, 100, 0],
        ['pum_pum', 25, 10],
        ['animManim', 50, 0],
        ['someAnim', 10, 100],
        ['oldAnim', 19, 230],
        ['NewAnim', 7, 123]
    ];

    var colorAnimBlockObjArr = [];
    function createExploreColl(placeHolder) {//izveido explore collapsible
        var collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"),
            "Explore",
            placeHolder,
            new Icon("explore", "medIcon")
        );
        collapsibleObj.buildCollapseButton();
        blockWidthCount = 0;
        // console.log('//////////////////////////////////////////////////////////////////////////////////');
        for (var i = 0; i < exploreArr.length; i++) {//izveido krāsu pogas un saliek tās collapsible pogas kontentā
            if (exploreArr[i].length == 5) {//ja masīva elementa atbilst krāsai 
                colorAnimBlockObjArr.push(
                    new ColorBlock(
                        exploreArr[i][0],
                        exploreArr[i].slice(1, 5),
                        'colorBlock',
                        addExploreButton
                    )
                );
            } else {
                colorAnimBlockObjArr.push(
                    new ColorBlock(
                        exploreArr[i][0],
                        exploreArr[i].slice(1, 3),
                        'colorBlock',
                        addExploreButton
                    )
                );
            }
            addColorBlock(i, collapsibleObj, colorAnimBlockObjArr, exploreArr.length);
        }
    }

    var blockWidthCount = 0;//skaita platumu krāsu bloku radīšanas brīdī
    function addColorBlock(j, collObj, objArr, arrLen) {//veido krāsu blokus to atbilstošajā vietā, atbilstošajā lielumā
        collObj.updateContent(objArr[j].build());//uzbūvē krāsu pogu
        // console.log(objArr[j].show());
        objArr[j].grow();//izveido krāsu bloku platumu
        blockWidthCount += objArr[j].blockWidth();//skaita uz priekšu rindas platumu
        // console.log('BEF_LEN: ', objArr[j].blockWidth());
        if (
            blockWidthCount >= collObj.contentLength() ||
            j == arrLen - 1
        ) {//pārbauda vai pēdējo krāsu bloku ir jāpaplašina
            // console.log('A');        
            if (
                blockWidthCount - objArr[j].blockWidth() !=
                collObj.contentLength() && j > 0 && j != arrLen - 1
            ) {//pagarina krāsas bloku līdz galam pa kreisi
                objArr[j - 1].grow(
                    collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth())
                );
                // console.log('B');
            }
            else if (
                j == arrLen - 1
            ) {
                objArr[j].grow(collObj.contentLength() - blockWidthCount - 1);
                // console.log('D');
            }
            blockWidthCount = objArr[j].blockWidth();//atgriežas uz nākamo rindiņu
        } else if (
            objArr[j].blockWidth() > collObj.contentLength() - blockWidthCount
        ) {
            // console.log('E');

            objArr[j - 1].grow(
                collObj.contentLength() - (blockWidthCount - objArr[j].blockWidth() + 1)
            );
            blockWidthCount = objArr[j].blockWidth();//ieņem nākamā elementa lielumu nākamajā rindiņā
        }
        if (blockWidthCount >= collObj.contentLength()) {
            blockWidthCount = 0;
        }
        //  console.log(objArr[j]);
        //console.log(j);
        //  console.log(collObj);
        // console.log(objArr);
        // console.log('AFTER_LEN: ', objArr[j].blockWidth());
        // console.log('CONTENT_LENGTH', collObj.contentLength());
        // console.log('BLOCK_SUM', blockWidthCount);
        // console.log(arrLen);
        // console.log(objArr[j].show());
        // console.log('---------------------------------------------------');
    }




    function createColl(placeHolder) {//Izveido collapsible div objektu
        var collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"), "Saved", placeHolder, new Icon("bookmark", "medIcon")
        );
        collapsibleObj.buildCollapseButton();
    }


    function checkRotateElement(checkNode1, checkNode2, styleToApply) {//Pagriež atbilstošo ikonu, ja pogā atrodas vairāk kā viena
        if (checkNode1.nodeName == "P") {//gadījumam, kad pogā atrodas vairāk kā viena ikona
            checkNode2.style = styleToApply;//rotē bultiņu
        } else {
            checkNode1.style = styleToApply;//rotē bultiņu
        }
    }


    var collObjArr = [0, 0, 0];//Masīvs, kurā atrodas visi collapsible objekti
    var collObjArrCount = 0;//skaita uz priekšu jauno objektu pozīcijas masīvā


    var rgbw = [
        [255, 255, 255, 0],
        [255, 255, 0, 0],
        [0, 255, 255, 0],
        [255, 0, 255, 10],
        [255, 255, 0, 120],
        [0, 255, 255, 0],
        [0, 255, 255, 0],
        [0, 255, 255, 0]
    ];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
    var rgbwNames = ['SomeColor1', 'SmallerColorLol', 'A', 'Here',
        'InternalSuffering', 'words', 'manyWords', 'lettersColor'];

    var colorBlockObjArr = [];

    var funcNum = [
        [2, 100],
        [3, 213],
        [15, 1],
        [23, 0],
        [22, 11],
        [76, 233],
        [1, 677]
    ];

    var funcNames = ['bitch', 'function', 'colors', 'this', 'test1', 'testdos', 'testtres'];
    var funcBlockObjArr = [];

    blockWidthCount = 0;//skaita uz priekšu krāsu bloku kopējo platumu rindā un salīdzina ar to atrašanās bloku platumu

    function createSubColl() {
        var collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"),
            "Colors",
            document.getElementsByClassName("elemPlaceHolder")[0],
            '',
            'colorBlockContent'
        );
        collapsibleObj.buildCollapseButton();
        blockWidthCount = 0;
        for (var i = 0; i < rgbw.length; i++) {
            //izveido krāsu pogas un saliek tās collapsible pogas kontentā
            colorBlockObjArr.push(
                new ColorBlock(
                    rgbwNames[i],
                    rgbw[i],
                    'colorBlock',
                    editColorButton)
            );
            addColorBlock(i, collapsibleObj, colorBlockObjArr, rgbw.length);//!!!!!
            colorCount++;//skaita uz priekšu cik ir krāsu pogu
        }

        collapsibleObj = new CollapsibleButton(
            new Icon("arrow", "medIcon"),
            "Animations",
            document.getElementsByClassName("elemPlaceHolder")[0],
            '',
            'animBlockContent'
        );//izveido animāciju collapsible pogu

        collapsibleObj.buildCollapseButton();

        for (i = 0; i < funcNum.length; i++) {//izveido animāciju pogas un saliek tās collapsible pogas kontentā
            funcBlockObjArr.push(new AnimationsBlock(funcNames[i], funcNum[i], 'animBlock', editAnimButton));
            collapsibleObj.updateContent(funcBlockObjArr[i].buildAnimBlock());

            animCount++;//skaita uz priekšu cik ir animāciju pogu
        }
    }



    var lampGroups = [
        ['Room1', '1-5#'],
        ['BedRoom', '2-8#'],
        ['Garden', '6-7#']
    ];//ienākošo lampu grupu datu masīvs
    var lampNum = 6;
    var lampButton;//lampu pogas mainīgais


    var editGroupSettings;//liela ievade un tad from to ievade, nosūta ajax datus
    var newGroupSettings;//liela ievade un tad from to ievade, izveido jaunu pogu nosūta ajax datus
    var addExploreButton;//teksts un tikai save vai close
    var newColorButton;//teksts un liela ievade, 3 pogas
    var editColorButton;//teksts un liela ievade, 3 pogas, tiek piemērota saved krāsām
    var editAnimButton;//teksts liela ievade, teksts, maza ievade, 3 pogas
    function buildSettings() {//izveido visus settings objektus, lai tie būtu tikai vienā eksemplārā un joprojām pieejami visiem citiem elementiem 
        editGroupSettings = new SettingsPopUp(
            'Edit this group',
            [
                ['Update name of group: ', 'bigInput'],
                ['Type which lamps you would like to change in group: ', 'double'],
                ['From: ', 'smInput'],
                ['To: ', 'smInput']
            ],
            3,
            'group',
            0,
            'updateGroup'
        );
        editGroupSettings.build();
        editGroupSettings.closeSettings();


        newGroupSettings = new SettingsPopUp(
            'Create new group',
            [
                ['Type new name of group: ', 'bigInput'],
                ['Type which lamps you would like to group up: ', 'double'],
                ['From: ', 'smInput'],
                ['To: ', 'smInput']
            ],
            2,
            'group',
            1,
            'group'
        );
        newGroupSettings.build();
        newGroupSettings.closeSettings();


        addExploreButton = new SettingsPopUp(
            'Save this to your collection?',
            [],
            2,
            'add',
            2,
            'add'
        );
        addExploreButton.build();
        addExploreButton.closeSettings();


        newColorButton = new SettingsPopUp(
            'Save color to your collection',
            [
                ['Type the name of your new color: ', 'bigInput']
            ],
            2,
            'add',
            3,
            'color'
        );
        newColorButton.build();
        newColorButton.closeSettings();


        editColorButton = new SettingsPopUp(
            'Color options',
            [
                ['Edit color name: ', 'bigInput']
            ],
            3,
            'add',
            4,
            'updateColor'
        );
        editColorButton.build();
        editColorButton.closeSettings();


        editAnimButton = new SettingsPopUp(
            'Animation options',
            [
                ['Edit animation name: ', 'bigInput'],
                ['Edit animation parameter', 'smInput']
            ],
            3,
            'add',
            5,
            'updateAnimation'
        );
        editAnimButton.build();
        editAnimButton.closeSettings();
    }



    function checkButtPlaceCount() {//pārbauda vai ir nepieciešams veidot nākamo elementu, lai turētu grupu pogas
        // console.log(document.getElementsByClassName('groupButtonHolder')[createButtHolder(true) - 1].childElementCount);
        if (document.getElementsByClassName('groupButtonHolder')[createButtHolder(true) - 1].childElementCount == 4) {
            createButtHolder();
        }
    }


    var createButtHolder = (function () {//mainīgais, funkcija, kas skaita uz priekšu ģenerētos pogas turetāja elementus
        var buttonPlaceCount = 0;
        // console.log('firstTime');
        return function (ret = false) {
            // console.log('funcExc');
            if (ret) {
                // console.log('ret count');
                return buttonPlaceCount;
            } else {
                // console.log('append');
                buttonPlaceCount++;
                document.getElementById('groupHolder').appendChild(buildElementNode('DIV', 'groupButtonHolder'));
            }
        }
    })();



    function createLampButts() {//izveido lampu pogas
        createButtHolder();
        lampButton = new LampBlock('All', '1-25#');//izveido pogu, kas ieslēdz visas lampas
        lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        checkButtPlaceCount();
        for (j = 0; j < lampGroups.length; j++) {//izveido lampu grupu pogu
            lampButton = new LampBlock(lampGroups[j][0], lampGroups[j][1], editGroupSettings);
            lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
            checkButtPlaceCount();
        }

        for (i = 0; i < lampNum; i++) {//izveido parastas lampas pogu
            lampButton = new LampBlock('L' + (i + 1), i + 1);
            lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
            checkButtPlaceCount();

        }
        createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
        checkButtPlaceCount();
        riseGroupButts();
    }


    function createNewLampGroup(name, value, settings = '', newButt = false) {//izveido jaunu lampu grupas pogu
        lampButton = new LampBlock(name, value, settings);
        if (!newButt) {//ja netiek pievienota jauna poga
            lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);
        } else {//ja tiek pievienota jauna poga
            if (
                !document.getElementsByClassName('groupButtonHolder')
                [document.getElementsByClassName('groupButtonHolder').length - 1]
                    .getElementsByClassName('lampButton').length == 0
            ) {//ja pogas holderī vēl ir vieta jaunai pogai
                document.getElementsByClassName('groupButtonHolder')//novāc create new lamp group pogu
                [document.getElementsByClassName('groupButtonHolder').length - 1]
                    .getElementsByClassName('lampButton')[document.getElementsByClassName('groupButtonHolder')
                    [document.getElementsByClassName('groupButtonHolder').length - 1]
                        .getElementsByClassName('lampButton').length - 1].remove();
                lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 1);//izveido elementu pēc pēdējās grupas pogas        
            } else {//ja pogas holderī nav vietas jaunai pogai
                document.getElementsByClassName('groupButtonHolder')//novāc pēdējo create lamp button pogu
                [document.getElementsByClassName('groupButtonHolder').length - 2]
                    .getElementsByClassName('lampButton')[document.getElementsByClassName('groupButtonHolder')
                    [document.getElementsByClassName('groupButtonHolder').length - 2]
                        .getElementsByClassName('lampButton').length - 1].remove();

                lampButton.build(document.getElementsByClassName('groupButtonHolder').length - 2);//izveido elementu pēc pēdējās grupas pogas        
            }
            checkButtPlaceCount();
            riseGroupButts();
            createNewLampGroup('Create new lamp group', 'newGroup', newGroupSettings);//izveido create new lamp group pogu
            checkButtPlaceCount();
            riseGroupButts();
        }
    }

    function checkButtHolders() {//pārbauda vai ir nepieciešams pārvietot grupu pogas uz citiem div elementiem
        var groupDivs = document.getElementsByClassName('groupButtonHolder');
        for (var i = 0; i < groupDivs.length; i++) {
            while (
                groupDivs[i].getElementsByClassName('lampButton').length < 4 &&
                i != groupDivs.length - 1 &&
                groupDivs[i + 1].getElementsByClassName('lampButton').length > 0
            ) {
                groupDivs[i].appendChild(groupDivs[i + 1].getElementsByClassName('lampButton')[0])
            }
        }
    }


    function riseGroupButts() {//iestata group pogām to garumu
        for (var i = 0; i < document.getElementsByClassName('groupButtonHolder').length; i++) {
            for (var j = 0; j < document.getElementsByClassName('groupButtonHolder')[i].childElementCount; j++) {
                switch (document.getElementsByClassName('groupButtonHolder')[i].childElementCount) {
                    case 1:
                        document.getElementsByClassName('groupButtonHolder')[i]
                            .getElementsByClassName('lampButton')[j].style.width = '100%';
                        break;
                    case 2:
                        document.getElementsByClassName('groupButtonHolder')[i]
                            .getElementsByClassName('lampButton')[j].style.width = '50%';
                        break;
                    case 3:
                        document.getElementsByClassName('groupButtonHolder')[i]
                            .getElementsByClassName('lampButton')[j].style.width = '33%';
                        break;
                    case 4:
                        // console.log(document.getElementsByClassName('groupButtonHolder')[i].getElementsByClassName('lampButton')[j]);
                        document.getElementsByClassName('groupButtonHolder')[i]
                            .getElementsByClassName('lampButton')[j].style.width = '25%';
                        break;
                    default:
                        break;
                }
            }
        }
    }




    function buildElementNode(type, classList = '', textToAdd = '') {//izveido un atgriež paragrāfu ar klasi
        var builtElement = document.createElement(type);
        if (classList != '') {
            if (classList.constructor === Array) {
                for (var i = 0; i < classList.length; i++) {
                    builtElement.classList.add(classList[i]);
                }
            } else {
                builtElement.classList.add(classList);
            }
        }
        if (textToAdd != '') {
            builtElement.appendChild(document.createTextNode(textToAdd));
        }
        return builtElement;
    }


    function createPopUp() {//izveido settings popUp
        // var createPopUp = new SettingsPopUp('Create new group', [['Type new name of group: ', 'bigInput'], ['Type which lamps you would like to group up: ', 'double'], ['From: ', 'smInput'], ['To: ', 'smInput']], 2, 1, 'group');
        // createPopUp.build();
    }


    backCover = buildElementNode('DIV', 'documentCover');//izveido lapas aptumšojošo div elementu
    document.body.appendChild(backCover);
    function backShadow(set) {//padara fonu tumšu, tiek izmantots priekš settings elementiem
        if (set) {
            backCover.style.display = 'block';
        } else {
            backCover.style.display = 'none';
        }
    }


    function createUserColor() {//saglabā lietotāja izvēlēto krāsu pēc 'Save this color' nospiešanas
        console.log('User Ok');
        newColorButton.open();
    }

    // window.onclick = e => {//būs nepieciešams, lai sekotu tam , kur notiek klikšķis, lai izvēlētos, vai atgriezt pogas default stāvokli vai nē
    //     console.log(e.target);
    //     console.log(e.target.tagName);
    // } 


    var getContrast = function (rgbColor) {//pārbauda un atgriež fonta krāsu
        // Get YIQ ratio
        var yiq = ((rgbColor[0] * 299) + (rgbColor[1] * 587) + (rgbColor[2] * 114)) / 1000;
        // Check contrast
        return (yiq >= 128) ? 'black' : 'white';
    };
</script>
<script>
    class CollapsibleButton {//izbīdamo pogu klase
        constructor(iconObj, textToAppend, elementHolder, secIcon = '', collContId = '') {

            this.iconObj = iconObj;//ikonas objekts, kas tiks parādīts pogas sānā
            this.textToAppend = textToAppend;//Teksts, kas parādīsies uz pogas
            this.elementHolder = elementHolder;//Elements, kurā atradīsies poga



            this.collButton;//galvenā poga, kas tiek izveidota
            this.labelDiv;
            this.smHolder;

            this.objectHolder;

            this.secIcon = secIcon;//Papildus ikona, ja ir nepieciešamība

            this.collContId = collContId;//Dotā collapsible kontenta ID
        }


        buildCollapseButton() {//Izveido pogas elementu un tajā esošo kontentu
            this.objectHolder = document.createElement('DIV');
            //this.objectHolder.style.marginBottom = '20px';
            this.labelDiv = document.createElement('P');

            this.collButton = document.createElement('BUTTON');//izveido pogas elementu, kas arī būs pati poga
            this.collButton.style.height = '30px';


            this.collButton.classList.add('collapsibleObj');
            this.collButton.classList.add('collapsible');//pievieno klasi pogai
            this.collButton.classList.add('expandButton');//pievieno klasi pogai

            if (this.secIcon != '') {//pievieno otro ikonu
                this.collButton.appendChild(this.secIcon.buildArrow());
            }

            var textToAdd = document.createTextNode(this.textToAppend);//Izveido tekstu pogai
            this.labelDiv.classList.add("collapsibleLabel");
            this.labelDiv.appendChild(textToAdd);//pievieno tekstu pogai
            this.collButton.appendChild(this.labelDiv);//pievieno tekstu pogai


            this.collButton.appendChild(this.iconObj.buildArrow());//ikona tiek pievienota pogas objektam


            this.smHolder = document.createElement("DIV");
            this.smHolder.classList.add('elemPlaceHolder');
            this.smHolder.classList.add('content');

            if (this.collContId != '') {//iestata kontenta ID, lai to varētu izmantot ievietojot tajā elementus
                this.smHolder.id = this.collContId;
            }

            this.objectHolder.appendChild(this.collButton);//pievieno izveidoto pogu un tās elementus elementam, kur atrodas poga
            this.objectHolder.appendChild(this.smHolder);

            this.elementHolder.appendChild(this.objectHolder);

            //var coll = document.getElementsByClassName("collapsibleObj");

            checkRotateElement(this.collButton.childNodes[1], this.collButton.childNodes[2], 'transform: rotate(0deg);top: 3px; margin-right: 10px; margin-left: auto');
            this.collButton.onclick = methodize(this.click, this);//rotē bultiņu uz klikšķi un atver kontentu
        }

        click() {//rotē bultiņu ar klikšķi un dara visu nepieciešamo, kas notiek klikšķa laika uz collapsible
            this.collButton.classList.toggle("active");
            this.content = this.collButton.nextElementSibling;
            if (this.content.style.maxHeight) {
                checkRotateElement(this.content.previousSibling.childNodes[1], this.content.previousSibling.childNodes[2], 'transform: rotate(0deg);top: 3px; margin-right: 10px; margin-left: auto');
                this.content.style.maxHeight = null;
            } else {
                checkRotateElement(this.content.previousSibling.childNodes[1], this.content.previousSibling.childNodes[2], 'bottom: 6px; transform: rotate(180deg); margin-right: 14px; margin-left: auto');
                this.content.style.maxHeight = this.content.scrollHeight + "px";
                if (this.content.parentElement.parentElement != null) {//Nodrošina, ka kontents nekur nepazudīs izplešoties
                    this.content.parentElement.parentElement.style.maxHeight = 'inherit';
                }
            }
        }

        updateContent(contentToAdd) {//apdeito kontentu
            this.collButton.nextElementSibling.appendChild(contentToAdd);
        }

        contentLength() {//iegūst kontenta elementa platumu
            return this.collButton.nextElementSibling.clientWidth;
        }
    }

</script>
<script>
    class Icon {//ikonas klase
        constructor(classType, iconSize) {
            this.classType = classType;
            this.iconSize = iconSize;

            this.iconDiv;
            this.arrHoldDiv;
        }

        buildArrow() {
            this.arrHoldDiv = document.createElement('DIV');
            this.iconDiv = document.createElement('DIV');

            this.iconDiv.classList.add(this.iconSize);
            this.arrHoldDiv.classList.add(this.classType);
            this.arrHoldDiv.classList.add(this.iconSize);

            this.iconDiv.appendChild(this.arrHoldDiv);
            return this.iconDiv;
        }
    }
</script>
<script>


    //slīderis priekš brightness
    // var slider = document.getElementById("myRange");//saņem vērtību no slīdera 0 - 100
    // var output = document.getElementById("sliderValueText");//mainīgais slīdera vērtībai, ko izvadīt

    // slider.oninput = function () {//izvada vērtību slīderim
    //   output.innerHTML = this.value;
    //   brightness = this.value;
    //   color_picker_add();
    // }


    function onOffTextChange() {//seko līdzi tam, vai lampas ieslēgtas vai nē
        if (onOff) {
            onOff = false;
        } else {
            onOff = true;
        }
        console.log(onOff);
    }




    function okWhite() {//aprekina un iestata baltas krasas vertibu
        if (whiteSetOn == true) {
            document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
            rgbw[3] = scaleToRange(newWhite, 0, 100, 0, 255);//Parveido procentus par viena baita vertibu
            if (rgbw[3] > 0) {//Nosaka vai balta krasa ir ieslegta vai ari nav
                whiteAllowed = true;
            } else {
                whiteAllowed = false;
            }
            dataType = 1;
            stringColorSet();//iestata parejas krasas un izvada vertibas
            whiteSetOn = false;
        }
    }

    function cancelWhite() {//iziet ara no baltas krasas iestatisanas lodzina nemainot nekadas vertibas
        if (whiteSetOn == true) {
            document.getElementsByClassName("whiteCenterDiv")[0].style.display = "none";
            whiteSetOn = false;
        }
    }

    function scaleToRange(number, fromMin, fromHigh, toMin, toHigh) {//Si funkcija parveido skaitli no vienas kopas uz citu
        return Math.round(((number - fromMin) / (fromHigh - fromMin)) * (toHigh - toMin) + toMin);
    }

    function funcNumBuilder(num) {
        if (num >= 100) {
            return num;
        } else if (num >= 10 && num < 100) {
            return "0" + num;
        } else {
            return "00" + num;
        }
    }



    function valueState(valueStateOutput) {//parāda vai dati tiek saņemti vai nosūtīti kā arī citus paziņojumus
        document.getElementById("outputState").innerText = valueStateOutput;
    }


    function setBrightness(brightness) {
        if (dataType == 1) {
            for (var i = 0; i < 4; i++) {
                rgbw[i] = Math.round(scaleToRange(brightness, 0, 100, 0, rgbw[i]));
            }
            stringColorSet();
        }
    }

    //Paroles ievades dala
    function submitPassword() {
        var password = "test";
        var passwordCheck = document.getElementById("passwordInput").value;
        if (passwordCheck == password) {
            window.location.href = "main.html";
        }
    }
    //Paroles ievades dala beidzas

    //Settings logs
    document.getElementsByClassName("optionsDiv")[0].style.display = "none";
    var openSettingsVar = false
    function openSettings() {
        if (openSettingsVar == false) {

            openSettingsVar = true;
            document.getElementsByClassName("optionsDiv")[0].style.display = "block";
        } else {

            openSettingsVar = false;
            document.getElementsByClassName("optionsDiv")[0].style.display = "none";
        }
    }



//lai darbotos ar datiem neizmantojot WiFi, ir jāizveido input lodzinš, kur tiks iekšā rakstītas vērtības

//Settingos var mainīt paroli
//Settingos atrodas lampu parskaitisanas

//izveidot lampu pārskaitīšanās nosūtīšanu

//izveidot funkciju, kas sadalītu lampu skaita vērtību no iekavām un izmantotu to turpmākajā skriptā

//<200[001]000> funkciju nosutisanas paraugs
//<000> lampu parskaitisanas nosutisanas paraugs
//<3> gaismas muzikas nosutisanas paraugs
//funkciju numuri nav zinami tapec tie tika izteikti sada veida: rainbow=1, fade=2, blink=3, onOff=0
//slideru vertibu parveidosana no 0-100 uz 0-255. Skaitliska veida tiks paradits viss procentos izmantojot map funkciju

//izveidot tā, lai funkcijas darbotos tikai tad, ja on off būls būtu true
//BOOKMARK1 ir iespeja pie ieslegsanas un izslegsanas noslept funkcionalo lapas dalu tadejadi tai lietotajam uz to bridi tai nebus piekluves. Sis ir atrais variants kuru butu velams uzlabot ar sarezgitaku un izskatigaku variantu

//Izveidot labu un parskatamu dizainu atbilstosi dazadiem ekranu izmeriem

</script>
<script>
    function parseToRGBA(stringToParse) {//sadala style rgb un rgba uz skaitliskām krāsu vērtībām
        var m;
        if (stringToParse.indexOf('rgba') == -1) {//pārbauda vai krāsas ir jāsadala pēc rgb vai pēc rgba tipa
            m = stringToParse.match(/^rgb\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*\)$/i);
            return [m[1], m[2], m[3], 0];
        } else {
            m = stringToParse.match(/^rgba\s*\(\s*(\d+)\s*,\s*(\d+)\s*,\s*(\d+)\s*,\s*(0\.(\d+))\s*\)$/i);
            return [m[1], m[2], m[3], m[4]];
        }
    }

    function stringColorSet(rgbwArr) {//Si funkcija parveido rgbw krasu vertibas String rindina. Gatavu izsutisanai
        var countString = "";
        var rgbwString = '';

        for (var i = 0; i < rgbwArr.length; i++) {//Nosaka vai saraksta skaitli ir divcipara vai viencipara vai trisciparu skaitlis un atbilstosi pieliek nulles
            if (rgbwArr[i] >= 100) {
                countString = rgbwArr[i];
            } else if (rgbwArr[i] < 100 && rgbwArr[i] >= 10) {
                countString = "0" + rgbwArr[i];
            } else {
                countString = "00" + rgbwArr[i];
            }
            rgbwString += countString;
            countString = "";
        }
        return rgbwString;
    }

    function stringFunctionSet(funcNum, funcPar) {//izveido funkciju nosūtāmo stringa otro daļu
        var sendOut = '';
        if (funcNum < 10) {
            sendOut = '0' + funcNum;
        } else {
            sendOut = funcNum;
        }
        if (funcPar >= 100) {
            sendOut += funcPar;
        } else if (funcPar < 100 && funcPar >= 10) {
            sendOut += "0" + funcPar;
        } else {
            sendOut += "00" + funcPar;
        }
        return sendOut;
    }

    function sendValue(dataType, lampNum, colorOutput) {//parāda nosūtamos datus
        var sendPar = '';
        sendPar = "<" + dataType + lampNum + colorOutput + ">";

        console.log(sendPar);
        /*else if (dataType == 2) {//funkciju nosutisana
          sendPar.innerText = "<" + dataType + "00" + sendValueOutput + "000" + ">";//pedejas tris nulles ir prieks parametru iestatisanas. pagaidam netiek izmantots
        } else if (dataType == 3) {//gaismas muzikas nosutisana
          sendPar.innerText = "<3>";
        } else if (dataType == 0) {//saskaitisanas nosutisana
          sendPar.innerText = "<000>";
        }*/
    }


    function createGroupString(from, to) {//izveido grupas string mainīgo
        // console.log('a');
        return from + '-' + to + '#';
    }

    function ajaxConsoleSend(dataName) {//'izsūta' datus uz konsoli
        console.log('AJAX SEND: ', dataName);
    }


    function methodize(methodize_func, methodize_scope) {//nepieciešams, lai objektiem varētu pievienot eventus
        return (function () { methodize_func.call(methodize_scope); });
    }


</script>
<script>
    class ColorBlock {
        constructor(colorName, colorValue, type, options = '') {
            this.colorName = colorName;//krāsas nosaukums
            this.colorValue = colorValue;//krāsas rgbw vērtība
            this.colorNameLen = this.colorName.length;//krāsas nosaukuma string garums
            this.colorBlock;//pats krāsas bloks
            this.colorBlockPar;//teksta atrašanās vieta
            this.type = type;//nosaka vai šī būs animācijas vai krāsu klase

            this.options = options; //animāciju un krāsu pogu editošanai
        }

        build() {//funkcija, kas atgriež gatavu krāsas bloku
            this.colorBlock = document.createElement('DIV');

            this.colorBlock.innerHTML = this.colorName;//izveido nosaukuma paragrāfu
            this.colorBlock.style.color = getContrast(this.colorValue.slice(0, 3));//Maina teksta krāsu atbilstoši fona krāsai

            this.colorBlock.classList.add(this.type);
            this.colorBlock.style.background = 'rgba(' + this.colorValue[0] + ', ' + this.colorValue[1] + ', ' + this.colorValue[2] + ', ' + scaleToRange(this.colorValue[3] * 100, 0 * 100, 255 * 100, 1 * 100, 0.01 * 100) / 100 + ')';

            this.colorBlock.addEventListener('click', function () {
                sendValue(0, currentLampString, stringColorSet(parseToRGBA(this.style.backgroundColor)));
            });

            if (this.options != '') {
                this.colorBlock.ondblclick = methodize(this.dblclick, this);
            }
            return this.colorBlock;
        }

        dblclick() {
            this.dblData = this.colorValue;//izveido atsevišķu masīvu datu nosūtīšanai
            this.dblData.push(this.colorName);
            this.options.open(this.dblData, this.colorBlock, this);
        }

        grow(plusWidth = 0) {//izveido krāsu blokam atbilstošu platumu
            if (!plusWidth) {//strādā tikai tad, kad netiek likts papildus platums
                // console.log('TEST: ', this.colorBlock.clientWidth);
                this.colorBlock.style.width = this.colorBlock.clientWidth + Math.floor(this.colorBlock.clientWidth * 0.5) + 'px';//izveido atbilstošo bloka garumu
            } else if (plusWidth) {//ja ir papildus vērtība, ko pievienot
                this.colorBlock.style.width = this.colorBlock.clientWidth + plusWidth + 'px';
            }
        }

        blockWidth() {//atgriež objekta platumu
            return this.colorBlock.clientWidth + 5/*margin-left*/;
        }

        updateData(name = '', value = '') {
            if (name != this.colorName && name != '' && typeof name != 'undefined') {//pārbauda vai var apdeitot nosaukumu
                this.colorBlock.innerHTML = name;
            }
            console.log('befvalue: ', value);

            if (value != this.colorValue[1] && value != '' && typeof value != 'undefined') {
                console.log('value: ', value);
                console.log('name', this.colorValue[0] + '|' + value);
                this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + value);
            }
        }

        show() {//parāda HTML elementu
            return this.colorBlock;
        }
    }




</script>
<!-- <script src=jsFiles\ColorWheel.js></script> -->
<script>
    class AnimationsBlock extends ColorBlock {//animāciju bloks ir tāds pats kā ColorBlock, bet ar citiem parametriem
        buildAnimBlock() {
            this.colorBlock = document.createElement('DIV');

            this.colorBlock.innerHTML += this.colorName;//izveido nosaukuma paragrāfu

            this.colorBlock.classList.add('animBlock');

            this.colorBlock.setAttribute('name', this.colorValue[0] + '|' + this.colorValue[1]);//lai varētu vēlāk iegūt funkciju vērtības no elementa name


            this.colorBlock.onclick = methodize(this.click, this);

            if (this.options != '') {
                this.colorBlock.ondblclick = methodize(this.dblclick, this);
            }

            return this.colorBlock;
        }

        click() {
            this.findMatch = this.colorBlock.getAttribute('name').match(/\d+/g);//atrod iekš name esošos parametrus funkcijai
            sendValue(1, currentLampString, stringFunctionSet(this.findMatch[0], this.findMatch[1]));
        }
    }

</script>
<script>
    class LampBlock {
        constructor(name, value, options = '') {
            this.name = name;//lampas pogas nosaukums
            this.value = value;//lampas pogas vērtība
            if (typeof this.value == 'number') {
                this.value = createGroupString(this.value, this.value);
            }
            this.options = options;
            // console.log(this.options);
            // if (this.options != '') {
            // this.options.build();
            // console.log('nowClose');
            // this.options.closeSettings();
            // }
        }

        build(placeToBuild = '') {
            this.colorBlock = document.createElement('DIV');


            this.colorBlock.innerHTML = this.name;//izveido nosaukuma paragrāfu
            this.colorBlock.setAttribute('name', this.value);//lai varētu vēlāk iegūt funkciju vērtības no elementa name
            this.colorBlock.classList.add('lampButton');
            // this.colorBlock.classList.add('no_selection');
            if (this.options != '') {
                this.colorBlock.classList.add('lampGroup');//lai būtu atšķirība no parastājām lampu pogām
            }

            // console.log(this.colorBlock.style.backgroundColor);
            // this.textColor = parseToRGBA(this.colorBlock.style.background);
            // console.log(this.textColor);
            // this.colorBlock.style.color = getContrast(this.colorValue.slice(0,3));


            this.colorBlock.onclick = methodize(this.sendButtonValue, this);//pievieno klikšķa iespēju
            if (typeof placeToBuild == 'number') {//izvēlās, kurā vietā tiks būvēta nākamā lampu poga
                document.getElementsByClassName('groupButtonHolder')[placeToBuild].appendChild(this.colorBlock);
            }

            if (this.options != '') {//pievieno dubultklikšķa iespēju
                this.colorBlock.ondblclick = methodize(this.doubleClick, this);
            }
        }

        doubleClick() {
            this.options.open('', this.colorBlock, this);
        }

        sendButtonValue() {
            currentLampString = this.value;
            document.getElementById('displayCurrentLamp').innerHTML = this.name;
            console.log('CurrentLampValue', this.value);
        }

        updateData(name = '', value = '') {//apdeito lampBlock elementu
            if (name != this.name && name != '' && typeof name != 'undefined') {//pārbauda vai var apdeitot vārdu
                this.colorBlock.innerHTML = name;
            } else if (createGroupString(value[0], value[1]) != this.value && !value.includes('') && !value.includes(undefined)) {//pārbauda vai var apdeitot vērtību
                console.log(value[1]);
                this.value = createGroupString(value[0], value[1]);
            }
        }
    }


</script>
<script>
    class SettingsPopUp {//pop elementu klase
        constructor(title, inputFields, buttonCount, type, classIndex, createType = '') {
            this.title = title;//popapa virsraksts
            this.inputFields = inputFields;//visu ievades lauciņu raksturojumi
            this.buttonCount = buttonCount;//Pogu daudzums

            this.popUp;//PopUp elementa galvenais div
            this.data;//saglabā lietotāja ievadītos input datus

            this.type = type;//nosaka vai šī ir grupas, animācijas, vai krāsu poga, STĀV NEIZMANTOTS

            this.classIndex = classIndex;//nepieciešams, lai manipulētu ar vairākiem settingu elementiem
            this.createType = createType;//ja ir jāizveido kādus jaunus elementus, tad nosaka to tipu

            this.dataIn;//klases globālais mainīgais, lai varētu apstrādāt ienākošos datus
            this.thisElement;//tiek padots objekta HTML elements, caur kuru arī atvēra settings 
            this.thisObj;//tiek saglabāts esošais objekts, caur kuru tika atvērts settings
        }

        build() {
            this.popUp = buildElementNode('DIV', 'settingsPopUp');//izveido pop up divu
            this.popElement = buildElementNode('FORM', 'popUpForm');
            this.popUp.appendChild(buildElementNode('H3', 'settingsPopTitle', this.title));//izveido virsrakstu

            var inputCount = this.inputFields.length;
            for (var i = 0; i < inputCount; i++) {//izveido visus ievades lauciņus
                if (this.inputFields[i][1] != 'double') {
                    this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
                    this.createInput = buildElementNode('INPUT', this.inputFields[i][1]);
                    this.createInput.classList.add('popUpInput');
                    this.popElement.appendChild(this.createInput);
                } else {
                    this.popElement.appendChild(buildElementNode('P', '', this.inputFields[i][0]));
                }
            }
            this.buttonHolder = buildElementNode('DIV', 'actionButtonsHolder');//izveido pogas divu
            if (this.buttonCount == 2) {
                this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-success'], 'Save'));
                this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-default'], 'Close'));
            } else {//ja ir visas 3 pogas
                this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-success'], 'Save'));
                this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-danger'], 'Delete'));
                this.buttonHolder.appendChild(buildElementNode('BUTTON', ['actionButton', 'btn', 'btn-default'], 'Close'));
            }

            this.popUp.appendChild(this.popElement);
            this.popUp.appendChild(this.buttonHolder);//pievieno pogas galvenajam divam
            this.popElement = document.body.appendChild(this.popUp);//pop up element, lai ar to varētu turpāk veikt manipulācijas


            if (this.buttonCount == 3) {
                this.popElement.getElementsByClassName('actionButton')[0].onclick = methodize(this.save, this);

                this.popElement.getElementsByClassName('actionButton')[1].onclick = methodize(this.delete, this);
                this.popElement.getElementsByClassName('actionButton')[2].onclick = methodize(this.closeSettings, this);
            } else {
                this.popElement.getElementsByClassName('actionButton')[0].onclick = methodize(this.save, this);
                this.popElement.getElementsByClassName('actionButton')[1].onclick = methodize(this.closeSettings, this);
            }
            document.getElementsByClassName('settingsPopUp')[0].style.display = 'none';
            backShadow(false);//iestata fona ēnu

        }

        open(dataIn = '', thisElement = '', thisObj) {//parāda settings logu
            this.dataIn = dataIn;
            this.thisElement = thisElement;
            this.thisObj = thisObj;
            backShadow(true);
            this.popUp.style.display = 'block';
        }

        save() {
            //nosūta uz serveri lietotāja jaunos ievadītos datus un izveido jaunus elementus, ja tas ir nepieciešams
            // this.dataIn = dataIn;//ja ir kkādi dati, kas ir papildus jāapstrādā saglabājot
            // console.log('thisDataIn:', this.dataIn);
            // console.log('dataIn: ', dataIn);
            this.formCount = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT').length;
            this.inputElem = document.getElementsByClassName('settingsPopUp')[this.classIndex].getElementsByTagName('INPUT');



            if (this.formCount > 0) {//ja ir bijusi viesmaz viena forma
                this.saveName = 'name=' + this.inputElem[0].value;//nolasa input datus un atbilstoši tos pārveido
                if (this.formCount < 3) {
                    // this.saveValue = 'value=' + this.inputElem[1].value;
                } else if (this.formCount == 3) {
                    this.saveValue = 'value=' + createGroupString(this.inputElem[1].value, this.inputElem[2].value);
                }
            }

            if (this.createType != '') {//ja dotajam settings logam ir jāizveido vēl kāds jauns elements
                switch (this.createType) {
                    case 'group':
                        createNewLampGroup(this.inputElem[0].value, createGroupString(this.inputElem[1].value, this.inputElem[2].value), editGroupSettings, true);
                        break;
                    case 'color':
                        if (colorCount == colorLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                            alert('You have already saved ' + colorLimit + ' colors');
                        } else {
                            this.createColorButt = new ColorBlock(this.inputElem[0].value, userRgbw, 'colorBlock', editColorButton);
                            document.getElementById('colorBlockContent').appendChild(this.createColorButt.build());
                            this.createColorButt.grow(document.getElementById('colorBlockContent').offsetWidth - this.createColorButt.blockWidth());
                            colorCount++;
                        }
                        break;
                    case 'animation':
                        break;
                    case 'add':
                        if (this.dataIn.length == 5) {//ja ir jāizveido jauns krāsu bloks
                            if (colorCount == colorLimit) {//salīdina vai jau ir sasniegts krāsu saglabāšanas limits
                                alert('You have already saved ' + colorLimit + ' colors');
                            } else {
                                this.createColorButt = new ColorBlock(this.dataIn[4], this.dataIn.slice(0, 4), 'colorBlock', editColorButton);
                                document.getElementById('colorBlockContent').appendChild(this.createColorButt.build());
                                this.createColorButt.grow();
                                colorCount++;
                            }
                        } else {
                            if (animCount == animLimit) {
                                alert('You have already saved ' + animLimit + ' animations');
                            } else {
                                // console.log(this.dataIn.slice(0, 2));
                                this.createColorButt = new AnimationsBlock(this.dataIn[2], this.dataIn.slice(0, 2), 'animBlock', editAnimButton);
                                document.getElementById('animBlockContent').appendChild(this.createColorButt.buildAnimBlock());
                                animCount++;
                            }
                        }
                        break;
                    case 'updateGroup'://apdeito grupu pogu
                        this.thisObj.updateData(this.inputElem[0].value, [this.inputElem[1].value, this.inputElem[2].value]);//apdeuto group pogas datus
                        break;
                    case 'updateColor'://apdeito krāsu pogu
                        this.thisObj.updateData(this.inputElem[0].value);
                        break;
                    case 'updateAnimation'://apdeito animāciju pogu
                        this.thisObj.updateData(this.inputElem[0].value, this.inputElem[1].value);
                        break;
                }
            }

            ajaxConsoleSend(this.saveName + ' ' + this.saveValue);//nosūta datus uz serveri
            document.getElementsByClassName('popUpForm')[this.classIndex].reset();//reseto formu
            // console.log('save');
        }

        closeSettings() {//noslēpj settings logu
            backShadow(false);//iestata fona ēnu
            document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
            // console.log('close');
        }

        delete() {//izdzēš atbilstošo vērtību un elementu
            // console.log(this.thisElement.className);
            this.thisElement.remove();//izdzēš objektu iestatot tā vērtību uz 0
            if (this.thisElement.className == 'lampButton lampGroup') {
                currentLampString = '1-25#';
                checkButtHolders();//Atbilstoši pabīda pogas un saliek tās savās vietās
                riseGroupButts();  //Piešķir pārvietotajām pogām nepieciešamos izmērus
            } else if (this.thisElement.className == 'colorBlock') {
                // console.log(this.thisElement);
                growColors();
                // debugger;
            }
            backShadow(false);//iestata fona ēnu
            document.getElementsByClassName('settingsPopUp')[this.classIndex].style.display = 'none';
        }
    }

    function growColors() {
        var place = document.getElementById('colorBlockContent');
        // console.log(place);
        var placeWidth = place.clientWidth;
        // console.log('PLACEWIDTH: ', placeWidth)
        var buttonWidth = 0;
        for (var i = 0; i < place.childElementCount; i++) {
            buttonWidth += place.getElementsByClassName('colorBlock')[i].offsetWidth + 5;
            // console.log('element: ', place.getElementsByClassName('colorBlock')[i]);
            // console.log('DIFFERENCE: ', placeWidth - buttonWidth);
            if (placeWidth - buttonWidth <= 2 && placeWidth - buttonWidth >= 0) {
                buttonWidth = 0;
                // console.log('C');
            } else if (placeWidth - buttonWidth < 0 && i != place.childElementCount - 1) {
                // console.log('A');
                place.getElementsByClassName('colorBlock')[i - 1].style.width = place.getElementsByClassName('colorBlock')[i - 1].offsetWidth + placeWidth - (buttonWidth - place.getElementsByClassName('colorBlock')[i].offsetWidth) + 5 + 'px';
                buttonWidth = place.getElementsByClassName('colorBlock')[i].offsetWidth + 5;
            } else if (i == place.childElementCount - 1 && placeWidth - buttonWidth > 1) {//Ja pēdējais elements
                // console.log('B', place.getElementsByClassName('colorBlock')[i]);
                // console.log(buttonWidth);
                // console.log(placeWidth);
                place.getElementsByClassName('colorBlock')[i].style.width = place.getElementsByClassName('colorBlock')[i].offsetWidth + placeWidth - buttonWidth + 'px';
            }
            // console.log('BUTTONWIDTH: ', buttonWidth);
            // console.log('PLACEWIDTH: ', placeWidth);
            // console.log('---------------------------------------------------');
        }
        // console.log('///////////////////////////////////////////////////////////////////////////////////////////');
    }
</script>
<script>
    /*!
     * iro.js v4.5.3
     * 2016-2019 James Daniel
     * Licensed under MPL 2.0
     * github.com/jaames/iro.js
     */
    !function (t, e) { "object" == typeof exports && "undefined" != typeof module ? module.exports = e() : "function" == typeof define && define.amd ? define(e) : t.iro = e() }(this, function () { "use strict"; var c = function () { }, i = {}, h = [], u = []; function p(t, e) { var o, n, r, i, s = arguments, a = u; for (i = arguments.length; 2 < i--;)h.push(s[i]); for (e && null != e.children && (h.length || h.push(e.children), delete e.children); h.length;)if ((n = h.pop()) && void 0 !== n.pop) for (i = n.length; i--;)h.push(n[i]); else "boolean" == typeof n && (n = null), (r = "function" != typeof t) && (null == n ? n = "" : "number" == typeof n ? n = String(n) : "string" != typeof n && (r = !1)), r && o ? a[a.length - 1] += n : a === u ? a = [n] : a.push(n), o = r; var l = new c; return l.nodeName = t, l.children = a, l.attributes = null == e ? void 0 : e, l.key = null == e ? void 0 : e.key, l } function M(t, e) { for (var o in e) t[o] = e[o]; return t } function l(t, e) { null != t && ("function" == typeof t ? t(e) : t.current = e) } var e = "function" == typeof Promise ? Promise.resolve().then.bind(Promise.resolve()) : setTimeout, f = /acit|ex(?:s|g|n|p|$)|rph|ows|mnc|ntw|ine[ch]|zoo|^ord/i, o = []; function s(t) { !t._dirty && (t._dirty = !0) && 1 == o.push(t) && e(n) } function n() { for (var t; t = o.pop();)t._dirty && I(t) } function S(t, e) { return t.normalizedNodeName === e || t.nodeName.toLowerCase() === e.toLowerCase() } function E(t) { var e = M({}, t.attributes); e.children = t.children; var o = t.nodeName.defaultProps; if (void 0 !== o) for (var n in o) void 0 === e[n] && (e[n] = o[n]); return e } function N(t) { var e = t.parentNode; e && e.removeChild(t) } function v(t, e, o, n, r) { if ("className" === e && (e = "class"), "key" === e); else if ("ref" === e) l(o, null), l(n, t); else if ("class" !== e || r) if ("style" === e) { if (n && "string" != typeof n && "string" != typeof o || (t.style.cssText = n || ""), n && "object" == typeof n) { if ("string" != typeof o) for (var i in o) i in n || (t.style[i] = ""); for (var i in n) t.style[i] = "number" == typeof n[i] && !1 === f.test(i) ? n[i] + "px" : n[i] } } else if ("dangerouslySetInnerHTML" === e) n && (t.innerHTML = n.__html || ""); else if ("o" == e[0] && "n" == e[1]) { var s = e !== (e = e.replace(/Capture$/, "")); e = e.toLowerCase().substring(2), n ? o || t.addEventListener(e, d, s) : t.removeEventListener(e, d, s), (t._listeners || (t._listeners = {}))[e] = n } else if ("list" !== e && "type" !== e && !r && e in t) { try { t[e] = null == n ? "" : n } catch (t) { } null != n && !1 !== n || "spellcheck" == e || t.removeAttribute(e) } else { var a = r && e !== (e = e.replace(/^xlink:?/, "")); null == n || !1 === n ? a ? t.removeAttributeNS("http://www.w3.org/1999/xlink", e.toLowerCase()) : t.removeAttribute(e) : "function" != typeof n && (a ? t.setAttributeNS("http://www.w3.org/1999/xlink", e.toLowerCase(), n) : t.setAttribute(e, n)) } else t.className = n || "" } function d(t) { return this._listeners[t.type](t) } var T = [], H = 0, g = !1, _ = !1; function P() { for (var t; t = T.shift();)t.componentDidMount && t.componentDidMount() } function A(t, e, o, n, r, i) { H++ || (g = null != r && void 0 !== r.ownerSVGElement, _ = null != t && !("__preactattr_" in t)); var s = U(t, e, o, n, i); return r && s.parentNode !== r && r.appendChild(s), --H || (_ = !1, i || P()), s } function U(t, e, o, n, r) { var i = t, s = g; if (null != e && "boolean" != typeof e || (e = ""), "string" == typeof e || "number" == typeof e) return t && void 0 !== t.splitText && t.parentNode && (!t._component || r) ? t.nodeValue != e && (t.nodeValue = e) : (i = document.createTextNode(e), t && (t.parentNode && t.parentNode.replaceChild(i, t), O(t, !0))), i.__preactattr_ = !0, i; var a, l, c = e.nodeName; if ("function" == typeof c) return function (t, e, o, n) { var r = t && t._component, i = r, s = t, a = r && t._componentConstructor === e.nodeName, l = a, c = E(e); for (; r && !l && (r = r._parentComponent);)l = r.constructor === e.nodeName; r && l && (!n || r._component) ? (j(r, c, 3, o, n), t = r.base) : (i && !a && (L(i), t = s = null), r = R(e.nodeName, c, o), t && !r.nextBase && (r.nextBase = t, s = null), j(r, c, 1, o, n), t = r.base, s && t !== s && (s._component = null, O(s, !1))); return t }(t, e, o, n); if (g = "svg" === c || "foreignObject" !== c && g, c = String(c), (!t || !S(t, c)) && (a = c, (l = g ? document.createElementNS("http://www.w3.org/2000/svg", a) : document.createElement(a)).normalizedNodeName = a, i = l, t)) { for (; t.firstChild;)i.appendChild(t.firstChild); t.parentNode && t.parentNode.replaceChild(i, t), O(t, !0) } var h = i.firstChild, u = i.__preactattr_, p = e.children; if (null == u) { u = i.__preactattr_ = {}; for (var f = i.attributes, d = f.length; d--;)u[f[d].name] = f[d].value } return !_ && p && 1 === p.length && "string" == typeof p[0] && null != h && void 0 !== h.splitText && null == h.nextSibling ? h.nodeValue != p[0] && (h.nodeValue = p[0]) : (p && p.length || null != h) && function (t, e, o, n, r) { var i, s, a, l, c, h = t.childNodes, u = [], p = {}, f = 0, d = 0, v = h.length, g = 0, _ = e ? e.length : 0; if (0 !== v) for (var m = 0; m < v; m++) { var y = h[m], b = y.__preactattr_, w = _ && b ? y._component ? y._component.__key : b.key : null; null != w ? (f++ , p[w] = y) : (b || (void 0 !== y.splitText ? !r || y.nodeValue.trim() : r)) && (u[g++] = y) } if (0 !== _) for (var m = 0; m < _; m++) { l = e[m], c = null; var w = l.key; if (null != w) f && void 0 !== p[w] && (c = p[w], p[w] = void 0, f--); else if (d < g) for (i = d; i < g; i++)if (void 0 !== u[i] && (x = s = u[i], C = r, "string" == typeof (k = l) || "number" == typeof k ? void 0 !== x.splitText : "string" == typeof k.nodeName ? !x._componentConstructor && S(x, k.nodeName) : C || x._componentConstructor === k.nodeName)) { c = s, u[i] = void 0, i === g - 1 && g-- , i === d && d++; break } c = U(c, l, o, n), a = h[m], c && c !== t && c !== a && (null == a ? t.appendChild(c) : c === a.nextSibling ? N(a) : t.insertBefore(c, a)) } var x, k, C; if (f) for (var m in p) void 0 !== p[m] && O(p[m], !1); for (; d <= g;)void 0 !== (c = u[g--]) && O(c, !1) }(i, p, o, n, _ || null != u.dangerouslySetInnerHTML), function (t, e, o) { var n; for (n in o) e && null != e[n] || null == o[n] || v(t, n, o[n], o[n] = void 0, g); for (n in e) "children" === n || "innerHTML" === n || n in o && e[n] === ("value" === n || "checked" === n ? t[n] : o[n]) || v(t, n, o[n], o[n] = e[n], g) }(i, e.attributes, u), g = s, i } function O(t, e) { var o = t._component; o ? L(o) : (null != t.__preactattr_ && l(t.__preactattr_.ref, null), !1 !== e && null != t.__preactattr_ || N(t), r(t)) } function r(t) { for (t = t.lastChild; t;) { var e = t.previousSibling; O(t, !0), t = e } } var a = []; function R(t, e, o) { var n, r = a.length; for (t.prototype && t.prototype.render ? (n = new t(e, o), y.call(n, e, o)) : ((n = new y(e, o)).constructor = t, n.render = m); r--;)if (a[r].constructor === t) return n.nextBase = a[r].nextBase, a.splice(r, 1), n; return n } function m(t, e, o) { return this.constructor(t, o) } function j(t, e, o, n, r) { t._disable || (t._disable = !0, t.__ref = e.ref, t.__key = e.key, delete e.ref, delete e.key, void 0 === t.constructor.getDerivedStateFromProps && (!t.base || r ? t.componentWillMount && t.componentWillMount() : t.componentWillReceiveProps && t.componentWillReceiveProps(e, n)), n && n !== t.context && (t.prevContext || (t.prevContext = t.context), t.context = n), t.prevProps || (t.prevProps = t.props), t.props = e, t._disable = !1, 0 !== o && (1 !== o && !1 === i.syncComponentUpdates && t.base ? s(t) : I(t, 1, r)), l(t.__ref, t)) } function I(t, e, o, n) { if (!t._disable) { var r, i, s, a = t.props, l = t.state, c = t.context, h = t.prevProps || a, u = t.prevState || l, p = t.prevContext || c, f = t.base, d = t.nextBase, v = f || d, g = t._component, _ = !1, m = p; if (t.constructor.getDerivedStateFromProps && (l = M(M({}, l), t.constructor.getDerivedStateFromProps(a, l)), t.state = l), f && (t.props = h, t.state = u, t.context = p, 2 !== e && t.shouldComponentUpdate && !1 === t.shouldComponentUpdate(a, l, c) ? _ = !0 : t.componentWillUpdate && t.componentWillUpdate(a, l, c), t.props = a, t.state = l, t.context = c), t.prevProps = t.prevState = t.prevContext = t.nextBase = null, t._dirty = !1, !_) { r = t.render(a, l, c), t.getChildContext && (c = M(M({}, c), t.getChildContext())), f && t.getSnapshotBeforeUpdate && (m = t.getSnapshotBeforeUpdate(h, u)); var y, b, w = r && r.nodeName; if ("function" == typeof w) { var x = E(r); (i = g) && i.constructor === w && x.key == i.__key ? j(i, x, 1, c, !1) : (y = i, t._component = i = R(w, x, c), i.nextBase = i.nextBase || d, i._parentComponent = t, j(i, x, 0, c, !1), I(i, 1, o, !0)), b = i.base } else s = v, (y = g) && (s = t._component = null), (v || 1 === e) && (s && (s._component = null), b = A(s, r, c, o || !f, v && v.parentNode, !0)); if (v && b !== v && i !== g) { var k = v.parentNode; k && b !== k && (k.replaceChild(b, v), y || (v._component = null, O(v, !1))) } if (y && L(y), (t.base = b) && !n) { for (var C = t, S = t; S = S._parentComponent;)(C = S).base = b; b._component = C, b._componentConstructor = C.constructor } } for (!f || o ? T.push(t) : _ || t.componentDidUpdate && t.componentDidUpdate(h, u, m); t._renderCallbacks.length;)t._renderCallbacks.pop().call(t); H || n || P() } } function L(t) { var e = t.base; t._disable = !0, t.componentWillUnmount && t.componentWillUnmount(), t.base = null; var o = t._component; o ? L(o) : e && (null != e.__preactattr_ && l(e.__preactattr_.ref, null), N(t.nextBase = e), a.push(t), r(e)), l(t.__ref, null) } function y(t, e) { this._dirty = !0, this.context = e, this.props = t, this.state = this.state || {}, this._renderCallbacks = [] } function b(t, e, o, n) { void 0 === n && (n = {}); for (var r = 0; r < e.length; r++)t.addEventListener(e[r], o, n) } function w(t, e, o, n) { void 0 === n && (n = {}); for (var r = 0; r < e.length; r++)t.removeEventListener(e[r], o, n) } M(y.prototype, { setState: function (t, e) { this.prevState || (this.prevState = this.state), this.state = M(M({}, this.state), "function" == typeof t ? t(this.state, this.props) : t), e && this._renderCallbacks.push(e), s(this) }, forceUpdate: function (t) { t && this._renderCallbacks.push(t), I(this, 2) }, render: function () { } }); var x = "mousedown", k = "mousemove", C = "mouseup", B = "touchstart", D = "touchmove", W = "touchend", t = function (e) { function t(t) { e.call(this, t), this.uid = (Math.random() + 1).toString(36).substring(5) } return e && (t.__proto__ = e), ((t.prototype = Object.create(e && e.prototype)).constructor = t).prototype.componentDidMount = function () { b(this.base, [x, B], this, { passive: !1 }) }, t.prototype.componentWillUnmount = function () { w(this.base, [x, B], this) }, t.prototype.handleEvent = function (t) { t.preventDefault(); var e = t.touches ? t.changedTouches[0] : t, o = e.clientX, n = e.clientY, r = this.base.getBoundingClientRect(); switch (t.type) { case x: case B: b(document, [k, D, C, W], this, { passive: !1 }), this.handleInput(o, n, r, "START"); break; case k: case D: this.handleInput(o, n, r, "MOVE"); break; case C: case W: this.handleInput(o, n, r, "END"), w(document, [k, D, C, W], this, { passive: !1 }) } }, t }(y), V = document.getElementsByTagName("base"); function F(t) { var e = window.location, o = window.navigator.userAgent, n = /^((?!chrome|android).)*safari/i.test(o), r = /iPhone|iPod|iPad/i.test(o); return (n || r) && 0 < V.length ? e.protocol + "//" + e.host + e.pathname + e.search + t : t } function $(t, e, o, n, r) { var i = r - n <= 180 ? 0 : 1; return n *= Math.PI / 180, r *= Math.PI / 180, "M " + (t + o * Math.cos(r)) + " " + (e + o * Math.sin(r)) + " A " + o + " " + o + " 0 " + i + " 0 " + (t + o * Math.cos(n)) + " " + (e + o * Math.sin(n)) } function G(t) { var e = t.r, o = t.url; return p("svg", { class: "iro__handle", x: t.x, y: t.y, style: { overflow: "visible" } }, o && p("use", Object.assign({}, { xlinkHref: F(o) }, t.origin)), !o && p("circle", { class: "iro__handle__inner", r: e, fill: "none", "stroke-width": 2, stroke: "#000" }), !o && p("circle", { class: "iro__handle__outer", r: e - 2, fill: "none", "stroke-width": 2, stroke: "#fff" })) } G.defaultProps = { x: 0, y: 0, r: 8, url: null, origin: { x: 0, y: 0 } }; var z = Array.apply(null, { length: 360 }).map(function (t, e) { return e }), q = function (t) { function e() { t.apply(this, arguments) } return t && (e.__proto__ = t), ((e.prototype = Object.create(t && t.prototype)).constructor = e).prototype._transformAngle = function (t, e) { var o = this.props.wheelAngle; return ((t = "clockwise" === this.props.wheelDirection ? -360 + t - (e ? -o : o) : o - t) % 360 + 360) % 360 }, e.prototype.render = function (t) { var e = this, o = t.width, n = t.borderWidth, r = t.handleRadius, i = t.color.hsv, s = o / 2 - n, a = this._transformAngle(i.h, !0) * (Math.PI / 180), l = i.s / 100 * (s - t.padding - r - n), c = s + n, h = s + n; return p("svg", { class: "iro__wheel", width: o, height: o, style: { overflow: "visible", display: "block" } }, p("defs", null, p("radialGradient", { id: this.uid }, p("stop", { offset: "0%", "stop-color": "#fff" }), p("stop", { offset: "100%", "stop-color": "#fff", "stop-opacity": "0" }))), p("g", { class: "iro__wheel__hue", "stroke-width": s, fill: "none" }, z.map(function (t) { return p("path", { key: t, d: $(c, h, s / 2, t, t + 1.5), stroke: "hsl(" + e._transformAngle(t) + ", 100%, 50%)" }) })), p("circle", { class: "iro__wheel__saturation", cx: c, cy: h, r: s, fill: "url(" + F("#" + this.uid) + ")" }), t.wheelLightness && p("circle", { class: "iro__wheel__lightness", cx: c, cy: h, r: s, fill: "#000", opacity: 1 - i.v / 100 }), p("circle", { class: "iro__wheel__border", cx: c, cy: h, r: s, fill: "none", stroke: t.borderColor, "stroke-width": n }), p(G, { r: r, url: t.handleSvg, origin: t.handleOrigin, x: c + l * Math.cos(a), y: h + l * Math.sin(a) })) }, e.prototype.handleInput = function (t, e, o, n) { var r = o.left, i = o.top, s = this.props, a = s.width / 2, l = a - s.padding - s.handleRadius - s.borderWidth; t = a - (t - r), e = a - (e - i); var c = Math.atan2(e, t), h = this._transformAngle(Math.round(c * (180 / Math.PI)) + 180), u = Math.min(Math.sqrt(t * t + e * e), l); s.onInput(n, { h: h, s: Math.round(100 / l * u) }) }, e }(t); function X(t, e) { var o = -1 < t.indexOf("%"), n = parseFloat(t); return o ? e / 100 * n : n } function Y(t) { return parseInt(t, 16) } function J(t) { return t.toString(16).padStart(2, "0") } var K = "(?:[-\\+]?\\d*\\.\\d+%?)|(?:[-\\+]?\\d+%?)", Q = "[\\s|\\(]+(" + K + ")[,|\\s]+(" + K + ")[,|\\s]+(" + K + ")\\s*\\)?", Z = "[\\s|\\(]+(" + K + ")[,|\\s]+(" + K + ")[,|\\s]+(" + K + ")[,|\\s]+(" + K + ")\\s*\\)?", tt = new RegExp("rgb" + Q), et = new RegExp("rgba" + Z), ot = new RegExp("hsl" + Q), nt = new RegExp("hsla" + Z), rt = "^(?:#?|0x?)", it = "([0-9a-fA-F]{1})", st = "([0-9a-fA-F]{2})", at = new RegExp("" + rt + it + it + it + "$"), lt = new RegExp("" + rt + it + it + it + it + "$"), ct = new RegExp("" + rt + st + st + st + "$"), ht = new RegExp("" + rt + st + st + st + st + "$"), ut = function (t) { this._onChange = !1, this._value = { h: 0, s: 0, v: 0, a: 1 }, t && this.set(t) }, pt = { hsv: { configurable: !0 }, rgb: { configurable: !0 }, hsl: { configurable: !0 }, rgbString: { configurable: !0 }, hexString: { configurable: !0 }, hslString: { configurable: !0 } }; ut.prototype.set = function (t) { var e = "string" == typeof t, o = "object" == typeof t; if (e && /^(?:#?|0x?)[0-9a-fA-F]{3,8}$/.test(t)) this.hexString = t; else if (e && /^rgba?/.test(t)) this.rgbString = t; else if (e && /^hsla?/.test(t)) this.hslString = t; else if (o && t instanceof ut) this.hsv = t.hsv; else if (o && "r" in t && "g" in t && "b" in t) this.rgb = t; else if (o && "h" in t && "s" in t && "v" in t) this.hsv = t; else { if (!(o && "h" in t && "s" in t && "l" in t)) throw new Error("invalid color value"); this.hsl = t } }, ut.prototype.setChannel = function (t, e, o) { var n; this[t] = Object.assign({}, this[t], ((n = {})[e] = o, n)) }, ut.prototype.clone = function () { return new ut(this) }, ut.hsvToRgb = function (t) { var e = t.h / 60, o = t.s / 100, n = t.v / 100, r = Math.floor(e), i = e - r, s = n * (1 - o), a = n * (1 - i * o), l = n * (1 - (1 - i) * o), c = r % 6; return { r: 255 * [n, a, s, s, l, n][c], g: 255 * [l, n, n, a, s, s][c], b: 255 * [s, s, l, n, n, a][c] } }, ut.rgbToHsv = function (t) { var e, o = t.r / 255, n = t.g / 255, r = t.b / 255, i = Math.max(o, n, r), s = Math.min(o, n, r), a = i - s, l = i, c = 0 === i ? 0 : a / i; switch (i) { case s: e = 0; break; case o: e = (n - r) / a + (n < r ? 6 : 0); break; case n: e = (r - o) / a + 2; break; case r: e = (o - n) / a + 4 }return { h: 60 * e, s: 100 * c, v: 100 * l } }, ut.hsvToHsl = function (t) { var e = t.s / 100, o = t.v / 100, n = (2 - e) * o, r = n <= 1 ? n : 2 - n, i = r < 1e-9 ? 0 : e * o / r; return { h: t.h, s: 100 * i, l: 50 * n } }, ut.hslToHsv = function (t) { var e = 2 * t.l, o = t.s * (e <= 100 ? e : 200 - e) / 100, n = e + o < 1e-9 ? 0 : 2 * o / (e + o); return { h: t.h, s: 100 * n, v: (e + o) / 2 } }, pt.hsv.get = function () { var t = this._value; return { h: t.h, s: t.s, v: t.v } }, pt.hsv.set = function (t) { var e = this._value; if (t = Object.assign({}, e, t), this._onChange) { var o = {}; for (var n in e) o[n] = t[n] != e[n]; this._value = t, (o.h || o.s || o.v || o.a) && this._onChange(this, o) } else this._value = t }, pt.rgb.get = function () { var t = ut.hsvToRgb(this._value), e = t.r, o = t.g, n = t.b; return { r: Math.round(e), g: Math.round(o), b: Math.round(n) } }, pt.rgb.set = function (t) { this.hsv = Object.assign({}, ut.rgbToHsv(t), { a: void 0 === t.a ? 1 : t.a }) }, pt.hsl.get = function () { var t = ut.hsvToHsl(this._value), e = t.h, o = t.s, n = t.l; return { h: Math.round(e), s: Math.round(o), l: Math.round(n) } }, pt.hsl.set = function (t) { this.hsv = Object.assign({}, ut.hslToHsv(t), { a: void 0 === t.a ? 1 : t.a }) }, pt.rgbString.get = function () { var t = this.rgb; return "rgb(" + t.r + ", " + t.g + ", " + t.b + ")" }, pt.rgbString.set = function (t) { var e, o, n, r, i = 1; if ((e = tt.exec(t)) ? (o = X(e[1], 255), n = X(e[2], 255), r = X(e[3], 255)) : (e = et.exec(t)) && (o = X(e[1], 255), n = X(e[2], 255), r = X(e[3], 255), i = X(e[4], 1)), !e) throw new Error("invalid rgb string"); this.rgb = { r: o, g: n, b: r, a: i } }, pt.hexString.get = function () { var t = this.rgb; return "#" + J(t.r) + J(t.g) + J(t.b) }, pt.hexString.set = function (t) { var e, o, n, r, i = 255; if ((e = at.exec(t)) ? (o = 17 * Y(e[1]), n = 17 * Y(e[2]), r = 17 * Y(e[3])) : (e = lt.exec(t)) ? (o = 17 * Y(e[1]), n = 17 * Y(e[2]), r = 17 * Y(e[3]), i = 17 * Y(e[4])) : (e = ct.exec(t)) ? (o = Y(e[1]), n = Y(e[2]), r = Y(e[3])) : (e = ht.exec(t)) && (o = Y(e[1]), n = Y(e[2]), r = Y(e[3]), i = Y(e[4])), !e) throw new Error("invalid hex string"); this.rgb = { r: o, g: n, b: r, a: i / 255 } }, pt.hslString.get = function () { var t = this.hsl; return "hsl(" + t.h + ", " + t.s + "%, " + t.l + "%)" }, pt.hslString.set = function (t) { var e, o, n, r, i = 1; if ((e = ot.exec(t)) ? (o = X(e[1], 360), n = X(e[2], 100), r = X(e[3], 100)) : (e = nt.exec(t)) && (o = X(e[1], 360), n = X(e[2], 100), r = X(e[3], 100), i = X(e[4], 1)), !e) throw new Error("invalid hsl string"); this.hsl = { h: o, s: n, l: r, a: i } }, Object.defineProperties(ut.prototype, pt); var ft = function (t) { function e() { t.apply(this, arguments) } return t && (e.__proto__ = t), ((e.prototype = Object.create(t && t.prototype)).constructor = e).prototype.renderGradient = function (t) { var e = t.color.hsv, o = []; switch (t.sliderType) { case "hue": o = [{ offset: "0", color: "#f00" }, { offset: "16.666", color: "#ff0" }, { offset: "33.333", color: "#0f0" }, { offset: "50", color: "#0ff" }, { offset: "66.666", color: "#00f" }, { offset: "83.333", color: "#f0f" }, { offset: "100", color: "#f00" }]; break; case "saturation": var n = ut.hsvToHsl({ h: e.h, s: 0, v: e.v }), r = ut.hsvToHsl({ h: e.h, s: 100, v: e.v }); o = [{ offset: "0", color: "hsl(" + n.h + ", " + n.s + "%, " + n.l + "%)" }, { offset: "100", color: "hsl(" + r.h + ", " + r.s + "%, " + r.l + "%)" }]; break; case "value": default: var i = ut.hsvToHsl({ h: e.h, s: e.s, v: 100 }); o = [{ offset: "0", color: "#000" }, { offset: "100", color: "hsl(" + i.h + ", " + i.s + "%, " + i.l + "%)" }] }return p("linearGradient", { id: this.uid }, o.map(function (t) { return p("stop", { offset: t.offset + "%", "stop-color": t.color }) })) }, e.prototype.render = function (t) { var e = t.width, o = t.sliderHeight, n = t.borderWidth, r = t.handleRadius; o = o || 2 * t.padding + 2 * r + 2 * n, this.width = e; var i, s = (this.height = o) / 2, a = e - 2 * s, l = t.color.hsv; switch (t.sliderType) { case "hue": i = l.h /= 3.6; break; case "saturation": i = l.s; break; case "value": default: i = l.v }return p("svg", { class: "iro__slider", width: e, height: o, style: { marginTop: t.sliderMargin, overflow: "visible", display: "block" } }, p("defs", null, this.renderGradient(t)), p("rect", { class: "iro__slider__value", rx: s, ry: s, x: n / 2, y: n / 2, width: e - n, height: o - n, "stroke-width": n, stroke: t.borderColor, fill: "url(" + F("#" + this.uid) + ")" }), p(G, { r: r, url: t.handleSvg, origin: t.handleOrigin, x: s + i / 100 * a, y: o / 2 })) }, e.prototype.getValueFromPoint = function (t, e, o) { var n = o.left, r = this.width - this.height; t -= n + this.height / 2; var i = Math.max(Math.min(t, r), 0); return Math.round(100 / r * i) }, e.prototype.handleInput = function (t, e, o, n) { var r, i, s = this.getValueFromPoint(t, e, o); switch (this.props.sliderType) { case "hue": i = "h", s *= 3.6; break; case "saturation": i = "s"; break; case "value": default: i = "v" }this.props.onInput(n, ((r = {})[i] = s, r)) }, e }(t); var dt = function (e) { function i(t) { e.call(this, t), this.emitHook("init:before"), this._events = {}, this._deferredEvents = {}, this._colorUpdateActive = !1, this._colorUpdateSrc = null, this.id = t.id, this.color = new ut(t.color), this.deferredEmit("color:init", this.color, { h: !1, s: !1, v: !1, a: !1 }), this.color._onChange = this.updateColor.bind(this), this.state = Object.assign({}, t, { color: this.color, ref: void 0 }), this.emitHook("init:state"), t.layout ? this.layout = t.layout : this.layout = [{ component: q, options: {} }, { component: ft, options: {} }], this.emitHook("init:after") } return e && (i.__proto__ = e), ((i.prototype = Object.create(e && e.prototype)).constructor = i).prototype.on = function (t, e) { var o = this, n = this._events; (Array.isArray(t) ? t : [t]).forEach(function (t) { o.emitHook("event:on", t, e), (n[t] || (n[t] = [])).push(e), o._deferredEvents[t] && (o._deferredEvents[t].forEach(function (t) { e.apply(null, t) }), o._deferredEvents[t] = []) }) }, i.prototype.off = function (t, o) { var n = this; (Array.isArray(t) ? t : [t]).forEach(function (t) { var e = n._events[t]; n.emitHook("event:off", t, o), e && e.splice(e.indexOf(o), 1) }) }, i.prototype.emit = function (t) { for (var e, o = [], n = arguments.length - 1; 0 < n--;)o[n] = arguments[n + 1]; (e = this).emitHook.apply(e, [t].concat(o)); for (var r = this._events[t] || [], i = 0; i < r.length; i++)r[i].apply(this, o) }, i.prototype.deferredEmit = function (t) { for (var e, o = [], n = arguments.length - 1; 0 < n--;)o[n] = arguments[n + 1]; var r = this._deferredEvents; (e = this).emit.apply(e, [t].concat(o)), (r[t] || (r[t] = [])).push(o) }, i.prototype.resize = function (t) { this.setState({ width: t }) }, i.prototype.reset = function () { this.color.set(this.props.color) }, i.addHook = function (t, e) { var o = i.pluginHooks; (o[t] || (o[t] = [])).push(e) }, i.prototype.emitHook = function (t) { for (var e = [], o = arguments.length - 1; 0 < o--;)e[o] = arguments[o + 1]; for (var n = i.pluginHooks[t] || [], r = 0; r < n.length; r++)n[r].apply(this, e) }, i.prototype.onMount = function (t) { this.el = t, this.deferredEmit("mount", this) }, i.prototype.updateColor = function (t, e) { this.emitHook("color:beforeUpdate", t, e), this.setState({ color: t }), this.emitHook("color:afterUpdate", t, e), this._colorUpdateActive || (this._colorUpdateActive = !0, "input" == this._colorUpdateSrc && this.emit("input:change", t, e), this.emit("color:change", t, e), this._colorUpdateActive = !1) }, i.prototype.handleInput = function (t, e) { "START" === t && this.emit("input:start", this.color), "MOVE" === t && this.emit("input:move", this.color), this._colorUpdateSrc = "input", this.color.hsv = e, "END" === t && this.emit("input:end", this.color), this._colorUpdateSrc = null }, i.prototype.render = function (t, n) { var r = this; return p("div", { class: "iro__colorPicker", id: t.id, style: { display: n.display, width: n.width } }, this.layout.map(function (t) { var e = t.component, o = t.options; return p(e, Object.assign({}, n, o, { onInput: function (t, e) { return r.handleInput(t, e) }, parent: r })) })) }, i }(y); dt.pluginHooks = {}, dt.defaultProps = { width: 300, height: 300, handleRadius: 8, handleSvg: null, handleOrigin: { x: 0, y: 0 }, color: "#fff", borderColor: "#fff", borderWidth: 0, display: "block", id: null, wheelLightness: !0, wheelAngle: 0, wheelDirection: "anticlockwise", sliderHeight: null, sliderMargin: 12, padding: 6, layout: null }; var vt, gt, _t, mt, yt = ((gt = function (e, t) { var o, n, r, i = null, s = document.createElement("div"); return o = p(vt, Object.assign({}, { ref: function (t) { return i = t } }, t)), A(n, o, {}, !1, s, !1), r = function () { var t = e instanceof Element ? e : document.querySelector(e); t.appendChild(i.base), i.onMount(t) }, "loading" !== document.readyState ? r() : b(document, ["DOMContentLoaded"], r), i }).prototype = (vt = dt).prototype, Object.assign(gt, vt), gt.__component = vt, gt); return mt = [], (_t = { Color: ut, ColorPicker: yt, ui: { h: p, Component: t, Handle: G, Slider: ft, Wheel: q }, util: { resolveUrl: F, createArcPath: $, parseUnit: X, parseHexInt: Y, intToHex: J }, version: "4.5.3" }).use = function (t, e) { void 0 === e && (e = {}), -1 < mt.indexOf(t) || (t(_t, e), mt.push(t)) }, _t.installedPlugins = mt, _t });
//# sourceMappingURL=iro.min.js.map

</script>
<script>
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

        //Ievieto 4 vērtības masīvā
        userRgbw = [...userRgbw, color.rgb.r, color.rgb.g, color.rgb.b, whiteColor]

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
    whitePicker.on('input:end', function (color) {//LAI TE NOTIKTU LIETAS TIEK IZVEIDOTS TAIMERIS UZ ONCLICK
        whiteColor = color.rgb.r;
        console.log('User: ', color.rgb.r);
        userRgbw[3] = whiteColor;//pievieno arī baltās krāsas vērtību
        console.log(userRgbw);
        console.log('<0' + currentLampString + stringColorSet(userRgbw) + '>');
    });
</script>

</html>
)=====";
