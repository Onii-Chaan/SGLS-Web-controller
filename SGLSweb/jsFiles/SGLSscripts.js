//var totalLamps = Number(prompt("Ievadi lampu daudzumu: "));
var lampButtonPressed = "#9ab8a0";//dinamisko pogu krasa kad ta tika nospiesta
var lampButtonDefault = "#6c8270";//dinamisko pogu krasa kad ta nav nospiesta

var dataType;//izsūtāmo vērtību tips, vai tā ir saskaitīšanās, funkcija vai krāsa
var sendRGBString = "";//nosūtāmā 3 krāsu rgb string vērtība
var rgbw = [0, 0, 0, 0];//šajā sarakstā glabājas 4 krāsu rgbw vērtības
var buttonOn = false;//norada vai lietotajs darbojas ap vienu lampu vai ap visam kopa, tiek izmantots, lai nevaretu ieslegt funkcijas kad darbojas ap vienu lampu
var lampNum = "00";//lampu numura String vērtība
var whiteAllowed = false;//atļauj vai arī aizliedz izmantot balto krāsu funkcijās
var funcNum = 0;//lampu funkcijas numurs
//document.getElementsByClassName("hidable")[0].style.display = "none"; BOOKMARK1



//slīderis priekš brightness
var slider = document.getElementById("myRange");//saņem vērtību no slīdera 0 - 100
var output = document.getElementById("sliderValueText");//mainīgais slīdera vērtībai, ko izvadīt
output.innerHTML = slider.value;

slider.oninput = function () {//izvada vērtību slīderim
  output.innerHTML = this.value;
}



























class Icon {
  constructor(classType, iconSize) {
    this.classType = classType;
    this.iconSize = iconSize;

    this.arrowElem;
    this.arrHoldDiv;
  }

  buildArrow(){
    this.arrHoldDiv = document.createElement('DIV');
    this.arrHoldDiv.classList.add(this.iconSize );
    this.arrHoldDiv.classList.add(this.classType);
    return this.arrHoldDiv;
  }
}



class Bookmark extends Icon{

}


class Arrow extends Icon{
  rotateArrow(position) {//Aprgriež otrādi bultiņu
    if (position) {
      this.arrHoldDiv.setAttribute('style', 'transform:rotate(-45deg)');
    } else {
      this.arrHoldDiv.setAttribute('style', 'transform:rotate(225deg)');
    }
  }
}




class CollapsibleButton {
  constructor(iconObj, textToAppend, elementHolder, elemNumToCreate) {
    
    this.iconObj = iconObj;//ikonas objekts, kas tiks parādīts pogas sānā
    this.textToAppend = textToAppend;//Teksts, kas parādīsies uz pogas
    this.elementHolder = elementHolder;//Elements, kurā atradīsies poga
    this.elemNumToCreate = elemNumToCreate;//Elementu skaits, ko izveidot atverot pogu



    this.collButton;//galvenā poga, kas tiek izveidota
    this.rotateState = false;
    this.smHolder;

    this.objectHolder;
  }


  buildCollapseButton() {//Izveido pogas elementu un tajā esošo kontentu
    this.objectHolder = document.createElement('DIV');
    

    this.collButton = document.createElement('BUTTON');//izveido pogas elementu, kas arī būs pati poga
    this.collButton .style.height = '30px';


    this.collButton.classList.add('collapsibleObj');
    this.collButton.classList.add('collapsible');//pievieno klasi pogai
    this.collButton.classList.add('expandButton');//pievieno klasi pogai

    var textToAdd = document.createTextNode(this.textToAppend);//Izveido tekstu pogai
    this.collButton.appendChild(textToAdd);//pievieno tekstu pogai

  
    this.collButton.appendChild(this.iconObj.buildArrow());//ikona tiek pievienota pogas objektam
    

    this.smHolder = document.createElement("DIV");
    this.smHolder.classList.add('elemPlaceHolder');
    this.smHolder.classList.add('content');
    textToAdd = document.createTextNode(this.textToAppend);//Izveido tekstu pogai
    this.smHolder.appendChild(textToAdd);
    

    
    this.objectHolder.appendChild(this.collButton);//pievieno izveidoto pogu un tās elementus elementam, kur atrodas poga
    this.objectHolder.appendChild(this.smHolder);

    this.elementHolder.appendChild(this.objectHolder);
  }
}

