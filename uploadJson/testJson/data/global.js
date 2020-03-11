// var RAW_JSON_DATA;
// var receivedTxt;
var fileUrl = "/configFile.txt";//txt json faila lokācija

var lampNum;//ievadītais lampu daudzums
var buttonOn;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu
var USER_SSID;
var rgbwArr;//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var colorBlockObjArr = [];
var funcArr;
var funcBlockObjArr = [];
var lampGroups;//ienākošo lampu grupu datu masīvs
var exploreArr;
var currentLampString;//jau izveidots string priekš lampu numuriem

// var checkSession = () => {//checks local storage if it has already loaded txt file
//    if (sessionStorage.getItem("jsonLoaded") == null) {
//        return false;
//    }
//    return true;
// }

var recData = async () => {//Fečo txt failu un izveido lapu
   const res = await fetch(fileUrl);
   const json = await res.json();


   let JSON_DATA = json;//parses json string from session storage

   lampNum = JSON_DATA.LampNum;
   buttonOn = JSON_DATA.OffState;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu

   lampGroups = JSON_DATA.LampGroups;//ienākošo lampu grupu datu masīvs
   funcArr = JSON_DATA.FuncArr;
   rgbwArr = JSON_DATA.RgbwArr;
   USER_SSID = JSON_DATA.UserWlanSsid;
   exploreArr = JSON_DATA.ExploreArr;
   document.getElementById('SGLSmainName').innerText = JSON_DATA.UserWlanSsid;//Iestata lietotāja nosaukuma title
   currentLampString = '1-' + lampNum + '#';//jau izveidots string priekš lampu numuriem
   document.getElementById('onOffButton').checked = buttonOn;//iestata ieslēgšanas pogas sākuma stāvokli

   buildSettings();
   createDynamicContent();
   loadingScreen.end();      
}



var lampButtonPressed = "#9ab8a0";//dinamisko pogu krasa kad ta tika nospiesta
var lampButtonDefault = "#6c8270";//dinamisko pogu krasa kad ta nav nospiesta
var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
// var lampNum = "00";//lampu numura String vērtība
var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās
var funcNum = 0;//lampu funkcijas numurs
var currentLamp; //seko līdzi tam, kura lampa ir pašlaik nospiesta
var colorCount = 0;//seko līdzi tam cik krāsu pogu ir saglabāts 
var animCount = 0;//seko līdzi tam cik animāciju pogu ir saglabāts
var groupCount = 0;

var savedLimit = 30;//maksimālais saglabāto elementu daudzums

var brightness = 50;//glabā sevī krāsu apļa spožumu atkarībā no slīdera
var whiteColor = 0;//glabā sevī visiem pieejamu baltās krāsas vērtību 
var userRgbw = [0, 255, 0, 0];//glabā lietotāja saglabātos, pēdējās nospiestās rgbw vērtības 

var onOff = false;//seko līdzi tam, vai lampas ieslēgtas vai izslēgtas



/*
{
   "ExploreArr":[
      [
         "SameColor",
         123,
         123,
         123,
         123
      ],
      [
         "hmhmmhh",
         0,
         23,
         0,
         122
      ],
      [
         "word",
         255,
         255,
         0,
         0
      ],
      [
         "manyWords",
         10,
         10,
         23,
         18
      ],
      [
         "manyMore",
         10,
         23,
         15,
         200
      ],
      [
         "Yeye",
         100,
         200,
         100,
         0
      ],
      [
         "pum_pum",
         25,
         10
      ],
      [
         "animManim",
         50,
         0
      ],
      [
         "someAnim",
         10,
         100
      ],
      [
         "oldAnim",
         19,
         230
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ],
      [
         "NewAnim",
         7,
         123
      ]
   ],
   "RgbwArr":[
      [
         "SomeColor1",
         255,
         255,
         255,
         0
      ],
      [
         "SmallerColorLol",
         255,
         255,
         0,
         0
      ],
      [
         "A",
         0,
         255,
         255,
         0
      ],
      [
         "Here",
         255,
         0,
         255,
         10
      ],
      [
         "InternalSuffering",
         255,
         255,
         0,
         120
      ],
      [
         "words",
         0,
         255,
         255,
         0
      ],
      [
         "manyWords",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ],
      [
         "lettersColor",
         0,
         255,
         255,
         0
      ]
   ],
   "FuncArr":[
      [
         "solid rainbow",
         2,
         10
      ],
      [
         "solid fade",
         3,
         13
      ],
      [
         "blink",
         4,
         540
      ],
      [
         "fire",
         5,
         10
      ],
      [
         "adr rainbow",
         6,
         11
      ],
      [
         "light music",
         7,
         233
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ],
      [
         "testtres",
         1,
         677
      ]
   ],
   "LampGroups":[
      [
         "Room1",
         "1-5#"
      ],
      [
         "BedRoom",
         "2-8#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ],
      [
         "Garden",
         "6-7#"
      ]
   ],
   "LampNum":6,
   "OffState":false,
   "UserWlanSsid":"ElektronikasKlubs"
}
*/