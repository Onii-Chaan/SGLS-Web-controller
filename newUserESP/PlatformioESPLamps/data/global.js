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

var wifiMode;//softAP or WLAN

var recData = async () => {//Fečo txt failu un izveido lapu
   const res = await fetch(fileUrl);
   const json = await res.json();

   let JSON_DATA = json;//parses json string from session storage

   lampNum = JSON_DATA.LampNum;
   buttonOn = JSON_DATA.OffState;//if buttons were turned on or off

   lampGroups = JSON_DATA.LampGroups;//ienākošo lampu grupu datu masīvs
   funcArr = JSON_DATA.FuncArr;
   rgbwArr = JSON_DATA.RgbwArr;

   wifiMode = JSON_DATA.WIFIMode;

   if(wifiMode == "softAP" && document.getElementsByClassName("radioIn")[0] != null){//for choose connection mode default check
       document.getElementsByClassName("radioIn")[1].checked = true;
   } else if(wifiMode == "WLAN" && document.getElementsByClassName("radioIn")[0] != null){
       document.getElementsByClassName("radioIn")[0].checked = true;
   }

   if (wifiMode == "WLAN")//operating mode (WLAN or softAP)
      USER_SSID = JSON_DATA.UserWlanSsid;
   else
      USER_SSID = JSON_DATA.SoftAPSSID;

   // if (window.location.pathname.split("/").pop() == "softap.html") {//if user is in softAP page
   //    document.getElementById('controllerLink').innerText = JSON_DATA.UserMDNS + ".local";
   //    document.getElementById("controllerLink").href = JSON_DATA.UserMDNS + ".local";
   // }

   exploreArr = JSON_DATA.ExploreArr;
   document.getElementById('SGLSmainName').innerText = USER_SSID;//Iestata lietotāja nosaukuma title
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