function createColl(placeHolder){//Izveido collapsible div objektu
  var collapsibleObj = new CollapsibleButton(new Arrow("arrow", "medIcon"), "Saved", placeHolder, 2);
  collapsibleObj.buildCollapseButton();

  collObjArr[collObjArrCount] = collapsibleObj;
  collObjArrCount+=1;
  
  createSubColl();


  var coll = document.getElementsByClassName("collapsibleObj");


  for (i = 0; i < coll.length; i++) {
    globalAddEventListener = i;
    
    coll[i].addEventListener("click", function() {
      this.classList.toggle("active");
      var content = this.nextElementSibling;
      
      if (content.style.maxHeight){
        collObjArr[globalAddEventListener].iconObj.rotateArrow(false);
        content.style.maxHeight = null;
      } else {

        collObjArr[globalAddEventListener].iconObj.rotateArrow(true);
        
        content.style.maxHeight = content.scrollHeight + "px";
        if(content.parentElement.parentElement != null){//Nodrošina, ka kontents nekur nepazudīs izplešoties
          content.parentElement.parentElement.style.maxHeight = content.parentElement.parentElement.scrollHeight  + content.scrollHeight + "px";
        }
      }
    });
  }
}

var globalAddEventListener;

var collObjArr = [0,0,0];//Masīvs, kurā atrodas visi collapsible objekti
var collObjArrCount = 0;//skaita uz priekšu jauno objektu pozīcijas masīvā

function createSubColl(){
  for(i = collObjArrCount; i<collObjArrCount+2; i++){
    collObjArr[i] = new CollapsibleButton(new Arrow("arrow", "medIcon"), "Colors", document.getElementsByClassName("elemPlaceHolder")[0], 2);
    collObjArr[i].buildCollapseButton();
  }
  collObjArrCount+=2;
}































//slideris prieks white brightness
var newWhite = 100;//saglaba sevi baltas krasas vertibu, pasa sakuma vertiba ir uzlikta uz maksimumu

var whiteSlider = document.getElementById("whiteRange");//saņem vērtību no balta līdera 0 - 100
var whiteSliderOutput = document.getElementById("whiteBrightnessSliderTextValue");//mainīgais baltajai slīdera vērtībai, ko izvadīt
output.innerHTML = whiteSlider.value;
whiteSlider.oninput = function () {//izvada vērtību slīderim
  if (whiteSetOn == true) {
    whiteSliderOutput.innerHTML = this.value;
    if (isNaN(this.value) == false) {
      newWhite = this.value;//Tiek iestatita baltas krasas vertiba
    }
  }
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



function sendValue(sendValueOutput) {//parāda nosūtamos datus
  var sendPar = document.getElementById("outputText");//izvada vērtību uz ekrāna
  if (dataType == 1) {//parasta krasas iestatisana
    sendPar.innerText = "<" + dataType + lampNum + sendValueOutput + ">";
  } else if (dataType == 2) {//funkciju nosutisana
    sendPar.innerText = "<" + dataType + "00" + sendValueOutput + "000" + ">";//pedejas tris nulles ir prieks parametru iestatisanas. pagaidam netiek izmantots
  } else if (dataType == 3) {//gaismas muzikas nosutisana
    sendPar.innerText = "<3>";
  } else if (dataType == 0) {//saskaitisanas nosutisana
    sendPar.innerText = "<000>";
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

function stringColorSet() {//Si funkcija parveido rgbw krasu vertibas String rindina. Gatavu izsutisanai
  var countString = "";
  for (var i = 0; i < 4; i++) {//Nosaka vai saraksta skaitli ir divcipara vai viencipara vai trisciparu skaitlis un atbilstosi pieliek nulles
    if (rgbw[i] >= 100) {
      countString = rgbw[i];
    } else if (rgbw[i] < 100 && rgbw[i] >= 10) {
      countString = "0" + rgbw[i];
    } else {
      countString = "00" + rgbw[i];
    }
    sendRGBString = sendRGBString + countString;
    countString = "";
  }
  sendValue(sendRGBString);
  sendRGBString = "";
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













//JAUNAIS KODS:
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

